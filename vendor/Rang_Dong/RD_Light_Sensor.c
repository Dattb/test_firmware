/*
 * RD_Light_Sensor.c
 *
 *  Created on: Nov 19, 2020
 *      Author: Dat UTC
 */


#include "RD_Light_Sensor.h"
#include"RD_BL55072A_LCD.h"
#include"RD_SHTC3_Sensor.h"
u8 check_done=0;
u8 check_poll=1;
u16 lux_val_old,lux_val_new;
u16 friend_poll = 60000;
u16 provision_time = 60000;
bool lux_changle;
u16 RD_LS_TransferCntInMin = 60*1000;    // 60*1000=60.000 ms
u32 RD_LS_TransferCntInHour = 60*60*1000;   // 60*60*1000 =3.600.000 ms
u8 factory_test_CLD_flag = 0;

bool tongle_Secne = 0;

extern pm_para_t	pmParam;


u8 sensor_to_gw_tx_buff[GW_TX_BUFF_DATA_LEN]={0};
u8 power_to_gw_tx_buff[GW_TX_BUFF_DATA_LEN]={0};

extern u8 i2c_tx_buff0[];
extern u8 i2c_tx_buff1[];
extern u8 i2c_tx_buff2[];

extern u8 i2c_SHTC3_rx_buff[];

mesh_lpn_par_t mesh_lpn_par;


u8 RD_Send_Scene_to_RGB_Buff[GW_TX_BUFF_DATA_LEN]={0};

u16 Gw_addr=0x0001;


u8 RD_Sensor_Send_Data_Cnt;
u16 RD_Sensor_Send_power_Cnt;







// chi thay doi data

extern  u8 LCD_Tx_buff0[];
extern  u8 LCD_Tx_buff1[];
extern  u8 LCD_Tx_buff2[];
extern  u8 LCD_Tx_buff3[];
extern  u8 LCD_Tx_buff4[];
extern  u8 LCD_Tx_buff5[];
extern  u8 LCD_Tx_buff6[];
extern  u8 LCD_Tx_buff7[];
extern  u8 LCD_Tx_buff8[];


extern int Temp_2_mesh,Hum_2_mesh;



extern RD_SensorSencesStoreTypedef RD_Sence_Store_obj[];
extern u8  RD_Sence_Flash_Read_Buff [];
extern u8  RD_Sence_Flash_Write_Buff[];

bool chek_3_cycle_flag;
u16 SenceID;

/*
 * RD_power_read()
 * Ham co tac dung doc ra ADC cho biet dien ap cua pin qua do dua vao bo tham so da khao sat se biet duoc
 * ung voi dien ap bao nhieu thi dung luong pin con lai la bao nhieu.
 */
unsigned int RD_power_read()
{
    RD_ADC_init (GPIO_PB5);
	unsigned int power_read;
	float power_persent=0;
    //sleep_us(2000);
	power_read = adc_sample_and_get_result();
	//do 3.28v => 2.382v       => he so la 1.4 lan
	// do 2.814v => 2.122 v     => he so la 1.3 lan
	// => chon he so 1.35
	// pin 0% => 1.8V
	// do tren mach khong phan ap nen dien ap pin phai /2 (tren cam bien anh sang dien ap ADC=1/2 dien ap pin)
	power_read=(u16)((1.35*power_read-1800)/(3200-1800)*100);

	return power_read;
}

/*
 * RD_ADC_init (u32 gpio)
 * Ham khoi tao bo ADC day la cau hinh khuyen dung
 */
void RD_ADC_init (u32 gpio)
{
	adc_init();
	adc_base_init(gpio);
	adc_power_on_sar_adc(1);

}


u8  friend_check(){
	static u8 check_friend_new = 0,check_friend_old = 0;
	check_friend_new = mesh_lpn_par.link_ok;
	if(check_friend_old != check_friend_new){
		check_friend_old = check_friend_new;
		return check_friend_new;
	}
	return 0;
}

/*
 * RD_light_sensor_tx (u16 loop)
 * Day la ham tinh toan va truyen cuong do sang cua cam bien.
 * Dua vao thoi gian cho vong loop co the cai dat duoc sau bao lau cam bien moi gui
 * ban tin bao cao cuong do sang 1 lan
 * khi an nut se gui ca cuong do sang va % pin
 */
#define NEGATIVE_EN  1
void RD_light_sensor_tx (u16 loop)
{

	RD_Sensor_Send_Data_Cnt++;
	RD_Sensor_Send_power_Cnt++;
	if((RD_Sensor_Send_Data_Cnt>=RD_SHTC3_SENSOR_SEND_DATA_TIME)||pmParam.is_pad_wakeup){

	*sensor_to_gw_tx_buff =0x06;
	*(sensor_to_gw_tx_buff+1) =0x00;

	RD_LCD_Set_data(RD_Read_Raw_Temp_Hum_data().temperature,
					RD_Read_Raw_Temp_Hum_data().humidity,
					(u16)(RD_power_read()));
	LCD_Show_provision_state();
	RD_LCD_printf();
	//Temp_2_mesh=-28.8;
	if(Temp_2_mesh<0){
		Temp_2_mesh = (-1)*Temp_2_mesh;
		u16 temp =Temp_2_mesh;
		*(sensor_to_gw_tx_buff+2) = (u8)(temp>>8);
		*(sensor_to_gw_tx_buff+2) |= (NEGATIVE_EN<<7);
		*(sensor_to_gw_tx_buff+3) = (u8)(temp);
	}
	else {
		u16 temp =Temp_2_mesh;
		*(sensor_to_gw_tx_buff+2) = (u8)(temp>>8);
		*(sensor_to_gw_tx_buff+3) = (u8)(temp);
	}

	u16 hum =Hum_2_mesh;
	*(sensor_to_gw_tx_buff+4) = (u8)(Hum_2_mesh>>8);
	*(sensor_to_gw_tx_buff+5) = (u8)(Hum_2_mesh);
	mesh_tx_cmd2normal_primary(SENSOR_STATUS, (u8 *)sensor_to_gw_tx_buff, GW_TX_BUFF_DATA_LEN, Gw_addr, RSP_MAX);
	if(pmParam.is_pad_wakeup){
		RD_Send_TempHumSensorPower();
		RD_Sensor_Send_power_Cnt--;
	}

		RD_Sensor_Send_Data_Cnt=0;

	}

	if(RD_Sensor_Send_power_Cnt>=RD_SHTC3_SENSOR_SEND_POWER_TIME){
		RD_Send_TempHumSensorPower();
		RD_Sensor_Send_power_Cnt=0;
	}

}



