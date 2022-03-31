/*
 * RD_BL55072A_LCD.h
 *
 *  Created on: Apr 11, 2021
 *      Author: Dat_UTC
 */

#ifndef RD_BL55072A_LCD_H_
#define RD_BL55072A_LCD_H_

#include "proj/tl_common.h"
#include "vendor/mesh/app.h"
#include "vendor/mesh_lpn/app.h"
#include "vendor/mesh_provision/app.h"
#include "vendor/mesh_switch/app.h"
#include "vendor/common/sensors_model.h"
#include "proj_lib/mesh_crypto/sha256_telink.h"
#include "vendor/common/app_heartbeat.h"
#include"Sensor_Flash.h"



typedef enum {

	TEMP_7SEG_1,
	TEMP_7SEG_2,
	TEMP_7SEG_3,
	HUM_7SEG_1,
	HUM_7SEG_2,
	HUM_7SEG_3,
}RD_7Seg_ID_tdef;



typedef enum {
	TEMP_ICON,
	HUM_ICON,
	TEMP_DOT_ICON,
	HUM_DOT_ICON,
	BLACK_LINE,
	PERCENT_ICON,
	CELSIUS_ICON,
	NEGATIVE_TEMP_ICON
}RD_Icon_ID_tdef;


typedef enum {
	ICON_ON=1,
	ICON_OFF=0,
}Icon_status;


/*************************************************************
 *    ky hieu tung thanh voi Normal 7seg
 *          4
 *       +++++++++
 *       +       +
 *    7  +       + 3
 *       +   6    +
 *       +++++++++
 *       +       +
 *    5  +       + 2
 *       +       +
 *       +++++++++
 *           1
 *
 *************************************************************
 */


#define NORMAL_7SEG_MUMBER_0  	0xDF   //so 0 cua led 7 thanh binh thuong (Led Hum 1, Led Hum 2, Led Temp 2)
#define NORMAL_7SEG_MUMBER_1  	0x86   //so 1 cua led 7 thanh binh thuong (Led Hum 1, Led Hum 2, Led Temp 2)
#define NORMAL_7SEG_MUMBER_2  	0xBD   //so 2 cua led 7 thanh binh thuong (Led Hum 1, Led Hum 2, Led Temp 2)
#define NORMAL_7SEG_MUMBER_3  	0xAF   //so 3 cua led 7 thanh binh thuong (Led Hum 1, Led Hum 2, Led Temp 2)
#define NORMAL_7SEG_MUMBER_4 	0xE6   //so 4 cua led 7 thanh binh thuong (Led Hum 1, Led Hum 2, Led Temp 2)
#define NORMAL_7SEG_MUMBER_5  	0xEB   //so 5 cua led 7 thanh binh thuong (Led Hum 1, Led Hum 2, Led Temp 2)
#define NORMAL_7SEG_MUMBER_6  	0xFB   //so 6 cua led 7 thanh binh thuong (Led Hum 1, Led Hum 2, Led Temp 2)
#define NORMAL_7SEG_MUMBER_7  	0x8E   //so 7 cua led 7 thanh binh thuong (Led Hum 1, Led Hum 2, Led Temp 2)
#define NORMAL_7SEG_MUMBER_8  	0xFF   //so 8 cua led 7 thanh binh thuong (Led Hum 1, Led Hum 2, Led Temp 2)
#define NORMAL_7SEG_MUMBER_9  	0xEF   //so 9 cua led 7 thanh binh thuong (Led Hum 1, Led Hum 2, Led Temp 2)


