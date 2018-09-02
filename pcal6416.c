#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "pcal6416.h" 


uint16_t i2c_read_word_data(uint8_t dev_addr, uint8_t reg)
{
	// Assume i2c read word function is provided
	// In Linux, i2c read operation must be done by file manupulation through sysfs or ioctl
	// return value is the 2 bytes data read from register and return minus value on errors
	uint16_t value;

	return value;
}
int i2c_write_word_data(uint8_t dev_addr, uint8_t reg, uint16_t data)
{
	// Assume i2c write word function is provided
	// In Linux, i2c wirte operation must be done by file manupulation through sysfs or ioctl
	// return 0 on success and return minus value on errors
	int err;
	
	return err;
}

// Read data from PCAL register
int read_reg_pcal6416(uint8_t reg, uint16_t *data)
{
	int err = i2c_read_word_data(I2C_ADDR_PCAL6416, reg);
	if (err<0) {
		printf("Error reading I2C device");
		return err;
	}
	*data = (uint16_t)err;
	return 0;	
}

// Write data into PCAL register
int write_reg_pcal6416(uint8_t reg, uint16_t data)
{
	int err = i2c_write_word_data(I2C_ADDR_PCAL6416, reg, data);
	if (err<0){
		printf("Error writing I2C device");
	}
	return err;	
}

// Read Port0 & Port1  
uint16_t read_input_pcal6416(uint8_t offset)
{
	int err = i2c_read_word_data(I2C_ADDR_PCAL6416, PCAL6416_INPUT);
	if (err<0){
		printf("Error reading Input port\n");
		return err;
	}
	return (err & (BIT0 << offset)) ?  1: 0;	
}

// Write data on Port0 & Port1 
int write_output_pcal6416(uint16_t data, uint8_t offset)
{
	uint16_t val;
	int err = i2c_read_word_data(I2C_ADDR_PCAL6416, PCAL6416_CONFIG);
	if (err<0){
		printf("Error reading Output port\n");
		return err;
	}
	err = i2c_read_word_data(I2C_ADDR_PCAL6416, PCAL6416_OUTPUT);
	if (err<0){
		printf("Error reading Output port\n");
		return err;
	}
	val = (uint16_t)err;

	if (data)
		val |= (BIT0 << offset);
	else
		val &= ~(BIT0 << offset);

	
	err = i2c_write_word_data(I2C_ADDR_PCAL6416, PCAL6416_OUTPUT, val);
	if (err<0){
		printf("Error writing OUTPUT Port\n");
	}
	return err;	

}

// Software reset for the device
void reset_pcal6416(void)
{
#ifdef COMPILE
	// Assume there is GPIO connection to reset PCAL6416 in the master controller
	// /RESET pin of PCAL6416 is connected to a master controller's Output
	printf("RESET PCAL6416\n");
	
	controller_gpio(PCAL6146, LOW); // Reset PCAL6416
	usleep(10);						// hold LOW for 10us 
	controller_gpio(PCAL6146, HIGH);// Start PCAL6416
	usleep(50);						// Wait for PCAL6416's recovery 
#endif
}

// 	Initialization of PCAL6416
int init_pcal6416(void)
{
	int err;
	uint16_t data;
	printf("initializing PCAL6416\n");

	// Reset GPIO Expander before Initialization
	reset_pcal6416();

	// Output port Open Drain Disabled
	err = write_reg_pcal6416(PCAL6416_OUT_CONFIG, ODDIS);
	if (err<0) {
		printf("failed to set Output config\n");
		return err;
	}

	// Port 0 is input, Port 1 is output
	err = write_reg_pcal6416(PCAL6416_CONFIG, 0x00FF);
	if (err<0) {
		printf("failed to set CONFIG\n");
		return err;
	}
	// Output Strength Port 1: All output port set to half drive level
	err = write_reg_pcal6416(PCAL6416_OUT_STR1, 0x5555);
	if (err<0) {
		printf("failed to set Output drive strength\n");
		return err;
	}
	// Input Latch Register : Latch Disabled
	err = write_reg_pcal6416(PCAL6416_IN_LATCH, 0x0000);
	if (err<0) {
		printf("failed to set Input Latch \n");
		return err;
	}
	// Pull-up/Pull-down Enable Register : Disabled
	err = write_reg_pcal6416(PCAL6416_IN_LATCH, 0x0000);
	if (err<0) {
		printf("failed to set Input Latch \n");
		return err;
	}
	// Pull-up/Pull-down Selection Register : Don't need to set 

	// Interrupt Mask Register : Input port 0 Bit0 will assert Interrupt on its change
	err = write_reg_pcal6416(PCAL6416_INT_MASK, ~BIT0);
	if (err<0) {
		printf("failed to set Interrupt Mask \n");
		return err;
	}
	// Read Interrupt Status Register to clear
	err = read_reg_pcal6416(PCAL6416_INT_STATUS, &data);
	if (err<0) {
		printf("failed to read interrupt status register\n");
		return err;
	}
	return err;
}

// this format of handler is defined in <linux/interrupt.h>:
// Assume we can use this in this system
#ifdef COMPILE 	// To avoid compile errors 
irq_hanler_t irq_handler_PCAL6416(int irq, void *dev)
{
	// Process Interrupt from PCAL6416
	int err;
	uint16_t data;
	err = read_reg_pcal6416(PCAL6416_INT_STATUS, &data); // reset INT STATUS register
	if (!data) {
		printf("PCAL is not the originator\n");
		return IRQ_NONE;
	}
	read_input_pcal6416(&data);
	data &= BIT0;
	if (data) {
		// Everytime Input port 0 bit0 changes from its previous status
		// Run this part
		// Output Port1 Bit0
	}

	return IRQ_HANDLED;
}
#endif

int main(void)
{
	int status, i;
	uint16_t data;


	// Initialize
	status = init_pcal6416();
	if (!status) {
		printf("GPIO extender initialization failed\n");
		return status;
	}

#ifdef COMPILE		// To avoid compile errors 
	// Assume that request_irq() can set irq_handler_PCAL6416() 
	// Interrupt on PCAL6416 will envoke irq_hanler_PCAL6416()
	// request_irq() is defined in <linux/interrupt.h>
	request_irq(irq_handler_PCAL6416); 
#endif

	while(1) {

		// Read input port0 B1-B7 and Write output port1 B1-B7 according to input value
		for (i = 1; i < 8; i++){
			data = read_input_pcal6416(i); 
			write_output_pcal6416(data, i + PORT1_OFFSET);
		}
		usleep(200000);//make it faster
	}
}
