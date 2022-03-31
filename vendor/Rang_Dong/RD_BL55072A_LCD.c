/*
 * RD_BL55072A_LCD.c
 *
 *  Created on: Apr 11, 2021
 *      Author: Dat_UTC
 */


#include"RD_BL55072A_LCD.h"
#include "RD_Light_Sensor.h"

int Temp_2_mesh,Hum_2_mesh;
u8 LCD_Tx_buff0[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x00,0x00}; // cau hinh led 7seg goc duoi ben trai va bieu tuong do am (bieu tuong do am la bit cao nhat)
u8 LCD_Tx_buff1[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x02,0x00}; // cau hinh led 7seg goc duoi ben phai va bieu tuong % (bieu tuong % la bit cao nhat)
u8 LCD_Tx_buff2[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x04,0x00}; //

u8 LCD_Tx_buff3[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x07,0x00}; // 4 bit thap cau hinh 4 thanh dau cua led 7seg goc tren ben trai 4,con 4 bit cao khong dung
u8 LCD_Tx_buff6[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x06,0x00}; // 3 bit dau cau hinh 3 thanh con lai cua led 7seg goc tren ben trai
														   // bit thu 4 la vach song 2
														   // bit thu 5 la vach ngan cach giua nhiet do va do am
														   // bit thu 6 la bieu tuong nhiet do
														   // bit thu 7 dau am cua nhiet do
														   // bit thu 8 la vach song 1

u8 LCD_Tx_buff4[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x09,0x00}; // cau hinh led hang don vi cua nhiet do va vach song 3

u8 LCD_Tx_buff5[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x0b,0x00}; // 4 bit dau cau hinh 4 thanh dau cua led nho phan thap phan cua nhiet do
														   // bit thu 5 la dau cham ngan cach phan nguyen va phan thap phan cua nhiet do
														   // 3 bit cuoi cau hinh 3 thanh con lai cua led nho phan thap phan

u8 LCD_Tx_buff7[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x0d,0x00};// bit 1 vach pin so 5
														  // bit 2 khung vien pin
														  // bit 3 bieu tuong *C
														  // bit 4 vach song so 4
														  // bit 5 vach pin so 4
														  // bit 6 vach pin so 3
														  // bit 7 vach pin so 2
														  // bit 8 vach pin so 1


//u8 LCD_Tx_buff0[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x00,0x8e};
//u8 LCD_Tx_buff1[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x02,0x8e};
//u8 LCD_Tx_buff2[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x04,0xdf};
//u8 LCD_Tx_buff3[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x07,0x3d};
//u8 LCD_Tx_buff4[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x09,0x7b};
//u8 LCD_Tx_buff5[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x0b,0x16};
//u8 LCD_Tx_buff6[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x06,0xbb};
//u8 LCD_Tx_buff7[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x0d,0xf7};



//u8 LCD_Tx_buff0[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x00,0x8e};
//u8 LCD_Tx_buff1[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x02,0xfb};
//u8 LCD_Tx_buff2[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x04};
//u8 LCD_Tx_buff3[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x07,0x5f};
//u8 LCD_Tx_buff4[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x09,0x6f};
//u8 LCD_Tx_buff5[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x0b,0xd6};
//u8 LCD_Tx_buff6[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x06,0xFD};
//u8 LCD_Tx_buff7[7] = {0xbe,0xf0,0xfc,0xc8,0xe8,0x0d,0xf7};

extern u8 wave_level;
void RD_LCD_Set_data(float Temp,float Hum,u16 Battery){
	Temp_2_mesh = Temp*10;
	Hum_2_mesh = Hum*10;
	RD_LCD_show_Temp(Temp);
	RD_LCD_Show_Hum(Hum);
	RD_LCD_Show_Battery(Battery);

}

void LCD_Show_provision_state() {
	if(get_provision_state()==STATE_DEV_PROVED){
		RD_LCD_Show_BLE_Wave_level(4);
	}
	else if(get_provision_state()==STATE_DEV_UNPROV){
		RD_LCD_Show_BLE_Wave_level(0);
	}
	else if(get_provision_state()==STATE_DEV_PROVING){
		RD_LCD_Show_BLE_Wave_level(wave_level);
	}
}


