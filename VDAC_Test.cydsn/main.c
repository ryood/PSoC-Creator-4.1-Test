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

#define TITLE_STR1  ("VDAC Test")
#define TITLE_STR2  ("20170722")

int main(void)
{
    char strBuffer[80];
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

    for(;;)
    {
        /* Place your application code here. */
        /*
        sprintf(strBuffer, "%u\r\n", cnt);
        UART_PutString(strBuffer);
        */
        
        Pin_Check1_Write(1);
        VDAC8_1_SetValue(cnt);
        Pin_Check1_Write(0);
        
        cnt++;
    }
}

/* [] END OF FILE */
