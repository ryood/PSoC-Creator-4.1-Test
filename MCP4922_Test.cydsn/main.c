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
#include <math.h>

#define TITLE_STR1  ("MCP4922 Test")
#define TITLE_STR2  ("20170722")

#define PI        (3.141592653589793238462)
#define AMPLITUDE (1.0)    // x * 3.3V
#define PHASE     (PI * 1) // 2*pi is one period
#define RANGE     (0x7FFF)
#define OFFSET    (0x7FFF)

// Configuration for wave output
#define BUFFER_SIZE (360)
uint16_t buffer_sine[BUFFER_SIZE];

char strBuffer[80];
    
// Create the wave buffer
void calculate_sinewave(void){
    for (int i = 0; i < BUFFER_SIZE; i++) {
	    double rads = (PI * i)/180.0; // Convert degree in radian
	    buffer_sine[i] = (uint16_t)(AMPLITUDE * (RANGE * (sin(rads + PHASE))) + OFFSET);
    }
}

// Write to MCP4922
// v: 0..4096
void MCP4922_write_u16(uint16 v)
{
    SPIM_WriteTxData((v >> 8) | 0x30);
    SPIM_WriteTxData(v & 0xff);
    while (! (SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE))
        ;
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_Start();
    SPIM_Start();
    UART_Start();
    
    LCD_Position(0u,0u);
    LCD_PrintString(TITLE_STR1);
    LCD_Position(1u,0u);
    LCD_PrintString(TITLE_STR2);
    
    sprintf(strBuffer, "%s %s \r\n", TITLE_STR1, TITLE_STR2);
    UART_PutString(strBuffer);
    
    CyDelay(1000u);
    //LCD_ClearDisplay();
    
    calculate_sinewave();
    
    /*
    for (int i = 0; i < BUFFER_SIZE; i++) {
        sprintf(strBuffer, "%u\r\n", buffer_sine[i]);
        UART_PutString(strBuffer);
    }    
    UART_PutString("Dump end\r\n");
    */

    for(;;)
    {
        for (int i = 0; i < BUFFER_SIZE; i++) {
            Pin_Check1_Write(1);
            MCP4922_write_u16(buffer_sine[i] >> 4);
            Pin_Check1_Write(0);
        }
        //CyDelay(1);
    }
}

/* [] END OF FILE */
