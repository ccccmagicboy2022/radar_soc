#include "adc.h"
#include "gpio.h"
#include "phm320_pmu.h"
#include "phm320_mtpc.h"
#include "phm320_timer.h"
#include "phm320_pwm.h"

//V64版本，修正V63版本的串口不能设置不检测感光的BUG，感光默认门限改为255（不检测感光）
//V65- 增加上电开关5次与10次操作
//V67- 增加通过串口自校准单片机晶振频率功能，模组测试时需要先用串口发送9600波特率数据3C 3A 06 FA 3A 3E，模组接收之后会自动校准单片机晶振频率
			//模组第一次上电禁止用串口其他波特率与模组通讯，单片机晶振频率校准值存储在MTP隐藏扇区0X00位置
			//每个采样周期分成64段，舍弃积分值较高的12段，消除尖峰干扰，提高数据稳定性
			//改为滑窗3次累加判断，提高数据稳定性，封锁时间改为1.3秒，感应门限需要重新测试后确定
			//PWM频率与占空比参数修改，减少程序占用空间
//V67版本需要上电第一次测试发送串口数据1C才能校准晶振频率偏快较多的单片机
//V69-改进频率自校准程序，串口发送9600波特率数据3C 3A 06 FA 3A 3E，可以校准晶振频率偏差在-12%~+10%以内的单片机
		//上电后记录上电次数的MTP区域改为在2个位置保存和读取

//V6A- 修改为默认晶振频率10MHz，ADC采样率和脉冲供电频率改为20kHz，一个采样周期次数改为5120次，分成80段，脉冲供电宽度8us
		//改为4次滑窗，封锁时间改为7个采样周期

//V70-串口通讯中允许每次通讯后修正晶振频率
//V71-提高雷达供电电压
//V72-降低采样率到原先的1/32，625HZ,计算积分值时SUM11不再/2，门限值需要降低到之前版本的1/16

#define VERSION 0X72
#define MAX_DELTA0 1200
//30000
#define MAX_DELTA1 2000
//50000

#define  NUM		4
//舍弃每80段积分值中最大的4段，干扰较大时也可用8或16
//最小可以用2

#define  TH_LOW		1000
//20000
#define  TH_HIGH	1500000
#define	 TH_DEF		4000
//80000

//预设感光门限
#define  LIGHT_TH0 255
//20~25-8LUX

//延时时间,30s
#define DELAY_NUM0 10
//110
//每个采样周期256ms左右

#define MAX_DELAY 15000

#define LIGHT_ON()  pwm_start(PWM_5, 2500, 2500);
//#define LIGHT_ON()  PHM320_TOP->GPIO_VAL |= (1ul << P1_4)

#define LIGHT_STANDBY() pwm_start(PWM_5, 2500,250);
//10%占空比

#define LIGHT_OFF() pwm_start(PWM_5, 2500, 0);
#define LIGHT_HALF() pwm_start(PWM_5, 2500, 1250);
//#define LIGHT_OFF() PHM320_TOP->GPIO_VAL &= (~(1ul << P1_4))

//通信数据协议部分
#define PACKET_HEADER_BYTE1	0x3C
#define PACKET_HEADER_BYTE2	0x3A
#define PACKET_TAIL_BYTE1	0x3A
#define PACKET_TAIL_BYTE2	0x3E
#define PACKET_CMD_GET		0xFA
#define PACKET_CMD_SET		0xFD
#define PACKET_CMD_START	0xFC
#define PACKET_CMD_LIGHTON	0xFE
#define PACKET_CMD_LIGHTOFF	0xFF

//volatile
unsigned long  SUM0,SUM2=0,TH;
unsigned long  average,LIGHT=0,DELAY_NUM;
unsigned long light_ad,LIGHT_TH;

unsigned long RXnum=0;
unsigned long RXdata[20]={0};
unsigned long FREQ_CAL,FREQ_CHANGE=0,RFLDO_OSC_VAL=0x00000CB0;//0X80880C48;

