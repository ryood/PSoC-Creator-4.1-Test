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

int main(void)
{
    uint8 cnt = 0;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    SPIM_Start();

    for(;;)
    {
        SPIM_WriteTxData(cnt);
        while (! (SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE))
            ;
        
        cnt++;
    }
}

/* [] END OF FILE */