void RD_LCD_show_Temp(float Temp){
	  int Temp_apsolute;

		if(Temp<0) Temp_apsolute =(-1)*Temp*10;
		else 	   Temp_apsolute=Temp*10;

		u8 Temp_1 =(u8)(Temp_apsolute/100);
		u8 Temp_2 =(u8)((Temp_apsolute%100)/10);
		u8 Temp_3 =(u8)(Temp_apsolute%10);

		RD_LCD_Show_TEMP_7SEG_1(Temp_1);
		RD_LCD_Show_Nomarl_7Seg(TEMP_7SEG_2,Temp_2);
		RD_LCD_Show_TEMP_HUM_7SEG_3 (TEMP_7SEG_3,Temp_3);
		RD_LCD_Show_Special_Characters ( TEMP_ICON,ICON_ON );
		RD_LCD_Show_Special_Characters ( TEMP_DOT_ICON,ICON_ON );
		RD_LCD_Show_Special_Characters ( CELSIUS_ICON,ICON_ON );

		if(Temp<0){
			RD_LCD_Show_Special_Characters ( NEGATIVE_TEMP_ICON,ICON_ON);

		}
		else RD_LCD_Show_Special_Characters ( NEGATIVE_TEMP_ICON,ICON_OFF);
}

void RD_LCD_Show_Hum (float Hum){
	int hum ;
	hum = Hum*10;
	u8 Hum_1 =(u8)(hum/100);
	u8 Hum_2 =(u8)((hum%100)/10);
	u8 Hum_3 =(u8)(hum%10);

//	RD_LCD_Show_TEMP_7SEG_1(Hum_1);
	RD_LCD_Show_Nomarl_7Seg(HUM_7SEG_1,Hum_1);
	RD_LCD_Show_Nomarl_7Seg(HUM_7SEG_2,Hum_2);
	RD_LCD_Show_TEMP_HUM_7SEG_3 (HUM_7SEG_3,Hum_3);

	RD_LCD_Show_Special_Characters ( HUM_ICON,ICON_ON );
	RD_LCD_Show_Special_Characters ( HUM_DOT_ICON,ICON_ON );
	RD_LCD_Show_Special_Characters ( BLACK_LINE,ICON_ON );
	RD_LCD_Show_Special_Characters ( PERCENT_ICON,ICON_ON );

}

void RD_LCD_Show_Battery(u16 Battery){
	if(Battery<20) RD_LCD_Show_Battery_Level(1);
	else if(Battery<40)RD_LCD_Show_Battery_Level(2);
	else if(Battery<60)RD_LCD_Show_Battery_Level(3);
	else if(Battery<80)RD_LCD_Show_Battery_Level(4);
	else if(Battery>=80)RD_LCD_Show_Battery_Level(5);

}
/*
 * void RD_Show_Nomarl_7Seg(RD_7Seg_ID_tdef LED_7Seg_ID,unsigned char data): ham su dung de dieu khien
 * 3 led bay thanh thong thuong , 3 led nay kha de dieu khien
 */
