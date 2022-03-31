/*
 * RD_SHTC3_Sensor.h
 *
 *  Created on: Apr 11, 2021
 *      Author: Dat_UTC
 */
#include "proj/tl_common.h"
#include "vendor/mesh/app.h"
#include "vendor/mesh_lpn/app.h"
#include "vendor/mesh_provision/app.h"
#include "vendor/mesh_switch/app.h"
#include "vendor/common/sensors_model.h"
#include "proj_lib/mesh_crypto/sha256_telink.h"
#include "vendor/common/app_heartbeat.h"
#include"Sensor_Flash.h"

#ifndef RD_SHTC3_SENSOR_H_
#define RD_SHTC3_SENSOR_H_

#define TCS34725_COMMAND_BIT (0x80)
typedef struct {

	float  temperature;
	float  humidity;
}SHTC3_Data_tdef;
void RD_I2C_Read_SHT30();
SHTC3_Data_tdef RD_Read_Raw_Temp_Hum_data();
void RD_I2C_Read_SHTC3 ();
u8 RD_SHTC3_CRC_Check (u8 data0,u8 data1);
#endif /* RD_SHTC3_SENSOR_H_ */
