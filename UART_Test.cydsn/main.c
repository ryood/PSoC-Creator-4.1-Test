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

int main(void)
{
    char strBuffer[80];
    int cnt = 0;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_1_Start();

    for(;;)
    {
        /* Place your application code here. */
        Pin_LED_Write(1);
        CyDelay(100);
        
        sprintf(strBuffer, "%d\r\n", cnt);
        UART_1_PutString(strBuffer);
        cnt++;
        
        Pin_LED_Write(0);
        CyDelay(100);
    }
}

/* [] END OF FILE */