void RD_LCD_Show_Nomarl_7Seg(RD_7Seg_ID_tdef LED_7Seg_ID,unsigned char data){
   u8 *pointer;
   if(LED_7Seg_ID==HUM_7SEG_1)  	 pointer = &LCD_Tx_buff0;
   else if(LED_7Seg_ID==HUM_7SEG_2)  pointer = &LCD_Tx_buff1;
   else if(LED_7Seg_ID==TEMP_7SEG_2) pointer = &LCD_Tx_buff4;
	switch(data)
	{
		case 0:{
			*(pointer+6) = NORMAL_7SEG_MUMBER_0;

			break;
		}
		case 1:{
			*(pointer+6)  = NORMAL_7SEG_MUMBER_1;
			break;
		}
		case 2:{
			*(pointer+6)  = NORMAL_7SEG_MUMBER_2;
			break;
		}
		case 3:{
			*(pointer+6)  = NORMAL_7SEG_MUMBER_3;
			break;
		}
		case 4:{
			*(pointer+6)  = NORMAL_7SEG_MUMBER_4;
			break;
		}
		case 5:{
			*(pointer+6)  = NORMAL_7SEG_MUMBER_5;
			break;
		}
		case 6:{
			*(pointer+6)  = NORMAL_7SEG_MUMBER_6;
			break;
		}
		case 7:{
			*(pointer+6)  = NORMAL_7SEG_MUMBER_7;
			break;
		}
		case 8:{
			*(pointer+6)  = NORMAL_7SEG_MUMBER_8;
			break;
		}
		case 9:{
			*(pointer+6)  = NORMAL_7SEG_MUMBER_9;
			break;
		}
	}
	LCD_Tx_buff4[6]&=0x7F; //  tat di vach song 3

}
/*
 * void RD_Show_TEMP_7SEG_1(unsigned char data): ham dieu khien led hien thi hang chuc cua nhiet do
 * do led nay can duoc dieu khien bang 2 byte nen viec cau hinh cac so phuc tap hon cac led 7 thanh con lai
 */
void RD_LCD_Show_TEMP_7SEG_1(unsigned char data){
	switch(data)
	{
		case 0:{
			LCD_Tx_buff3[6] = TEMP_7SEG_1_BUFF3_NUMBER_0;
			LCD_Tx_buff6[6] = TEMP_7SEG_1_BUFF6_NUMBER_0;
			break;
		}
		case 1:{
			LCD_Tx_buff3[6] = TEMP_7SEG_1_BUFF3_NUMBER_1;
			LCD_Tx_buff6[6] = TEMP_7SEG_1_BUFF6_NUMBER_1;
			break;
		}
		case 2:{
			LCD_Tx_buff3[6] = TEMP_7SEG_1_BUFF3_NUMBER_2;
			LCD_Tx_buff6[6] = TEMP_7SEG_1_BUFF6_NUMBER_2;
			break;
		}
		case 3:{
			LCD_Tx_buff3[6] = TEMP_7SEG_1_BUFF3_NUMBER_3;
			LCD_Tx_buff6[6] = TEMP_7SEG_1_BUFF6_NUMBER_3;
			break;
		}
		case 4:{
			LCD_Tx_buff3[6] = TEMP_7SEG_1_BUFF3_NUMBER_4;
			LCD_Tx_buff6[6] = TEMP_7SEG_1_BUFF6_NUMBER_4;
			break;
		}
		case 5:{
			LCD_Tx_buff3[6] = TEMP_7SEG_1_BUFF3_NUMBER_5;
			LCD_Tx_buff6[6] = TEMP_7SEG_1_BUFF6_NUMBER_5;
			break;
		}
		case 6:{
			LCD_Tx_buff3[6] = TEMP_7SEG_1_BUFF3_NUMBER_6;
			LCD_Tx_buff6[6] = TEMP_7SEG_1_BUFF6_NUMBER_6;
			break;
		}
		case 7:{
			LCD_Tx_buff3[6] = TEMP_7SEG_1_BUFF3_NUMBER_7;
			LCD_Tx_buff6[6] = TEMP_7SEG_1_BUFF6_NUMBER_7;
			break;
		}
		case 8:{
			LCD_Tx_buff3[6] = TEMP_7SEG_1_BUFF3_NUMBER_8;
			LCD_Tx_buff6[6] = TEMP_7SEG_1_BUFF6_NUMBER_8;
			break;
		}
		case 9:{
			LCD_Tx_buff3[6] = TEMP_7SEG_1_BUFF3_NUMBER_9;
			LCD_Tx_buff6[6] = TEMP_7SEG_1_BUFF6_NUMBER_9;
			break;
		}
	}
}


/*
 * void RD_Show_TEMP_HUM_7SEG_3 (unsigned char data) :  dieu khien 2 led bay thanh phan thap phan cua nhiet do va do am
 */
