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

#define TITLE_STR1  ("SPI Master Test")
#define TITLE_STR2  ("20170719")

int main(void)
{
    char strBuffer[17];
    uint8 cnt = 0;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_Start();
    SPIM_Start();
    
    LCD_Position(0u,0u);
    LCD_PrintString(TITLE_STR1);
    LCD_Position(1u,0u);
    LCD_PrintString(TITLE_STR2);
    
    CyDelay(1000u);

    for(;;)
    {
        /* Place your application code here. */
        /*
        LCD_Char_1_Position(1, 0);
        sprintf(strBuffer, "%d", cnt);
        LCD_Char_1_PrintString(strBuffer);
        */

        SPIM_WriteTxData(cnt);
        while (! (SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE))
            ;
        
        cnt++;

        //CyDelay(1);
    }
}

/* [] END OF FILE */
