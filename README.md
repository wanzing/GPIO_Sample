# GPIO_sample

This code is to show you how to control PCAL6416 which is GPIO Expander. .

 

It has 16 bits of GPIO pins that can be configured as Input or Output via I2C.

I used 8 bits of Input port and 8 bits of Output port. It reads the data from Input port and write the data to Output ports. Bit0 of input port is handled by interrupt handler.

As you can see in the code, there are some assumptions, such as I2C read/write function and interrupt handler related functions are ready to use.

 
