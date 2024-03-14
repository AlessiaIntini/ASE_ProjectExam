/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../lib_draw.h"
#include "../Actions.h"
#include "../TouchPanel/TouchPanel.h"
#include "../adc.h"
#include "../RIT.h"

volatile int time=5,battery=0;
volatile int life=0;
volatile int color1=4,color2=4;
volatile int xH=91,xS=219;
volatile int finishBH=0,finishBS=0;
int f=0,g=0;
int cud=0;
int numC=0;
int xM=5,yM=180;

//GESTIONE SUONO
uint16_t SinTable[45] =                                       /*                      */
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};

//unsigned short AD_current;   
//unsigned short AD_last = 0xFF;     /* Last converted value               */


//fai un vettore per ogni suono che deve fare
//const int freqs[8]={4240,3779,3367,3175,2834,2525,2249,2120};
//const int freqs[8]={2120,1890,1684,1592,1417,1263,1125,1062};
const int freqS=4240;																							//S
const int freqA[3]={1890,1684,1592};															//A
const int freqD[5]={1592,1417,1263,1125,1062};										//D
const int freqC[8]={4240,3779,3367,3175,2834,2525,2249,2120};			//C

volatile int selAudio=0;
extern int level;
extern int volume;

/*
262Hz	k=2120		c4
294Hz	k=1890		
330Hz	k=1684		
349Hz	k=1592		
392Hz	k=1417		
440Hz	k=1263		
494Hz	k=1125		
523Hz	k=1062		c5

*/
int down=0;
int notaA=0,notaD=0,notaC=0;
/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


																	
																	
void TIMER0_IRQHandler (void)
{	
  if(getDisplayPoint(&display, Read_Ads7846(), &matrix )){
		if((display.y >80)&&(display.y<280)&&(display.x>20)&&(display.x<240)){
			drawLove(xM,yM);
			cud=1;
			selAudio=4;
		}}
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	//cancelli animazione
		numC++;
		DrawCharacter();
		life++;
		printAge(life);
	
		if(battery==4){
		time--;
		f=SetSnack();
		if(time!=4){
		if(f==0){
		xH=xH-12;
		color1--;
		}else{
			if(color1<4){
			color1++;
			}
			life++;
			
			f=0;
		}}
		if(xH==43){
			finishBH=1;
		}
		Actions_timeSnack(xH,color1);
		
		g=SetMeal();
		if(time!=4){
		if(g==0){
		xS=xS-12;
		color2--;
		}else{
			if(color2<4){
			color2++;
			}
			life++;
			g=0;
		}}
		
		Actions_timeMeal(xS,color2);
		battery=0;
		if(xS==171){
			finishBS=1;
		}
	
	}else{
		battery++;
	 }
		
		if(numC==3){
			numC=0;
			//aggiornamento batteria
			if(cud==1){
			
			if(color1<4){
				color1++;
				}
			incrementBattery_color(xH-9, ReturnColor(color1));
			  xH=xH+12;
				deleteLove();
				yM=180;
				cud=0;
			}
		}else{
			//animazione
			if(cud==1){
				yM=yM-30;
				deleteLove();
				drawLove(xM,yM);
				
			}
		}
	if((finishBH==1)||(finishBS==1)){
		life=0;
		xS=219;
		xH=91;
		color1=4;
		color2=4;
		f=0;
		g=0;
		finishBH=0;
		finishBS=0;
		death();
	}
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}
	
void TIMER2_IRQHandler (void)
{
	static int ticks=0;
	/* DAC management */	
	LPC_DAC->DACR = (SinTable[ticks]<<4)*volume;
	ticks++;
	if(ticks==45) ticks=0;

	
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER3_IRQHandler (void)
{
	
		switch(selAudio){
			case 1:{
								disable_timer(2);
								reset_timer(2);
								init_timer(2,0,0,3,freqS);
								enable_timer(2);
								selAudio=0;
								
								break;
			}	
			case 2:{
								disable_timer(2);
								reset_timer(2);
								init_timer(2,0,0,3,freqA[notaA]);
								enable_timer(2);
								if (notaA==2) {
								notaA=0;
								selAudio=0;}
								else{
								notaA++; 
								}
								
								break;
								}
			
			case  3:{
								disable_timer(2);
								reset_timer(2);
								init_timer(2,0,0,3,freqD[notaD]);
								enable_timer(2);
								if (notaD==4){ 
								notaD=0;
								selAudio=0;}
								else{
								notaD++; 
								}
									break;
								}
			case  4:{
								disable_timer(2);
								reset_timer(2);
								init_timer(2,0,0,3,freqC[notaC]);
								enable_timer(2);
								if (notaC==8){ 
								notaC=0;
								selAudio=0;}
								else{
								notaC++; 
								}
									break;
								
								}
			default: disable_timer(2);
								break;
							}
				
	LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}



/******************************************************************************
**                            End Of File
******************************************************************************/
