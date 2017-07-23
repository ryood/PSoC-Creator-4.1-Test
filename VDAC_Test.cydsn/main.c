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

#define TITLE_STR1  ("VDAC Test")
#define TITLE_STR2  ("20170723")

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

int main(void)
{
    uint8_t cnt = 0;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_Char_Start();
    UART_Start();
    VDAC8_1_Start();
    Opamp_1_Start();
    
    LCD_Char_PrintString(TITLE_STR1);
    LCD_Char_Position(1, 0);
    LCD_Char_PrintString(TITLE_STR2);
    
    sprintf(strBuffer, "\r\n%s %s\r\n", TITLE_STR1, TITLE_STR2);
    UART_PutString(strBuffer);

    calculate_sinewave();
    
    for(;;)
    {
        /* Place your application code here. */
        for (int i = 0; i < BUFFER_SIZE; i++) {
            Pin_Check1_Write(1);
            VDAC8_1_SetValue(buffer_sine[i] >> 8);
            Pin_Check1_Write(0);
        }
        
        cnt++;
    }
}

/* [] END OF FILE */
