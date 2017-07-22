/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>

#define TITLE_STR1  ("MCP3008 Test")
#define TITLE_STR2  ("20170721")

char strBuffer[17];

// MCP3008_analogRead(channel)   MCP3008からアナログ値を読み取る処理
//  channel : 読み取るチャンネルを指定する(0-7ch)
int MCP3008_analogRead(int channel)
{
    uint16 d1, d2;
    int ret_val;
    
    // ADCから指定チャンネルのデータを読み出す
    SPIM_WriteTxData(0x01);
    SPIM_WriteTxData(0x80 | ((channel & 0x07) << 4));
    d1 = SPIM_ReadRxData();
    SPIM_WriteTxData(0x00); // dummy
    d2 = SPIM_ReadRxData();
    
    while (! (SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE))
        ;
    /*    
    LCD_Position(0, 0);
    sprintf(strBuffer, "%3d %3d      ", d1, d2);
    LCD_PrintString(strBuffer);
    */
    
    ret_val = ((d2 & 0x03) << 8) | d1; 
    
    return ret_val;
}

#if 0
// MCP3208_analogRead(channel)   MCP3208からアナログ値を読み取る処理
//  channel : 読み取るチャンネルを指定する(0-7ch)
int MCP3208_analogRead(int channel)
{
    uint16 d1, d2;
    int ret_val;
    
    // ADCから指定チャンネルのデータを読み出す
    SPIM_WriteTxData(0x06 | (channel >> 2));
    SPIM_WriteTxData(channel << 6);
    d1 = SPIM_ReadRxData();
    SPIM_WriteTxData(0x00); // dummy
    d2 = SPIM_ReadRxData();
    
    while (! (SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE))
        ;
    
    /*
    LCD_Position(0, 0);
    sprintf(strBuffer, "%3d %3d      ", d1, d2);
    LCD_PrintString(strBuffer);
    */
    
    ret_val = ((d2 & 0x0f) << 8) | d1; 
    
    return ret_val;
}
#endif

int main(void)
{
    uint8 cnt = 0;
    int ADC_v[8];
    int i;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_Start();
    UART_Start();
    SPIM_Start();
    
    LCD_Position(0u,0u);
    LCD_PrintString(TITLE_STR1);
    LCD_Position(1u,0u);
    LCD_PrintString(TITLE_STR2);
    
    UART_PutString("\r\n");
    UART_PutString(TITLE_STR1);
    UART_PutString("\t");
    UART_PutString(TITLE_STR2);
    UART_PutString("\r\n");
    
    CyDelay(1000u);
    LCD_ClearDisplay();

    for(;;)
    {
        Pin_Check1_Write(1);
        //
        // 複数チャンネルの読み取りがうまくいかない。
        //
        for (i = 0; i < 8; i++) {
            ADC_v[i] =  MCP3008_analogRead(i);
        }
        Pin_Check1_Write(0);
        
        /* Place your application code here. */
        sprintf(strBuffer, "%d\t", cnt);
        UART_PutString(strBuffer);
        for (i = 0; i < 8; i++) {       
            sprintf(strBuffer, "%6d\t", ADC_v[i]);        
            UART_PutString(strBuffer);
        }
        UART_PutString("\r\n");
        
        cnt++;
        
        CyDelay(100);
    }
}

/* [] END OF FILE */