volatile uint32_t hide_data,*data01 = (uint32_t *)0x00;//,*osc16m_trim = (uint32_t *)0x1f000010UL;

//unsigned long address_1;//,address_2;
	
void  __attribute__ ((section (".mtp_run_ram"))) volatile mtp_readx(void)
{ 

 //volatile str_mtpc_run_t mtpc_config;
 //clear_mem_struct(mtpc_config);
 //mtpc_config.mode = AHB_READX;
 
 PHM320_MTPC->MTPC_CTL_BITS.MODE = AHB_READX;//mtpc_config.mode;
 hide_data = *data01;

 //mtpc_config.mode = AHB_READ;
 PHM320_MTPC->MTPC_CTL_BITS.MODE = AHB_READ;//mtpc_config.mode;
}


void pwm_start(uint32_t pwm_port, uint32_t pwm_freq, uint32_t pwm_duty )
{
    PWM_Config_t pwmconf;

    pwmconf.idx  =  pwm_port;
    pwmconf.freq =  pwm_freq;
    pwmconf.duty = pwm_duty;
    pwm_enable(&pwmconf);
}

/*
void pwm_stop(uint32_t pwm_port)
{
    PWM_Config_t pwmconf;

    pwmconf.idx  =  pwm_port;
    pwm_disable(&pwmconf);
}
*/

int wdg_config(WDGCfg *wdg)
{
    if (wdg == NULL)
        return -1;

    STC_reg_st *tmr_reg = ((STC_reg_st*)(PHM320_STC_BASE ));

    tmr_reg->wdg_cnt = wdg->counter;
    tmr_reg->enable.bits.wdg_rst_en = wdg->reset_enable;	/* watch dog reset enable*/
    tmr_reg->enable.bits.wdg_en = wdg->enable;		/* watch dog counter enable */
    return 0;
}


void watch_dog(uint8_t dog_reset_enable, uint8_t dog_counter_enable, uint32_t dog_cmpvalue)
{
    WDGCfg dogconf;
    dogconf.enable = dog_counter_enable;
    dogconf.reset_enable = dog_reset_enable;
    dogconf.counter = dog_cmpvalue;

    wdg_config(&dogconf);
}


void feed_dog(void)
{
    STC_reg_st *tmr_reg = ((STC_reg_st*)(PHM320_STC_BASE ));
    
    tmr_reg->enable.bits.wdg_en = 0;		/* watch dog counter enable */
    tmr_reg->enable.bits.wdg_en = 1;		/* watch dog counter enable */
}


/////用P1_0口模拟串口发送数据，波特率9600
void send_data(unsigned char d)
{
    unsigned char i;//,j;

    PHM320_TOP->GPIO_VAL &= (~(1ul << P1_0));
    delay_us(111);		//91	
    for(i=0;i<8;i++)
    {
        if((d&0x01)==0)
        {
            PHM320_TOP->GPIO_VAL &= (~(1ul << P1_0));
        }
        else
        {
            PHM320_TOP->GPIO_VAL |= (1ul << P1_0);
        }
        delay_us(110);

        d>>=1;
    }
    PHM320_TOP->GPIO_VAL |= (1ul << P1_0);
    delay_us(150);
}

//延时n个50ms
void delay_sub(unsigned char n)
{
    unsigned long i;

        for(;n>0;n--)
        {
            for(i=0;i<250;i++)delay_us(219);	//10MHz	  //16MHz- 176  //50ms
            feed_dog();
		   // watch_dog(1,1,16100000);  //递减计数
        }
}

void adc_get_polling1(unsigned long *adc_val)
{
	while (!(PHM320_TOP->TOP_INT_FLAG_BITS.ADC)) {}
	*adc_val = PHM320_TOP->ADC_DATA;
	 PHM320_TOP->TOP_INT_CLEAR_BITS.ADC = 1;
	
}

