/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "lib_draw.h"
#include "GLCD/GLCD.h" 
#include "Actions.h"
#include "timer/timer.h"
#include "adc.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


volatile char select=' ';
extern int selAudio;


void RIT_IRQHandler (void)
{
	
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
		switch(select){
			case 'L':{ 
								disable_RIT();
								meal();
								enable_RIT( );
								select=' ';
								break;
			}
			case 'R':{
								disable_RIT();
								snack();
								enable_RIT( );
								select=' ';
								break;
			}
			case 'D':{
								DisegnaRett(0,280,240,320,Red);
								disable_RIT();
								enable_timer(1);
								LCD_ClearWindow();
								resetCharacter();
								setGame();
								break;		
								
			}
			default: break;
		}
	}else if(((LPC_GPIO1->FIOPIN & (1<<27)) == 0)&&select!='D'){	//left
		select='L';
		selAudio=1;
		DisegnaRett(0,280,120,320,Red);
		DisegnaRett(120,280,240,320, Black);
	}else if(((LPC_GPIO1->FIOPIN & (1<<28)) == 0)&&select!='D'){	//right
		select='R';
		selAudio=1;
		DisegnaRett(0,280,120,320,Black);
		DisegnaRett(120,280,240,320,Red);
	}						
		

	ADC_start_conversion();
 LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}


/******************************************************************************
**                            End Of File
******************************************************************************/
