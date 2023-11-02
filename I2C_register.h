

#ifndef _I2C_REGISTER_H_
#define _I2C_REGISTER_H_

#define TWAR        *((volatile u8*)0x22)
#define TWBR        *((volatile u8*)0x20)
#define TWSR        *((volatile u8*)0x21)
#define TWCR        *((volatile u8*)0x56)
#define TWDR        *((volatile u8*)0x23)



void __vector_19(void) __attribute__((signal));


#endif