void send_back(unsigned char data) 
{
	send_data(PACKET_HEADER_BYTE1);
	send_data(PACKET_HEADER_BYTE2);
	send_data(0X06);
	send_data(data);
	send_data(PACKET_TAIL_BYTE1);
	send_data(PACKET_TAIL_BYTE2);	
	
}

void set_var(void)
{
	TH=*(volatile uint32_t *)0x0FC0;

	if(TH<TH_LOW||TH>TH_HIGH)TH=TH_DEF;

	LIGHT_TH=*(volatile uint32_t *)0x0FC4;

	if((LIGHT_TH==0)||(LIGHT_TH>=0XFF))LIGHT_TH=LIGHT_TH0;
	else if(LIGHT_TH==0XFE)LIGHT_TH=255;

	DELAY_NUM=*(volatile uint32_t *)0x0FC8;
	if(DELAY_NUM==0||DELAY_NUM>MAX_DELAY)DELAY_NUM=DELAY_NUM0;		
	
}

void mtp_write_val(unsigned char i)
{
		send_back(i);
		mtp_erase(0x3e0);//address_1);
		//delay_us(176);		
        mtp_write(0x3e0,i);	
       // mtp_write(address_1+4,i);			
}

void set_freq(void)
{
	RFLDO_OSC_VAL&=0XFFFFFF00;
	RFLDO_OSC_VAL+=FREQ_CAL;
	PHM320_TOP->ANALOG_A_BITS.RFLDO_OSC=RFLDO_OSC_VAL;
}

