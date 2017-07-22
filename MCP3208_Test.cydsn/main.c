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

#define TITLE_STR1  ("MCP3208 Test")
#define TITLE_STR2  ("20170719")

char strBuffer[17];

// ADC_analogRead(channel)   MCP3208からアナログ値を読み取る処理
//  channel : 読み取るチャンネルを指定する(0-7ch)
int ADC_analogRead(int channel)
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

int main(void)
{
    uint8 cnt = 0;
    int ADC_v;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_Start();
    SPIM_Start();
    
    LCD_Position(0u,0u);
    LCD_PrintString(TITLE_STR1);
    LCD_Position(1u,0u);
    LCD_PrintString(TITLE_STR2);
    
    CyDelay(1000u);
    LCD_ClearDisplay();

    for(;;)
    {
        Pin_Check1_Write(1);
        ADC_v =  ADC_analogRead(0);
        Pin_Check1_Write(0);
        
        /* Place your application code here. */
        LCD_Position(1, 0);
        sprintf(strBuffer, "%3d %6d", cnt, ADC_v);
        LCD_PrintString(strBuffer);
        
        cnt++;
        
        //CyDelay(1);
    }
}

/* [] END OF FILE */