#define TEMP_7SEG_3_MUMBER_0  	0xBF   //so 0  led 7 thanh hien thi phan thap phan cua nhiet do (Led Temp 3)
#define TEMP_7SEG_3_MUMBER_1  	0x16   //so 1  led 7 thanh hien thi phan thap phan cua nhiet do (Led Temp 3)
#define TEMP_7SEG_3_MUMBER_2  	0x7D   //so 2  led 7 thanh hien thi phan thap phan cua nhiet do (Led Temp 3)
#define TEMP_7SEG_3_MUMBER_3  	0x5F   //so 3  led 7 thanh hien thi phan thap phan cua nhiet do (Led Temp 3)
#define TEMP_7SEG_3_MUMBER_4 	0xD6   //so 4  led 7 thanh hien thi phan thap phan cua nhiet do (Led Temp 3)
#define TEMP_7SEG_3_MUMBER_5  	0xDB   //so 5  led 7 thanh hien thi phan thap phan cua nhiet do (Led Temp 3)
#define TEMP_7SEG_3_MUMBER_6  	0xFB   //so 6  led 7 thanh hien thi phan thap phan cua nhiet do (Led Temp 3)
#define TEMP_7SEG_3_MUMBER_7  	0x1E   //so 7  led 7 thanh hien thi phan thap phan cua nhiet do (Led Temp 3)
#define TEMP_7SEG_3_MUMBER_8  	0xFF   //so 8  led 7 thanh hien thi phan thap phan cua nhiet do (Led Temp 3)
#define TEMP_7SEG_3_MUMBER_9  	0xDF   //so 9  led 7 thanh hien thi phan thap phan cua nhiet do (Led Temp 3)



#define TEMP_7SEG_1_BUFF3_NUMBER_0	 0x0F
#define TEMP_7SEG_1_BUFF6_NUMBER_0	 0x05

#define TEMP_7SEG_1_BUFF3_NUMBER_1	 0X06
#define TEMP_7SEG_1_BUFF6_NUMBER_1	 0x00

#define TEMP_7SEG_1_BUFF3_NUMBER_2	 0x0D
#define TEMP_7SEG_1_BUFF6_NUMBER_2	 0x03

#define TEMP_7SEG_1_BUFF3_NUMBER_3	 0x0F
#define TEMP_7SEG_1_BUFF6_NUMBER_3	 0x02

#define TEMP_7SEG_1_BUFF3_NUMBER_4	 0x06
#define TEMP_7SEG_1_BUFF6_NUMBER_4	 0x06

#define TEMP_7SEG_1_BUFF3_NUMBER_5	 0x0B
#define TEMP_7SEG_1_BUFF6_NUMBER_5	 0x06

#define TEMP_7SEG_1_BUFF3_NUMBER_6	 0x0B
#define TEMP_7SEG_1_BUFF6_NUMBER_6	 0x07

#define TEMP_7SEG_1_BUFF3_NUMBER_7	 0x0E
#define TEMP_7SEG_1_BUFF6_NUMBER_7	 0x00

#define TEMP_7SEG_1_BUFF3_NUMBER_8 	 0x0F
#define TEMP_7SEG_1_BUFF6_NUMBER_8	 0x07

#define TEMP_7SEG_1_BUFF3_NUMBER_9 	 0x0F
#define TEMP_7SEG_1_BUFF6_NUMBER_9	 0x06






void RD_LCD_Set_data(float Temp,float Hum,u16 Battery);
void LCD_Show_provision_state();
void RD_LCD_show_Temp(float Temp);
void RD_LCD_Show_Hum (float Hum);
void RD_LCD_Show_Battery(u16 Battery);
void RD_LCD_Show_Nomarl_7Seg(RD_7Seg_ID_tdef LED_7Seg_ID,unsigned char data);
void RD_LCD_Show_TEMP_7SEG_1(unsigned char data);
void RD_LCD_Show_TEMP_HUM_7SEG_3 (RD_7Seg_ID_tdef LED_7Seg_ID,unsigned char data);
void RD_LCD_Show_Special_Characters (RD_Icon_ID_tdef Icon,Icon_status status);
void RD_LCD_printf();
void RD_Wave_Seg_On_Off (u8 Seg,u8 status);
void RD_LCD_Show_BLE_Wave_level (u8 wave_level);
void RD_Battery_Seg_On_Off (u8 Seg,u8 status);
void RD_LCD_Show_Battery_Level(u8 Battery_level);
void RD_LCD_test (u8 LCD_test_step,u8 test_pin_cnt,u8 test_wave_cnt);
#endif /* RD_BL55072A_LCD_H_ */