int main()
{
	unsigned long SUM1_counter=0,SUM1_num=24,SUM0_num=8,stop_times=0,light_ad0,check_light_times=8,times=0;//,check_light_interval=8;
	//uint16_t  k;//,start_times=0;
	unsigned long k;
	unsigned long MAX_DELTA,SUM,SUM1=0,ALL_SUM1=0,SUM10=0,SUM01=16000000,init_times=0,run_times=0;
	//str_adc_init_cfg_t  adc_init_cfg;
	unsigned char i, j;
	unsigned long SUM1_MAX[NUM];	//每64次采样中积分值较大的12个信号积分值
	unsigned long SUM11=0;		//每64次采样后累加的积分值
	unsigned long SUM20=0,SUM21=0,SUM22=0,k32;	

	PHM320_TOP->ANALOG_A_BITS.RFLDO_OSC=RFLDO_OSC_VAL;//0x00000cB4;

	PHM320_TOP->TOP_CTLA_BITS.DIV= 250;		//脉冲供电和ADC频率改为20k，默认值500-10k@10MHz
	//PHM320_TOP->TOP_CTLA_BITS.MUX6 = 3;		//P1.5管脚设置为16M频率输出
	
    //ldo_powered_way(ALWAYS); //常供电
    ldo_powered_way(PLUS); //脉冲供电
	SUM0=16000000;

    gpio_config();
	
	LIGHT_ON();
  //  adc_config();
	adc_init(CH1);
	watch_dog(1,1,10000000);  //递减计数

	delay_sub(4);
	
	mtp_readx();
	FREQ_CAL=hide_data;
	if(FREQ_CAL<0x8A||FREQ_CAL>0XD6)
	{
		FREQ_CAL=0;	
		//PHM320_TOP->ANALOG_A_BITS.RFLDO_OSC=0x00000cB4;//0X80880C48;//晶振频率默认值
	}
	else
		set_freq();
		
	set_var();
	
	send_back(FREQ_CAL);//PACKET_CMD_START);	
	delay_sub(6);
	//address_1=0x0f90;
	//address_2=0x0f90;
	
	i=*(volatile uint32_t *)0x0f80;
/*	
	//0x0F90;
	address_1-=0x10;
	
	delay_sub(1);
	j=*(volatile uint32_t *)address_1;
	//0x0F80;

	address_1>>=2;
	//	address_2>>=2;
*/
	
	//if(i==j&&i<10)
	if(i<10)
	{

		if(i==4)	//进入快测模式
		{
			i++;		
			mtp_write_val(i);
			
			for(j=0;j<3;j++)
			{
				delay_sub(10);
				LIGHT_OFF();
				delay_sub(10);  
				LIGHT_HALF();             
			}

			//TH<<=3;
			LIGHT_TH=0xff;
			DELAY_NUM=7;	//快测模式下延时改为2秒
			init_times=420;	//快测模式下2分钟后恢复正常延时
			
		}
		else if(i==9)		//进入常亮模式
		{
			mtp_write_val(0);
			for(j=0;j<5;j++)
			{
				delay_sub(10);
				LIGHT_OFF();
				delay_sub(10);  
				LIGHT_HALF();             
			}

			while(1)
			{
				delay_sub(10);
				LIGHT_ON();
				send_back(10);
			}
		}
		else
		{
			if(i>9)i=0;
			i++;
			mtp_write_val(i);
			delay_sub(50);      //2.5S
		}
	}
	
	mtp_erase(0x3e0);
	//delay_us(176);
	//mtp_write(0x3e0,0);
	//mtp_write(address_1+4,0);	
	
	RFLDO_OSC_VAL+=0x80880000;
	PHM320_TOP->ANALOG_A_BITS.RFLDO_OSC=RFLDO_OSC_VAL;
	//delay_sub(1);
	
    top_clear_flag();
    //PHM320_TOP->TOP_INT_CLEAR_BITS.OUT = 1;
    irq_enable_all();	
	
    //延时9秒
	//send_data(0X31);		
    delay_sub(180);
	//send_data(0X32);	
	
	LIGHT_STANDBY();
	delay_sub(10);

    //计算直流电压平均值
    SUM=0;
    for(i=0;i<128;i++)	//1S
    {
        for(j=0;j<128;j++)
        {
            adc_get_polling1(&k);

            SUM+=k;
        }
		feed_dog();
    }
    average=SUM>>14;
	
    SUM=0;
	for(i=0;i<NUM;i++)SUM1_MAX[i]=0;
    while (1)
    {
		k32=0;
		for(i=0;i<32;i++)
		{
			adc_get_polling1(&k);
			k32+=k;
		}
		k32+=16;
		k=k32>>5;
		SUM+=k;
		
        times++;

        if(k>average){k-=average;}
        else {k=average-k;}
        SUM11+=k;

		if((times&0x1)==0)	//每2(64)次采样的信号积分值存一次	//总共80段
		{
			//SUM11>>=1;
			SUM1+=SUM11;
			
			for(i=0;i<NUM;i++)
			{
				if(SUM11>SUM1_MAX[i])
				{
					for(j=NUM-1;j>i;j--)
					{
						SUM1_MAX[j]=SUM1_MAX[j-1];	//移位排序得出积分值最大的8段
					}
					SUM1_MAX[i]=SUM11;
					break;
				}
			}
			SUM11=0;
		}
		
        if(times>=160)//5120)//&0x1000)>0)	//每5120次采样（256ms）统计一次信号积分值，滑窗取4次信号积分值的和做判断
        {
			if(init_times>0)
			{
				init_times--;
				if(init_times==0)
				{
					set_var();
				}
			}
			
			if(run_times<3000)run_times++;
				
            average+=SUM/160;//5120;//>>12;
            average>>=1;		//每260ms重新计算一次直流电压值

//舍弃数值较大的16个64次信号积分值，取较小的64个64次信号积分值累加为一个采样周期的信号积分值			
			for(i=0;i<NUM;i++)
			{
				SUM1-=SUM1_MAX[i];
				SUM1_MAX[i]=0;
			}
			
            SUM=SUM1;
            SUM1+=SUM20;
			SUM1+=SUM21;
			SUM1+=SUM22;			
//上电前4次测到的信号值累加作为噪声积分值，+200是避免噪声积分值过小,同时限制最大噪声积分值
            if((SUM20>0)&&(SUM0==16000000))
            {
                SUM0=SUM1+200;
                if(SUM0>300000)SUM0=300000;
            }

            SUM20=SUM21;
			SUM21=SUM22;
			SUM22=SUM;
			
            SUM2=SUM1;
            //asm("clrwdt");
            times=0;
			feed_dog();

            if(LIGHT==0)
            {
                check_light_times++;
                if(check_light_times>=8)
                {
                    //读取感光AD值
					adc_init(CH2);
					PHM320_TOP->ANALOG_B_BITS.PGA_BYPASS = 1;
					adc_get_polling1(&k);
					SUM=0;
					for(i=0;i<16;i++)
					{
						adc_get_polling1(&k);
						SUM+=k;
					}
					light_ad=SUM>>8;	//转换为8位AD值

					adc_init(CH1);
					PHM320_TOP->ANALOG_B_BITS.PGA_BYPASS = 0;
					adc_get_polling1(&k);

                    if((light_ad<=(light_ad0+2))&&(light_ad0<=(light_ad+2)))
                        light_ad=light_ad0;
                    light_ad0=light_ad;
                    check_light_times=0;
                }
            }
            if(SUM1_counter==0)
            {
                SUM10=SUM1;
                MAX_DELTA=1;
            }
			
			if((SUM10<(SUM1+MAX_DELTA))&&(SUM1<(SUM10+MAX_DELTA)))//噪声波动在一定范围内时
            {
                SUM1_counter++;
                ALL_SUM1+=SUM1;
                SUM10=ALL_SUM1/SUM1_counter;
                MAX_DELTA=SUM10>>3;
                if(MAX_DELTA<MAX_DELTA0)MAX_DELTA=MAX_DELTA0;
                if(MAX_DELTA>MAX_DELTA1)MAX_DELTA=MAX_DELTA1;

                if(SUM0>SUM10)
                {
                    SUM=SUM0-SUM10;

					if(SUM>10000)SUM0_num=5;
					else if(SUM>5000)SUM0_num=6;
					else SUM0_num=8;
					
					if((SUM1_counter>=SUM0_num)) //&&(SUM10<SUM0))
					{
						if(run_times<3000)
						{
							if(SUM1_num>16)	//没有点亮灯时允许噪声积分值减小
							{
								if(SUM0_num<=6)SUM0=SUM10;
								else if(SUM0>(SUM10+200))
								{
									SUM0+=SUM10;
									SUM0/=2;
								}
							}
						}
						SUM1_counter=0;
						ALL_SUM1=0;
					}
				}
                else if(SUM1_counter>=SUM1_num)		//SUM10>SUM0
                {
                   // if(SUM10>(SUM0+0X800))
                    {
                        SUM=SUM10-SUM0;

                        //if((SUM10<12000000)&&(SUM<3000000))
						if(SUM<300000)
//噪声积分值没有达到满幅时,并且新检测到的噪声值增加值小于3000000时，允许噪声值增大
                        {
                            SUM0+=SUM10;
                            SUM0/=2;
                        }
                    }
                    SUM1_counter=0;
                    ALL_SUM1=0;
                }
            }
            else
            {
                SUM1_counter=0;
                ALL_SUM1=0;
            }

            if(stop_times>0)	//灯灭后1秒以内不再判断是否有目标动作
            {
                stop_times--;
                if((SUM0>SUM01)&&(SUM1<(SUM01+2000)))SUM0=SUM01;
				//LIGHT_STANDBY();
            }
            else
            {
                if(SUM1>(SUM0+TH))
                {
                    if(light_ad<=LIGHT_TH)
                    {
                        if(LIGHT==0)SUM01=SUM0;
                        LIGHT=1;

                        LIGHT_ON();

                        SUM1_num=6;
                    }
                }
                else if(LIGHT>0)	//灯点亮时
                {
                    LIGHT++;
                    if(LIGHT>DELAY_NUM)
                    {
                        LIGHT=0;
                        SUM1_num=24;
                        LIGHT_STANDBY();
                        stop_times=7;
                        check_light_times=3;
                        SUM1_counter=0;
                        ALL_SUM1=0;
						run_times=2600;
                    }
                }
            }

//发送数据，测试用

 //           send_data(VERSION);
  //          send_data(TH>>10);
/*			
           // send_data(TH>>8);
 //           send_data(DELAY_NUM>>8);
 //           send_data(DELAY_NUM);

            send_data(average>>4);
           // send_data(average);
		
 //           send_data(LIGHT_TH);
           // send_data(light_ad);

            send_data(SUM0>>12);
            send_data(SUM0>>4);
            send_data(SUM2>>12);
            send_data(SUM2>>4);

            send_data(LIGHT);
			delay_sub(1);
*/			
            SUM=0;
            SUM1=0;
        }
    }

    return 0;
}

