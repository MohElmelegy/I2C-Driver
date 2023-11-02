
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "I2C_interface.h"
#include "I2C_register.h"

void I2C_VidInitialMaster(void)
{

	TWBR = 32;			 // TWBR MUST EQAUL TO 10 OR MORE TO AVOID INCORRECT DATA//
	CLR_BIT(TWSR, PIN0); // SET THE PRESCALLER TO 1//
	CLR_BIT(TWSR, PIN1); // SET THE PRESCALLER TO 1//
	SET_BIT(TWCR, PIN2); // Enable I2c
	/*
	#if INTERRUPT==ENABLE
		SET_BIT(TWCR,PIN0); //ENABLE TWI INTERRUPT FLAG//
	#endif
		*/
}

I2C_ERROR_STATUS I2C_u8MasterStartCondition(void)
{

	I2C_ERROR_STATUS STATE = NOK;
	SET_BIT(TWCR, PIN5); // start//
	SET_BIT(TWCR, PIN7); // CLEAR TWINT FLAG//

	while (GET_BIT(TWCR, PIN7) == 0);

	if ((TWSR & 0xF8) == 0x08)
	{
		STATE = OK;
	}
	return STATE;
}
I2C_ERROR_STATUS I2C_u8MasterRepeatedStart(void)
{

	I2C_ERROR_STATUS STATE = NOK;
	SET_BIT(TWCR, PIN5); // start//
	SET_BIT(TWCR, PIN7); // CLEAR TWINT FLAG//

	while (GET_BIT(TWCR, PIN7) == 0)
		;
	if ((TWSR & 0xF8) == 0x10)
	{
		STATE = OK;
	}
	return STATE;
}
void I2C_u8MasterStopCondition(void)
{

	SET_BIT(TWCR, PIN4); // STOP CONDITION//
	SET_BIT(TWCR, PIN7); // CLEAR TWINT FLAG//
}

I2C_ERROR_STATUS I2C_u8MasterSendAddressWrite(u8 LOC_u8SlaveadressWrite)
{

	I2C_ERROR_STATUS STATE = NOK;
	TWDR = (LOC_u8SlaveadressWrite << 1); // adress must be even to avoid genral call//
	CLR_BIT(TWCR, PIN5);
	SET_BIT(TWCR, PIN7); // CLEAR TWINT FLAG//
	while (GET_BIT(TWCR, PIN7) == 0); // wait until recieve the ACK//

	if ((TWSR & 0xF8) == 0x18)
	{
		STATE = OK;
	}
	return STATE;
}

I2C_ERROR_STATUS I2C_u8MasterSendAddressRead(u8 LOC_u8SlaveadressRead)
{

	I2C_ERROR_STATUS STATE = NOK;
	TWDR = (LOC_u8SlaveadressRead << 1); // adress must be even to avoid genral call//
	SET_BIT(TWDR, PIN0);
	CLR_BIT(TWCR, PIN5);
	SET_BIT(TWCR, PIN7); // CLEAR TWINT FLAG//
	while (GET_BIT(TWCR, PIN7) == 0)
		; // wait until recieve the ACK//
	if ((TWSR & 0xF8) == 0x40)
	{
		STATE = OK;
	}
	return STATE;
}

I2C_ERROR_STATUS I2C_u8MasterSendData(u8 LOC_u8Data)
{

	I2C_ERROR_STATUS STATE = NOK;
	TWDR = LOC_u8Data;
	SET_BIT(TWCR, PIN7); // CLEAR TWINT FLAG//
	while (GET_BIT(TWCR, PIN7) == 0)
		; // wait until recieve the ACK//

	if ((TWSR & 0xF8) == 0x28)
	{

		STATE = OK;
	}
	return STATE;
}
I2C_ERROR_STATUS I2C_u8MasterReciveData(u8 *GLO_u8Ptr)
{

	I2C_ERROR_STATUS STATE = NOK;
	SET_BIT(TWCR, PIN7); // CLEAR TWINT FLAG//
	while (GET_BIT(TWCR, PIN7) == 0)
		; // wait until recieve the ACK//

	if ((TWSR & 0xF8) == 0x58)
	{

		STATE = OK;
		*GLO_u8Ptr = TWDR;
	}
	return STATE;
}

////////////////////////////////Slave///////////////////////////////////////////////////////////////////

void I2C_vidIntialSlave(void)
{

	TWAR = 0b00000010;	 // adress//
	SET_BIT(TWCR, PIN2); // ENABLE TWI//
}

I2C_ERROR_STATUS I2C_u8SlaveCheckAddressWrite(void)
{
	I2C_ERROR_STATUS STATE = NOK;
	SET_BIT(TWCR, PIN6); // ENABLE THE ACK//
	SET_BIT(TWCR, PIN7); // clear flag//

	while (GET_BIT(TWCR, PIN7) == 0)
		; // wait until recieve the ACK//
	if ((TWSR & 0xF8) == 0x60)
	{
		STATE = OK;
	}
	return STATE;
}
I2C_ERROR_STATUS I2C_u8SlaveCheckAddressRead(void)
{
	I2C_ERROR_STATUS STATE = NOK;
	SET_BIT(TWCR, PIN6); // ENABLE THE ACK//
	SET_BIT(TWCR, PIN7); // clear flag//

	while (GET_BIT(TWCR, PIN7) == 0)
		; // wait until recieve the ACK//

	if ((TWSR & 0xF8) == 0xA8)
	{
		STATE = OK;
	}
	return STATE;
}
I2C_ERROR_STATUS I2C_u8SlaveReceiveData(u8 *ptr)
{

	I2C_ERROR_STATUS STATE = NOK;
	SET_BIT(TWCR, 7);
	while ((GET_BIT(TWCR, 7)) == 0)
		;
	if ((TWSR & 0xF8) == 0x80)
	{
		STATE = OK;
		*ptr = TWDR;
	}
	return STATE;
}

I2C_ERROR_STATUS I2C_u8SlaveTransmiteData(u8 DATA)
{

	I2C_ERROR_STATUS STATE = NOK;
	TWDR = DATA;
	SET_BIT(TWCR, 7);
	while ((GET_BIT(TWCR, 7)) == 0)
		;
	if ((TWSR & 0xF8) == 0xC0)
	{
		STATE = OK;
	}
	return STATE;
}
