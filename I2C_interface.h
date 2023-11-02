
#ifndef _I2C_INTERFACE_H_
#define _I2C_INTERFACE_H_

typedef enum{
	
	NOK,
	OK
	
}I2C_ERROR_STATUS;


////////////////////////////////master///////////////////////////////////////////////////////////////////
void I2C_VidInitialMaster(void);
I2C_ERROR_STATUS I2C_u8MasterStartCondition(void);
I2C_ERROR_STATUS I2C_u8MasterRepeatedStart(void);
void I2C_u8MasterStopCondition(void);
I2C_ERROR_STATUS I2C_u8MasterSendAddressWrite(u8 LOC_u8SlaveadressWrite);
I2C_ERROR_STATUS I2C_u8MasterSendAddressRead(u8 LOC_u8SlaveadressRead);
I2C_ERROR_STATUS I2C_u8MasterSendData(u8 LOC_u8Data);
I2C_ERROR_STATUS I2C_u8MasterReciveData(u8*GLO_u8Ptr);

////////////////////////////////Slave///////////////////////////////////////////////////////////////////
void I2C_vidIntialSlave(void);
I2C_ERROR_STATUS I2C_u8SlaveCheckAddressWrite(void);
I2C_ERROR_STATUS I2C_u8SlaveCheckAddressRead(void);
I2C_ERROR_STATUS I2C_u8SlaveReceiveData(u8 * ptr);
I2C_ERROR_STATUS I2C_u8SlaveTransmiteData(u8 DATA);


#endif