void RD_LCD_Show_TEMP_HUM_7SEG_3 (RD_7Seg_ID_tdef LED_7Seg_ID,unsigned char data){
	u8 *pointer;
	if(LED_7Seg_ID==HUM_7SEG_3) pointer = &LCD_Tx_buff2;
	else if(LED_7Seg_ID==TEMP_7SEG_3) pointer = &LCD_Tx_buff5;
	switch(data)
	{
		case 0:{
			*(pointer+6) = TEMP_7SEG_3_MUMBER_0;
			break;
		}
		case 1:{
			*(pointer+6) = TEMP_7SEG_3_MUMBER_1;
			break;
		}
		case 2:{
			*(pointer+6) = TEMP_7SEG_3_MUMBER_2;
			break;
		}
		case 3:{
			*(pointer+6) = TEMP_7SEG_3_MUMBER_3;
			break;
		}
		case 4:{
			*(pointer+6) = TEMP_7SEG_3_MUMBER_4;
			break;
		}
		case 5:{
			*(pointer+6) = TEMP_7SEG_3_MUMBER_5;
			break;
		}
		case 6:{
			*(pointer+6)= TEMP_7SEG_3_MUMBER_6;
			break;
		}
		case 7:{
			*(pointer+6) = TEMP_7SEG_3_MUMBER_7;
			break;
		}
		case 8:{
			*(pointer+6) = TEMP_7SEG_3_MUMBER_8;
			break;
		}
		case 9:{
			*(pointer+6) = TEMP_7SEG_3_MUMBER_9;
			break;
		}
	}
}

void RD_LCD_Show_Special_Characters (RD_Icon_ID_tdef Icon,Icon_status status){

	if(status==ICON_ON){
		if(Icon==TEMP_ICON)  {
			LCD_Tx_buff6[6] |=(1<<5);
		}
		else if(Icon==HUM_ICON){
			LCD_Tx_buff0[6] |=(1<<7);
		}
		else if(Icon==TEMP_DOT_ICON){
			LCD_Tx_buff5[6] |=(1<<4);
		}
		else if(Icon==HUM_DOT_ICON){
			LCD_Tx_buff2[6] |=(1<<4);
		}
		else if(Icon==BLACK_LINE){
			LCD_Tx_buff6[6] |=(1<<4);
		}
		else if(Icon==PERCENT_ICON){
			LCD_Tx_buff1[6] |= (1<<7);
		}
		else if(Icon==CELSIUS_ICON){
			LCD_Tx_buff7[6] |=(1<<2);
		}
		else if(Icon==NEGATIVE_TEMP_ICON){
			LCD_Tx_buff6[6] |=(1<<6);
		}
	}
	else if(status==ICON_OFF){
		if(Icon==TEMP_ICON)  {
			LCD_Tx_buff6[6] &=0xDF;  // 1101 1111  bit thu 6 = 0 la bieu tuong nhiet do off
		}
		else if(Icon==HUM_ICON){
			LCD_Tx_buff0[6] &=0x7F; // 0111 1111  bit thu 8 = 0 la bieu tuong do am off
		}
		else if(Icon==TEMP_DOT_ICON){
			LCD_Tx_buff5[6] &=0xEF; // 1101 1111  bit thu 6 = 0 dau cham phan thap phan cua nhiet do off
		}
		else if(Icon==HUM_DOT_ICON){
			LCD_Tx_buff2[6] &=0xEF; // 1101 1111  bit thu 6 = 0 dau cham phan thap phan cua do am off
		}
		else if(Icon==BLACK_LINE){
			LCD_Tx_buff6[6] &=0xEF;//1110 1111  bit thu 5 = 0 vach ngan cach giua nhiet do va do am off
		}
		else if(Icon==PERCENT_ICON){
			LCD_Tx_buff1[6] &= 0x7F; // 0111 1111  bit thu 8 = 0 la bieu tuong % do am  off
		}
		else if(Icon==CELSIUS_ICON){
			LCD_Tx_buff7[6] &=(0<<2);
		}
		else if(Icon == NEGATIVE_TEMP_ICON){
			LCD_Tx_buff6[6] &=0xBF;
		}
	}
	//;
}

