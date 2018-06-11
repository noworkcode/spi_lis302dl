#include "init_mcu.h"

uint8_t data_x[256] = {0};
int i =0;

void init_GPIOA(void) 
{
        GPIO_InitTypeDef GPIO_InitStructure_A;
        
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
        
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
        
        GPIO_InitStructure_A.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure_A.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure_A.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure_A.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_InitStructure_A.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
        GPIO_Init(GPIOA, &GPIO_InitStructure_A);
}
void init_GPIOE(void) 
{
        GPIO_InitTypeDef GPIO_InitStructure_E;
        
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
        
        GPIO_InitStructure_E.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure_E.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure_E.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure_E.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_InitStructure_E.GPIO_Pin = GPIO_Pin_3;
        GPIO_Init(GPIOE, &GPIO_InitStructure_E);
        
        CS_OFF();
}
void init_SPI(void) 
{
        SPI_InitTypeDef SPI_InitStructure;
        
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  
        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
        SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
        SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; 
        SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; 
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32; 
        SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
        SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
        SPI_Init(SPI1, &SPI_InitStructure); 
        SPI_Cmd(SPI1, ENABLE);
}

//uint8_t search(void)
//{
//        CS_ON();
//        
//        SPI_I2S_SendData(SPI1, 0x20); 
//        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
//        SPI_I2S_ReceiveData(SPI1);
//        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
//        SPI_I2S_SendData(SPI1, 0x07); 
//        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
//        data = SPI_I2S_ReceiveData(SPI1);
//        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
//        
//        CS_OFF();
//        
//        return data;
//}

uint8_t search_x(void)
{
        CS_ON();
        
        SPI_I2S_SendData(SPI1, 0xA9); 
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        SPI_I2S_ReceiveData(SPI1);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        SPI_I2S_SendData(SPI1, 0x00); 
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        data_x[0] = SPI_I2S_ReceiveData(SPI1);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);       

        CS_OFF();
        
        return data_x[0];
}