//模拟串口接收中断
__SECTION_INT __INT_HANDLER void irq_test(void)
{
	unsigned long i,k=0;
    top_clear_flag();
	
	//PHM320_TOP->TOP_INT_CLEAR_BITS.OUT = 1;
    //if(gpio_get_flag(P1_1))
	
	//if((PHM320_TOP->TOP_INT_FLAG >> P1_1) & 1)
	if((PHM320_TOP->TOP_INT_FLAG &2)>0)
    {
        //gpio_clear_flag(P1_1);
		PHM320_TOP->TOP_INT_CLEAR = 2;//1u << P1_1;
        //to do
	//	if(!gpio_get(P1_1))
		if((PHM320_TOP->GPIO_VAL &2) ==0)
		{
			if(FREQ_CAL==0)
				delay_us(60);
			else
				delay_us(141);  //147 	//允许96~198
				
			for(i=0;i<7;i++)
			{
				k>>=1;
			//	if(!gpio_get(P1_1))
				if((PHM320_TOP->GPIO_VAL &2) ==0)
					k&=0x7f;
				else k|=0x80;
				delay_us(112);
			}
			k>>=1;
		//	if(!gpio_get(P1_1))
			if((PHM320_TOP->GPIO_VAL &2) ==0)
				k&=0x7f;
			else k|=0x80;

			for(i=0;i<40;i++)		//一个循环6.1us左右
			{
				if((PHM320_TOP->GPIO_VAL&0x02)>0)break;
				delay_us(2);
			}
			
			if(i<40&&k>0)
			{
				if(FREQ_CAL==0)//&&i>0)
				{
					if(i>0)
					{
						FREQ_CAL=i+i+0X88;
						//PHM320_TOP->ANALOG_A_BITS.OSC16M_TRIM=FREQ_CAL;
						set_freq();
						FREQ_CHANGE=1;
					}
				}
				else if(((i<6&&i>0)||(i>10&&i<32))&&(FREQ_CHANGE==0))		//晶振频率准确时i值为8
				{
					FREQ_CAL+=i+i;
					FREQ_CAL-=16;
					//PHM320_TOP->ANALOG_A_BITS.OSC16M_TRIM=FREQ_CAL;
					set_freq();
					FREQ_CHANGE=1;
				}
			}
			
			if(i<40)
			{
				
				if(RXnum==2)
				{
					if(k>17||k<6)RXnum=0;
				}
				RXdata[RXnum++]=k;//RX1;
				
				if(FREQ_CAL>0&&FREQ_CHANGE==0)
				{
					if(RXnum == 1)
					{
						if(k!= PACKET_HEADER_BYTE1)
						{
							//RXdata[0] = 0;
							RXnum = 0;
						}
					}
					else if(RXnum == 2)
					{
						if(k!= PACKET_HEADER_BYTE2)
						{
							//RXdata[0] = 0;
							RXnum = 0;
						}
					}
					//else 

				}
				if(RXdata[2]!=17)
				{
					if(k==PACKET_HEADER_BYTE1)RXnum =1;
				}				
				if(RXnum> 17)
				{
					RXdata[2] = 0;
					RXnum = 0;
				}
				else if(RXnum == RXdata[2]&&RXnum>0)
				{
					//if(RXdata[RXnum-2]==PACKET_TAIL_BYTE1&&RXdata[RXnum-1]==PACKET_TAIL_BYTE2)
					if(RXdata[RXnum-1]==PACKET_TAIL_BYTE2)
					{
						if(RXdata[3]==PACKET_CMD_GET)	//读取实时数据
						{
							send_data(PACKET_HEADER_BYTE1);
							send_data(PACKET_HEADER_BYTE2);
							send_data(23);
							send_data(0xFA);
							send_data(VERSION);
							send_data(TH>>16);
							send_data(TH>>8);
							send_data(TH);
							send_data(LIGHT_TH);
							send_data((DELAY_NUM>>8) & 0xFF);
							send_data(DELAY_NUM & 0xFF);
							

							send_data(FREQ_CAL);
							send_data(LIGHT);
							send_data(i);
							send_data(0);
							
							send_data(light_ad);
							send_data(average>>4);
							send_data(SUM0>>16);
							send_data(SUM0>>8);
							send_data(SUM2>>16);
							send_data(SUM2>>8);
							send_data(PACKET_TAIL_BYTE1);
							send_data(PACKET_TAIL_BYTE2);
						}
/*						
						else if((RXdata[3] == 0x4D)&&(RXnum==6))
						{
							ldo_powered_way(ALWAYS); //常供电
							
							send_back(PACKET_CMD_SET);				
						}
						else if(RXdata[3] == 0x59)
						{
							ldo_powered_way(PLUS); //脉冲供电
							
							send_back(PACKET_CMD_SET);					
						}    						
*/					


						else if(RXdata[3] == PACKET_CMD_SET&&RXnum==17)	//设置感应门限，延时周期数，感光门限
						{
							TH = RXdata[4];
							TH = TH << 8;
							TH |= RXdata[5];
							TH = TH << 8;
							TH |= RXdata[6];
							//if(TH<TH_LOW||TH>TH_HIGH)TH=TH_DEF;
							LIGHT_TH = RXdata[7];
							//if(LIGHT_TH==0||LIGHT_TH==0XFF)LIGHT_TH=LIGHT_TH0;
							//else if(LIGHT_TH==0XFE)LIGHT_TH=255;
							DELAY_NUM = RXdata[8];
							DELAY_NUM = DELAY_NUM << 8;
							DELAY_NUM |= RXdata[9];
							//if(DELAY_NUM==0||DELAY_NUM>MAX_DELAY)DELAY_NUM=DELAY_NUM0;
							
							send_back(PACKET_CMD_SET);		
							//RXnum=0;

							if(RXdata[14] == 0)	//保存参数；RXdata[14] 不为0时不保存
							{
								//irq_disable_all();
								mtp_erase(0x3f0);
								//delay_us(176);
								mtp_write(0x3f0,TH);
//								delay_us(176);
								mtp_write(0x3f1,RXdata[7]);
//								delay_us(176);
								mtp_write(0x3f2,DELAY_NUM);
								//delay_us(176);
								set_var();
								//top_clear_flag();
								//irq_enable_all();
							}
			
						}

					}
					//for(i=0;i<10;i++)RXdata[i]=0;
				//	RXdata[0]=0;
				//	RXdata[1]=0;
					RXdata[2]=0;
					RXnum = 0;//清除数据长度
					
					if(FREQ_CHANGE==1)
					{
						mtp_erase(0x400);
						mtp_write(0x400,FREQ_CAL);
						FREQ_CHANGE=0;
					}
				}
			}
			else RXnum=0;			
			
		}
		//gpio_clear_flag(P1_1);
		 PHM320_TOP->TOP_INT_CLEAR = 1u << P1_1;
    }
}
