/*
 * Sensor_Flash.c
 *
 *  Created on: Jan 28, 2021
 *      Author: Dat UTC
 */



#include"Sensor_Flash.h"
#include "RD_Light_Sensor.h"
RD_SensorSencesStoreTypedef RD_Sence_Store_obj[10];
u8  RD_Sence_Flash_Read_Buff [FLASH_BUFF_LEN];
u8  RD_Reset_Flash_Read_Buff [FLASH_BUFF_LEN];

u8  RD_Sence_Flash_Write_Buff[FLASH_BUFF_LEN];
extern u16 Gw_addr;

void RD_FlashSaveSenceData(u8 *RD_SencePar)
{
    u8 Sence_Number = RD_SencePar[2];
/***************************************************************
 * Mau data luu scene tren cam bien
 */
/*
 * 	RD_Sence_Store_obj[Scene_Number].Header[0] 				= RD_SencePar[0];
 * 	RD_Sence_Store_obj[Scene_Number].Header[1] 				= RD_SencePar[1];
	RD_Sence_Store_obj[Scene_Number].SenceNumberInSensor 	= RD_SencePar[2];
	RD_Sence_Store_obj[Scene_Number].Light_Condition 		= RD_SencePar[3];
	RD_Sence_Store_obj[Scene_Number].PIR_Condition 			= RD_SencePar[4];
	RD_Sence_Store_obj[Scene_Number].LuxLow[0]     			= RD_SencePar[5];
	RD_Sence_Store_obj[Scene_Number].LuxLow[1]     			= RD_SencePar[6];
	RD_Sence_Store_obj[Scene_Number].LuxHight[0]   			= RD_SencePar[7];
	RD_Sence_Store_obj[Scene_Number].LuxHight[1]  			= RD_SencePar[8];
	RD_Sence_Store_obj[Scene_Number].Motion[0]   			= RD_SencePar[9];
	RD_Sence_Store_obj[Scene_Number].Motion[1]				= RD_SencePar[10];
	RD_Sence_Store_obj[Scene_Number].SenceID[0]   			= RD_SencePar[11];
	RD_Sence_Store_obj[Scene_Number].SenceID[1]   			= RD_SencePar[12];
	RD_Sence_Store_obj[Scene_Number].SrgbID   				= RD_SencePar[13];
 */

    RD_SensorSencesStoreTypedef *RD_Sence_Store_pointer;
    RD_Sence_Store_pointer = (RD_SensorSencesStoreTypedef *) RD_SencePar;
    RD_Sence_Store_obj[Sence_Number] = *RD_Sence_Store_pointer;

    RD_Sence_Store_pointer = (RD_SensorSencesStoreTypedef *)RD_Sence_Flash_Write_Buff;
    for(u8 i=0;i<NUMBER_OF_SCENE;i++) *(RD_Sence_Store_pointer+i) = RD_Sence_Store_obj[i];

	flash_erase_sector(SCENE_FLASH_ADDR);
	flash_write_page(SCENE_FLASH_ADDR,FLASH_BUFF_LEN,RD_Sence_Flash_Write_Buff);
	RD_FlashReadSceneData ();

	//BYTE_OF_ONE_SCENE_OBJ
//#define SCENE_STORE_RESPONE  0x4582
//#define GATEWAY_ADDR         0x0001
#define RSP_MAX              2
mesh_tx_cmd2normal_primary(RD_OPCODE_SCENE_RSP,(u8 *)RD_SencePar,BYTE_OF_ONE_SCENE_OBJ, GATEWAY_ADDR, RSP_MAX);

}



void RD_FlashWriteGwAddr(uint16_t addr){
	flash_erase_sector(SCENE_FLASH_ADDR);
	RD_Sence_Flash_Write_Buff[NUMBER_OF_SCENE*BYTE_OF_ONE_SCENE_OBJ]=(u8)(addr>>8);
	RD_Sence_Flash_Write_Buff[NUMBER_OF_SCENE*BYTE_OF_ONE_SCENE_OBJ+1]=(u8)(addr);
	flash_write_page(SCENE_FLASH_ADDR,FLASH_BUFF_LEN,RD_Sence_Flash_Write_Buff);
	RD_FlashReadSceneData ();
}






extern u8 reset_cnt;
void RD_FlashReadSceneData ()
{
	//flash_read_page (FACTORY_RESET_FLASH_ADDR, FLASH_BUFF_LEN, RD_Reset_Flash_Read_Buff);
	flash_read_page (SCENE_FLASH_ADDR, FLASH_BUFF_LEN, RD_Sence_Flash_Read_Buff);

//	reset_cnt = RD_Reset_Flash_Read_Buff[0];

    RD_SensorSencesStoreTypedef *RD_Sence_Store_pointer;
    RD_Sence_Store_pointer = (RD_SensorSencesStoreTypedef *)RD_Sence_Flash_Read_Buff;
	for(u8 i=0;i<NUMBER_OF_SCENE;i++) RD_Sence_Store_obj[i] = *(RD_Sence_Store_pointer + i);

	uint16_t Flash_GwAddr;
	Flash_GwAddr = (RD_Sence_Flash_Read_Buff[NUMBER_OF_SCENE*BYTE_OF_ONE_SCENE_OBJ]<<8)|
					RD_Sence_Flash_Read_Buff[NUMBER_OF_SCENE*BYTE_OF_ONE_SCENE_OBJ+1];
	if(Flash_GwAddr) Flash_GwAddr=Gw_addr;
	else Gw_addr=0x0001;
}

void RD_ClearAllSceneInFlash()
{
	u8 RD_Sence_Flash_Clear_Buff[FLASH_BUFF_LEN] = {0};
	flash_erase_sector(SCENE_FLASH_ADDR);
	flash_write_page(SCENE_FLASH_ADDR,FLASH_BUFF_LEN,RD_Sence_Flash_Clear_Buff);
	RD_FlashReadSceneData ();
}

void RD_ClearSceneInFlash(u8 Scene_Number)
{
	RD_SensorSencesStoreTypedef RD_Clear_scene = {0};
    RD_Sence_Store_obj[Scene_Number]= RD_Clear_scene;

    RD_SensorSencesStoreTypedef *RD_Sence_Store_pointer;
    RD_Sence_Store_pointer = (RD_SensorSencesStoreTypedef *) RD_Sence_Flash_Write_Buff;
    for(u8 i=0;i<NUMBER_OF_SCENE;i++) *(RD_Sence_Store_pointer+i) = RD_Sence_Store_obj[i];

	flash_erase_sector(SCENE_FLASH_ADDR);
	flash_write_page(SCENE_FLASH_ADDR,FLASH_BUFF_LEN,RD_Sence_Flash_Write_Buff);
	RD_FlashReadSceneData ();

}



extern u8 reset_cnt;
void RD_Write_reset_cnt(u8 data)
{
	RD_Factory_Reset_Flash_Write_Buff[0]=data;
	flash_erase_sector(0x23000);
	flash_write_page(0x23000,1,RD_Factory_Reset_Flash_Write_Buff);
	RD_FlashReadSceneData ();
}




