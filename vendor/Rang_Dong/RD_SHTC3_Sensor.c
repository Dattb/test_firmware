/*
 * RD_SHTC3_Sensor.c
 *
 *  Created on: Apr 11, 2021
 *      Author: Dat_UTC
 */
#include "RD_SHTC3_Sensor.h"
#include "RD_Light_Sensor.h"
u8 i2c_tx_buff0[2] = {0x35,0x17};// wake up buff
u8 i2c_tx_buff1[2] = {0x5c,0x24};// mesure SHTC3 in normal mode when wakeup
u8 i2c_tx_buff2[2] = {0xB0,0x98};// sleep buff
u8 i2c_SHTC3_rx_buff[RX_BUFF_DATA_LEN] = {0};


SHTC3_Data_tdef RD_Read_Raw_Temp_Hum_data(){
	SHTC3_Data_tdef data={0};
	 RD_I2C_Read_SHTC3();
	if(RD_SHTC3_CRC_Check (i2c_SHTC3_rx_buff[0],i2c_SHTC3_rx_buff[1])==i2c_SHTC3_rx_buff[2] &&
	RD_SHTC3_CRC_Check(i2c_SHTC3_rx_buff[3],i2c_SHTC3_rx_buff[4])==i2c_SHTC3_rx_buff[5]){

		u16 Hum_Raw =(i2c_SHTC3_rx_buff[0]<<8)|i2c_SHTC3_rx_buff[1];
		u16 Temp_Raw =(i2c_SHTC3_rx_buff[3]<<8)|i2c_SHTC3_rx_buff[4];
		float  Temp = 1.0*Temp_Raw/65536*175-45;
	    float  Hum  = 1.0*Hum_Raw/65536*100;

	    data.humidity = Hum;
	    data.temperature = Temp;
	}
	return data;

}


u8 RD_SHTC3_CRC_Check (u8 data0,u8 data1)
 {
 	unsigned char data[2];
 	data[0] =data0;
 	data[1] =data1;
	unsigned char nbrOfBytes = 2;
  	unsigned char bit;        // bit mask
  	unsigned char  crc = 0xFF; // calculated checksum
  	unsigned char byteCtr;    // byte counter

  // calculates 8-Bit checksum with given polynomial
  for(byteCtr = 0; byteCtr < nbrOfBytes; byteCtr++) {
    crc ^= (data[byteCtr]);
    for(bit = 8; bit > 0; --bit) {
      if(crc & 0x80) {
        crc = (crc << 1) ^ (0x131);
      } else {
        crc = (crc << 1);
      }
    }
  }

  return crc;
}

void RD_I2C_Read_SHTC3 ()
{
	i2c_gpio_set(I2C_GPIO_GROUP_C0C1);
	i2c_master_init(0xe0,(unsigned char)(CLOCK_SYS_CLOCK_HZ/(4*I2C_CLK_SPEED)));
	i2c_write_series(0,0,(u8 *)i2c_tx_buff0, 2);
	sleep_us(160);
	i2c_write_series(0,0,(u8 *)i2c_tx_buff1, 2);
	sleep_ms(13);
	i2c_read_series(0,0,i2c_SHTC3_rx_buff,7);
	i2c_write_series(0,0,(u8 *)i2c_tx_buff2, 2);
}

void RD_I2C_Read_SHT30(){
	i2c_gpio_set(I2C_GPIO_GROUP_C0C1);
	i2c_master_init(0x52,(unsigned char)(CLOCK_SYS_CLOCK_HZ/(4*I2C_CLK_SPEED)));

		u8 i2c_SHT30_tx_buff1[1] = {0x01};	// control command
		u8 i2c_SHT30_tx_buff2[1] = {0x03};	// control command
		u8 i2c_SHT30_read_Red_buff1[1] = {0};
		u8 i2c_SHT30_read_Red_buff2[1] = {0};
//		u8 i2c_SHT30_read_Green_buff[2] = {0};
//		u8 i2c_SHT30_read_Blue_buff[2] = {0};

		i2c_write_series(0x00|TCS34725_COMMAND_BIT,1,(u8 *)i2c_SHT30_tx_buff1, 1);
		sleep_ms(3);
		i2c_write_series(0x00|TCS34725_COMMAND_BIT,1,(u8 *)i2c_SHT30_tx_buff2, 1);

		i2c_read_series(TCS34725_COMMAND_BIT|0x16,1,(u8 *)i2c_SHT30_read_Red_buff1,1);
		i2c_read_series(TCS34725_COMMAND_BIT|0x17,1,(u8 *)i2c_SHT30_read_Red_buff2,1);
		//mesh_tx_cmd2normal_primary(0x52, (u8 *)i2c_SHT30_rx_buff, 6, 0x0001, 2);
}
