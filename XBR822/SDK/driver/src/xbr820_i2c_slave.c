#include "xbr820.h"
#include "xbr820_i2c_slave.h"

/**
  * @brief  I2C slave initialize. 
  *
  * @note   To assign an address for this I2C slave deive and enable it.
  *
  * @param  sl_addr: I2C slave device's address.
  * @retval none.
  */
void I2C_SL_Init(uint8_t sl_addr) {
	brx820_i2c_slave_regdef* i2c_sl;	
	i2c_sl = (brx820_i2c_slave_regdef*)(BRX820_I2C_slave);
	
	i2c_sl->slavedev = sl_addr << 1;
	i2c_sl->en_slaveb = 1;
	i2c_sl->rel_slb_rw = 1;
	i2c_sl->rel_slb_nack = 1;
	i2c_sl->rel_slb_stop = 1;
	i2c_sl->rel_slb_addr = 1;
	//i2c_sl->msk_slb_addr = 1;
	//i2c_sl->msk_slb_rw = 1;
	i2c_sl->msk_slb_stop = 1;
	i2c_sl->msk_slb_nack = 1;
	csi_vic_enable_irq(I2C_SLAVE_IRQn);
}

/**
  * @brief  I2C slave de-initialize. 
  *
  * @note   Disable this I2C slave device and set its address to zero.
  *
  * @param  none.
  * @retval none.
  */
void I2C_SL_DeInit(void){
	brx820_i2c_slave_regdef* i2c_sl;	
	i2c_sl = (brx820_i2c_slave_regdef*)(BRX820_I2C_slave);
	
	i2c_sl->en_slaveb = 0;	
	i2c_sl->slavedev = 0; //is this needed?
	csi_vic_disable_irq(I2C_SLAVE_IRQn);
}

/**
  * @brief  I2C slave device send data to the interface, eg. to the I2C master.
  * @param  data: which will be sent to the interface.
  *             It is an input param.
  * @retval none.
  */
void I2C_SL_SendData(uint8_t data) {
	brx820_i2c_slave_regdef* i2c_sl;	
	i2c_sl = (brx820_i2c_slave_regdef*)(BRX820_I2C_slave);
	
	i2c_sl->slaveb_data_2_iic = data;
}

/**
  * @brief  I2C slave device receive data from the interface, eg. from the I2C master.
  * @param  data: which is received from the interface.
  *             It is an output param.
  * @retval none.
  */
uint8_t I2C_SL_RecvSubAddr(void) {
	brx820_i2c_slave_regdef* i2c_sl;	
	i2c_sl = (brx820_i2c_slave_regdef*)(BRX820_I2C_slave);
	
	return i2c_sl->slaveb_addr;
}

/**
  * @brief  I2C slave device receive data from the interface, eg. from the I2C master.
  * @param  data: which is received from the interface.
  *             It is an output param.
  * @retval none.
  */
uint8_t I2C_SL_RecvData( void) {
	brx820_i2c_slave_regdef* i2c_sl;	
	i2c_sl = (brx820_i2c_slave_regdef*)(BRX820_I2C_slave);
	
	return (uint8_t)(i2c_sl->slaveb_data);
}

uint8_t I2C_SL_GetIntr(void) {
	brx820_i2c_slave_regdef* i2c_sl;	
	i2c_sl = (brx820_i2c_slave_regdef*)(BRX820_I2C_slave);
	
	return i2c_sl->slave_int.status;
}

void I2C_SL_Clr_RW(void)
{
	brx820_i2c_slave_regdef* i2c_sl;	
	i2c_sl = (brx820_i2c_slave_regdef*)(BRX820_I2C_slave);

	i2c_sl->rel_slb_rw = 1;
}

void I2C_SL_Clr_addr(void)
{
	brx820_i2c_slave_regdef* i2c_sl;	
	i2c_sl = (brx820_i2c_slave_regdef*)(BRX820_I2C_slave);

	i2c_sl->rel_slb_addr = 1;
}

/**
  * @brief  I2C slave device clear all the interrupts.
  * @param  none.
  * @retval none.
  */
void I2C_SL_ClrIntr(void) {
	brx820_i2c_slave_regdef* i2c_sl;	
	i2c_sl = (brx820_i2c_slave_regdef*)(BRX820_I2C_slave);
	i2c_sl->rel_slb_int = 1;
#if 0	
	//uint32_t status  = i2c_sl->slave_int.status;
	if (i2c_sl->slave_int.Bits.slave_rw)//(status & 0x1)
		i2c_sl->rel_slb_rw = 1;
	if (i2c_sl->slave_int.Bits.slave_nackb)//(status & 0x2)
		i2c_sl->rel_slb_nack = 1;
	if (i2c_sl->slave_int.Bits.slave_stopb)//(status & 0x4)
		i2c_sl->rel_slb_stop = 1;
	if (i2c_sl->slave_int.Bits.slave_addrb)//(status & 0x8)
		i2c_sl->rel_slb_addr = 1;
#endif
}

uint32_t I2C_SL_RecvOrSend(void) {
	brx820_i2c_slave_regdef* i2c_sl;	
	i2c_sl = (brx820_i2c_slave_regdef*)(BRX820_I2C_slave);

	return (i2c_sl->slave_int.status)&I2C_SL_INTR_RWO;
}