void factory_test_LCD (u8 lCD_test_flag,u8 LCD_test_step,u8 pin_cnt,u8 wave_cnt){
	if(lCD_test_flag) {
		RD_LCD_test (LCD_test_step,pin_cnt,wave_cnt);

	}
}



/*
 * Ham truc tiep gui gia tri % pin cua cam bien
 */
void RD_Send_TempHumSensorPower()
{
	u16 Power_Data=RD_power_read();
	*power_to_gw_tx_buff = 0x01;
	*(power_to_gw_tx_buff+1) = 0x00;
	*(power_to_gw_tx_buff+2) = (u8) (Power_Data>>8);
	*(power_to_gw_tx_buff+3) = (u8)(Power_Data);
	mesh_tx_cmd2normal_primary(SENSOR_STATUS, (u8 *)power_to_gw_tx_buff, GW_TX_BUFF_DATA_LEN, Gw_addr, RSP_MAX);
}


u8 type_device_to_gw_tx_buff[TYPE_DEVICE_BUFF_LEN] ={0};

int RD_Messenger_Process_Type_Device(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par){
	//uart_CSend("Co ban tin");
	//char UART_TempSend[128];
	//sprintf(UART_TempSend,"Messenger type:%d-Content:%x-%x-%x-%x-%x-%x-%x-%x\n",par_len,par[0],par[1],par[2],par[3],par[4],par[5],par[6],par[7]);
	//uart_CSend(UART_TempSend);
	//uart_CSend("..\n");
	uint16_t Message_Header = (par[1]<<8)|par[0];
	if(Message_Header==RD_TYPE_DEVICE_RSP_HEADER){
//		for(uint8_t i=0;i<11;i++)
//		type_device_to_gw_tx_buff[i] = RD_NONE;
		type_device_to_gw_tx_buff[0] = (u8)(RD_TYPE_DEVICE_RSP_HEADER);
		type_device_to_gw_tx_buff[1] = (u8)(RD_TYPE_DEVICE_RSP_HEADER>>8);
		type_device_to_gw_tx_buff[2] = RD_SENSOR_TYPE_DEVICE;
		type_device_to_gw_tx_buff[3] = RD_TEMP_HUM_SENSOR_TYPE_DEVICE;
		type_device_to_gw_tx_buff[4] = RD_SHTC3_TEMP_HUM_SENSOR_TYPE_DEVICE;
		type_device_to_gw_tx_buff[5]= 0x00;
		type_device_to_gw_tx_buff[6]= 0x00;
		type_device_to_gw_tx_buff[7]= 0x00;


		mesh_tx_cmd2normal_primary(RD_OPCODE_TYPE_DEVICE_RSP, (u8 *)type_device_to_gw_tx_buff, TYPE_DEVICE_BUFF_LEN, Gw_addr, 2);
	}
	else if(Message_Header==RD_SAVE_GW_ADDR_HEADER){
		Gw_addr=cb_par->adr_src;
		//RD_FlashWriteGwAddr(Gw_addr);  //RD_EDIT: can xem lai cho luu dia chi GW
		type_device_to_gw_tx_buff[0] = (u8)(RD_SAVE_GW_ADDR_HEADER);
		type_device_to_gw_tx_buff[1] = (u8)(RD_SAVE_GW_ADDR_HEADER>>8);
		type_device_to_gw_tx_buff[2] = (u8)(Gw_addr);
		type_device_to_gw_tx_buff[3] = (u8)(Gw_addr>>8);
		type_device_to_gw_tx_buff[4] = 0x00;
		type_device_to_gw_tx_buff[5]=  0x00;
		type_device_to_gw_tx_buff[6]=  0x00;
		type_device_to_gw_tx_buff[7]=  0x00;
		mesh_tx_cmd2normal_primary(RD_OPCODE_TYPE_DEVICE_RSP, (u8 *)type_device_to_gw_tx_buff, TYPE_DEVICE_BUFF_LEN, Gw_addr, 2);
	}
	return 0;
}

int RD_Messenger_Process_Scene(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par){
	uint16_t Message_Header;
	Message_Header = (par[1]<<8)|par[0];
	if(Message_Header==0x0a0a) {
		factory_test_CLD_flag = 1;
	}
	else if(Message_Header==0x0b0b) {
		factory_test_CLD_flag = 0;
	}
	return 0;
}

int RD_Messenger_Process_Null(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par){

	return 0;
}