void RD_LCD_printf(){

	i2c_gpio_set(I2C_GPIO_GROUP_C0C1);
	i2c_master_init(0x7C,(unsigned char)(CLOCK_SYS_CLOCK_HZ/(4*I2C_CLK_SPEED)));

	i2c_write_series(0,0,(u8 *)LCD_Tx_buff0, 7);
	i2c_write_series(0,0,(u8 *)LCD_Tx_buff1, 7);
	i2c_write_series(0,0,(u8 *)LCD_Tx_buff2, 7);
	sleep_us(280);
	i2c_write_series(0,0,(u8 *)LCD_Tx_buff3, 7);
	i2c_write_series(0,0,(u8 *)LCD_Tx_buff4, 7);
	i2c_write_series(0,0,(u8 *)LCD_Tx_buff5, 7);
	i2c_write_series(0,0,(u8 *)LCD_Tx_buff6, 7);
	i2c_write_series(0,0,(u8 *)LCD_Tx_buff7, 7);

}


void RD_LCD_Show_BLE_Wave_level (u8 wave_level){

	switch(wave_level){
		case 0:{
			RD_Wave_Seg_On_Off(1,0);
			RD_Wave_Seg_On_Off(2,0);
			RD_Wave_Seg_On_Off(3,0);
			RD_Wave_Seg_On_Off(4,0);
			break;
		}
		case 1:{
			RD_Wave_Seg_On_Off(1,1);
			RD_Wave_Seg_On_Off(2,0);
			RD_Wave_Seg_On_Off(3,0);
			RD_Wave_Seg_On_Off(4,0);
			break;
		}
		case 2:{
			RD_Wave_Seg_On_Off(1,1);
			RD_Wave_Seg_On_Off(2,1);
			RD_Wave_Seg_On_Off(3,0);
			RD_Wave_Seg_On_Off(4,0);
			break;
		}
		case 3:{
			RD_Wave_Seg_On_Off(1,1);
			RD_Wave_Seg_On_Off(2,1);
			RD_Wave_Seg_On_Off(3,1);
			RD_Wave_Seg_On_Off(4,0);
			break;
		}
		case 4:{
			RD_Wave_Seg_On_Off(1,1);
			RD_Wave_Seg_On_Off(2,1);
			RD_Wave_Seg_On_Off(3,1);
			RD_Wave_Seg_On_Off(4,1);
			break;
		}

	}
}
void RD_Wave_Seg_On_Off (u8 Seg,u8 status){
	switch(Seg){
		case 1:{
			if(status) LCD_Tx_buff6[6] |=(1<<7);
			else LCD_Tx_buff6[6] &=0x7F;
			break;
		}
		case 2:{
			if(status) LCD_Tx_buff6[6] |=(1<<3);
			else LCD_Tx_buff6[6] &=0xF7;

			break;
		}
		case 3:{
			if(status) LCD_Tx_buff4[6] |=(1<<7);
			else LCD_Tx_buff4[6] &=0x7F;
			break;
		}
		case 4:{
			if(status) LCD_Tx_buff7[6] |=(1<<3);
			else LCD_Tx_buff7[6] &=0xF7;
			break;
		}
	}
}





