#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "joystick.h"
#include "RIT.h"
#include "Actions.h"
#include "lib_draw.h"
#include "timer/timer.h"
volatile int xCorr1,xCorr2;
volatile uint16_t colorS;
volatile uint16_t colorM;
volatile int currS=0, currM=0;
extern char select;
extern int selAudio;

//fai partire il timer0, disegni e poi nel timer0 cancelli il disegno per sempre

int Actions_timeSnack(int xH,int time){
	//deve cancellare la batteria
	colorS=ReturnColor(time);
	xCorr1=xH;
	deleteBattery(xH);
		return 1;
}
int Actions_timeMeal(int xS,int time){
	//deve cancellare la batteria
	
	colorM=ReturnColor(time);
	xCorr2=xS;
	deleteBattery(xS);
	
		return 1;
}

int SetSnack(){
	if(currS==1){
		currS=0;
	return 1;
	
	}else{
		return 0;
	}
}
int SetMeal(){
	if(currM==1){
		currM=0;
	return 1;
	
	}else{
		return 0;
	}
}

void snack(void){
		currS=1;
		disable_timer(1);
		drawSnack();
		moveCharacter();
		incrementBattery_color(xCorr1-9,colorS);
		deleteAction();
		enable_timer(1);
		selAudio=2;
	//incrementare la batteria
	return;
}

void meal(void){
		currM=1;
		disable_timer(1);
		drawMeal();
		moveCharacter();
		incrementBattery_color(xCorr2-9,colorM);
		deleteAction();
		enable_timer(1);
		selAudio=2;
	return;
}
void death(void){
	select='D';
	deleteCharacter();
	drawDeath();
	LCD_DrawLine( 0,  280,  240, 280 , Black );
	GUI_Text(100, 300, (uint8_t *) "RESET ", Black, White);
	disable_timer(1);
	selAudio=3;
}

void cuddles(void){
	int i;
	int xM=5,yM=180;
	for(i=0;i<2;i++){
	drawLove(xM,yM);
	deleteLove();
	yM=yM-30;
	}

}


