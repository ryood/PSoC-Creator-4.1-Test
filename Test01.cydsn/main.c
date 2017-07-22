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
#include "stdio.h"

#define TITLE_STR1  ("Char LCD Test")
#define TITLE_STR2  ("20170718")

int main(void)
{
    char strBuffer[80];
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_Char_1_Start();
    LCD_Char_1_PrintString(TITLE_STR1);
    LCD_Char_1_Position(1, 0);
    LCD_Char_1_PrintString(TITLE_STR2);
    
    CyDelay(1000);
        
    int cnt = 0;
    for(;;)
    {
        /* Place your application code here. */
        sprintf(strBuffer, "%8d", cnt);
        LCD_Char_1_Position(1, 8);
        LCD_Char_1_PrintString(strBuffer);
        cnt++;
        
        CyDelay(1000);
    }
}

/* [] END OF FILE */