void RD_LCD_Show_Battery_Level(u8 Battery_level){
	switch(Battery_level){
		case 0:{
			RD_Battery_Seg_On_Off(1,0);
			RD_Battery_Seg_On_Off(2,0);
			RD_Battery_Seg_On_Off(3,0);
			RD_Battery_Seg_On_Off(4,0);
			RD_Battery_Seg_On_Off(5,0);
			break;
		}
		case 1:{
			RD_Battery_Seg_On_Off(1,1);
			RD_Battery_Seg_On_Off(2,0);
			RD_Battery_Seg_On_Off(3,0);
			RD_Battery_Seg_On_Off(4,0);
			RD_Battery_Seg_On_Off(5,0);
			break;
		}
		case 2:{
			RD_Battery_Seg_On_Off(1,1);
			RD_Battery_Seg_On_Off(2,1);
			RD_Battery_Seg_On_Off(3,0);
			RD_Battery_Seg_On_Off(4,0);
			RD_Battery_Seg_On_Off(5,0);
			break;
		}
		case 3:{
			RD_Battery_Seg_On_Off(1,1);
			RD_Battery_Seg_On_Off(2,1);
			RD_Battery_Seg_On_Off(3,1);
			RD_Battery_Seg_On_Off(4,0);
			RD_Battery_Seg_On_Off(5,0);
			break;
		}
		case 4:{
			RD_Battery_Seg_On_Off(1,1);
			RD_Battery_Seg_On_Off(2,1);
			RD_Battery_Seg_On_Off(3,1);
			RD_Battery_Seg_On_Off(4,1);
			RD_Battery_Seg_On_Off(5,0);
			break;
		}
		case 5:{
			RD_Battery_Seg_On_Off(1,1);
			RD_Battery_Seg_On_Off(2,1);
			RD_Battery_Seg_On_Off(3,1);
			RD_Battery_Seg_On_Off(4,1);
			RD_Battery_Seg_On_Off(5,1);
			break;
		}
	}
}
void RD_Battery_Seg_On_Off (u8 Seg,u8 status){
	LCD_Tx_buff7[6]|=(1<<1);
	switch(Seg){
		case 1:{
			if(status==1) LCD_Tx_buff7[6] |=(1<<7);
			else if(status==0)LCD_Tx_buff7[6] &=0x7F;
			break;
		}
		case 2:{
			if(status) LCD_Tx_buff7[6] |=(1<<6);
			else LCD_Tx_buff7[6] &=0xB7;

			break;
		}
		case 3:{
			if(status) LCD_Tx_buff7[6] |=(1<<5);
			else LCD_Tx_buff7[6] &=0xDF;
			break;
		}
		case 4:{
			if(status) LCD_Tx_buff7[6] |=(1<<4);
			else LCD_Tx_buff7[6] &=0xEF;
			break;
		}
		case 5:{
			if(status) LCD_Tx_buff7[6] |=1;
			else LCD_Tx_buff7[6] &=0xFE;
			break;
		}
	}
}



void RD_LCD_test (u8 LCD_test_step,u8 test_pin_cnt,u8 test_wave_cnt){

	//LCD_test_step;

	RD_LCD_Show_TEMP_7SEG_1(LCD_test_step);
	RD_LCD_Show_Nomarl_7Seg(TEMP_7SEG_2,LCD_test_step);
	RD_LCD_Show_TEMP_HUM_7SEG_3 (TEMP_7SEG_3,LCD_test_step);
	RD_LCD_Show_Nomarl_7Seg(HUM_7SEG_1,LCD_test_step);
	RD_LCD_Show_Nomarl_7Seg(HUM_7SEG_2,LCD_test_step);
	RD_LCD_Show_TEMP_HUM_7SEG_3 (HUM_7SEG_3,LCD_test_step);

	Icon_status test_LCD_icon;
	if(LCD_test_step%2){

		//if(test_pin_wave_cnt>5) test_pin_wave_cnt = 0
		test_LCD_icon = ICON_OFF;
	}
	else test_LCD_icon = ICON_ON;






	RD_LCD_Show_Special_Characters ( TEMP_ICON,test_LCD_icon );
	RD_LCD_Show_Special_Characters ( TEMP_DOT_ICON,test_LCD_icon );
	RD_LCD_Show_Special_Characters ( CELSIUS_ICON,test_LCD_icon );
	RD_LCD_Show_Special_Characters ( HUM_ICON,test_LCD_icon );
	RD_LCD_Show_Special_Characters ( HUM_DOT_ICON,test_LCD_icon );
	RD_LCD_Show_Special_Characters ( BLACK_LINE,test_LCD_icon );
	RD_LCD_Show_Special_Characters ( PERCENT_ICON,test_LCD_icon );
	RD_LCD_Show_Special_Characters ( NEGATIVE_TEMP_ICON,test_LCD_icon);


	RD_LCD_Show_Battery_Level (test_pin_cnt);
	RD_LCD_Show_BLE_Wave_level(test_wave_cnt);
}
