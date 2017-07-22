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

#define TITLE_STR1  ("MCP4922 Test")
#define TITLE_STR2  ("20170719")

char strBuffer[17];

int main(void)
{
    uint16 cnt = 0;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_Start();
    SPIM_Start();
    
    LCD_Position(0u,0u);
    LCD_PrintString(TITLE_STR1);
    LCD_Position(1u,0u);
    LCD_PrintString(TITLE_STR2);
    
    CyDelay(1000u);
    //LCD_ClearDisplay();

    for(;;)
    {
        Pin_Check1_Write(1);
        
        SPIM_WriteTxData((cnt >> 8) | 0x30);
        SPIM_WriteTxData(cnt & 0xff);
        while (! (SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE))
            ;
        
        Pin_Check1_Write(0);
        
        /*        
        LCD_Position(1, 0);
        sprintf(strBuffer, "%3d", cnt);
        LCD_PrintString(strBuffer);
        */
        
        cnt++;
        if (cnt > 4096) {
            cnt = 0;
        }
        
        //CyDelay(1);
    }
}

/* [] END OF FILE */
