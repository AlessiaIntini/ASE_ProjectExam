#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "joystick.h"
#include "RIT.h"
#include "GLCD/AsciiLib.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

uint16_t MatriceSchermo[42][30]={	White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,White,White,White,Black,Black,Black,Black,White,White,White,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,White,White,Black,White,White,White,White,Black, White,White,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,White,White,Black,White,White,White,White,Black, White,White,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,White,Black,White,Magenta,White,White,Magenta,White,Black, White,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,White,Black,White,Magenta,White,White,Magenta,White,Black, White,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,Black,Black,Magenta,Magenta,White,White,Magenta,Magenta,Black, Black,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,Black,Black,White,White,White,White,White,White,Black, Black,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,Black,Black,Black,Black,White,White,Black,Black,Black,Black, White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,Black,Black,White,White,White,White,White,White,Black, Black,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,Black,Black,Magenta,Magenta,White,White,Magenta,Magenta,Black,Black,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,Black,Black,Magenta,Magenta,White,White,Magenta,Magenta,Black,Black,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,White,Black,Black,Magenta,Magenta,White,White,Magenta,Magenta,Black,Black,White,White,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,White,Black,Black,Black,White,Magenta,White,White,Magenta,White,Black,Black,Black, White,White,White,White,White,White,White,White, 
																	 White,White,White,White,White,White,White,White,White,Black,Black,Black,Black,White,White,White,White,White,White,Black,Black,Black,Black,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,Black,Black,Black,Black,White,White,White,White,White,White,Black,Black,Black,Black,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,Black,Black,Black,Black,White,White,Black,Black,White,White,Black,Black,Black,Black,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,Black,Black,Black,Black,White,White,Black,Black,White,White,Black,Black,Black,Black,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,White,Black,Black,Black,Black,Black,White,White,White,White,Black,Black,Black,Black,Black,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,Black,Black,Black,Black,Black,Black,White,White,White,White,Black,Black,Black,Black,Black,White,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,Black,Black,Black,Black,Black,Black,White,White,White,White,Black,Black,Black,Black,Black,Black,White,White,White,White,White,White,
																	 White,White,White,White,White,White,White,White,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,White,White,White,White,White,White,
																	White,White,White,White,White,White,White,White,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,White,White,White,White,White,White,
																	White,White,White,White,White,White,White,White,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,Black,White,White,White,White,White,White,
																	
																	White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,
																	White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White,White
																	
																	};
uint16_t colorBattery[5]={Red,Maroon,Yellow,Green,Green};
uint16_t	love[10][10]={
                       White, White, White, White, White, White, White, White, White, White, 
                       White, White, White, White, White, White, White, White, White, White, 
                       White, White, White, White, White, White, White, White, White, White, 
                       White, White, Red, White, Red, White, White, White, White, White, 
                       White, White, Red, Red, Red, White, White, White, White, White, 
                       White, White, White, Red, White, White, Red, White, Red, White, 
                       White, White, White, White, White, White, Red, Red, Red, White, 
                       White, White, White, White, White, White, White, Red, White, White, 
                       White, White, White, White, White, White, White, White, White, White, 
											 White, White, White, White, White, White, White, White, White, White, 
                       };
volatile int flag=0,j=0;



void DrawCharacter(){
	int y,x,xM,yM;
	uint16_t var=White;
for(y=0;y<30;y++){
	for(x=0;x<42;x++){
	if(MatriceSchermo[x][y]!=var){
	DisegnaPixel(xM,yM,(xM+8),(yM+8),MatriceSchermo[x][y]);}
		else{
		if(((x==25)&&(y==15))||((x==25)&&(y==16))||((x==28)&&(y==15))||((x==28)&&(y==16))){
			DisegnaPixel(xM,yM,(xM+8),(yM+8),MatriceSchermo[x][y]);
		}
		
	}
		yM=yM+8;
}
	xM=xM+8;
	yM=0;
}
if(flag==0){
	MatriceSchermo[25][15]=Black;
	MatriceSchermo[25][16]=Black;
	MatriceSchermo[28][15]=Black;
	MatriceSchermo[28][16]=Black;
	flag=1;
}else{
	MatriceSchermo[25][15]=White;
	MatriceSchermo[25][16]=White;
	MatriceSchermo[28][15]=White;
	MatriceSchermo[28][16]=White;
	flag=0;
}
}

void DrawBackground(){
	//barra sopra
	GUI_Text(32, 20, (uint8_t *) "HAPPINES ", Black, White); //scrive questa informazione in una data posizione, con colore del testo e di background
	GUI_Text(160, 20, (uint8_t *) "SATIETY ", Black, White);
	
	//BARRA SOTTO
	LCD_DrawLine( 0,  280,  240, 280 , Black );
	LCD_DrawLine( 120,  280,  120, 320 , Black );
	GUI_Text(48, 300, (uint8_t *) "MEAL ", Black, White); //scrive questa informazione in una data posizione, con colore del testo e di background
	GUI_Text(156, 300, (uint8_t *) "SNACK ", Black, White);
}

void DrawBattery(){
//batterie
//width=60
//hight=27
	DisegnaRett(32, 45, 92, 75,Black);
	DisegnaPixel(92, 52, 97, 68,Black);

	DisegnaRett(160, 45, 220, 75,Black);
	DisegnaPixel(220, 52, 225, 68,Black);
}

void incrementBattery(int x){
	int i;
	for(i=0;i<5;i++){
	DisegnaPixel(x, 48, x+9, 73,colorBattery[i]);
		x=x+12;
	}

}

void incrementBattery_color(int x,int color){
DisegnaPixel(x, 48, x+9, 73,color);
}

void deleteBattery(int x){
	
	DisegnaPixel(x-9, 48, x, 73,White);
}

void drawMeal(){
	int x,y=180;
	for(x=5;x<35;x++){
		LCD_SetPoint(x,y,Black);
		y--;
		}
	LCD_DrawLine(33,150,50,180,Black);
	LCD_DrawLine(5,180,60,180,Black);
	DisegnaPixel(25,165,35,180,Black);
	
}
void deleteAction(){
	int x,y;
	for(x=0;x<150;x=x+8){
		for(y=80;y<270;y=y+8){
			DisegnaPixel(x,y,x+8,y+8,White);
		}}
	
	
	
}
int ReturnColor(int time){
return colorBattery[time];
}

void drawSnack(){

	DisegnaPixel(5,150,40,200,Maroon);
	 
	LCD_DrawLine(5,165,40,165,Black);
	LCD_DrawLine(5,185,40,185,Black);
	LCD_DrawLine(18,150,18,200,Black);
	LCD_DrawLine(32,150,32,200,Black);

}


void printAge(int life){
	char time[5];
	int hours=0,min=0,sec=0;
	if(life>59){
	sec=life%60;
	min=life/60;
	min=life%60;
	hours=life/3600;
	}else{
		sec=life;
	}
	sprintf(time,"%02d:%02d:%02d",hours,min,sec);
	GUI_Text(90, 0, (uint8_t *) time ,Black, White);
	
}

void deleteCharacter(){
	int x,y;
	for(x=0;x<240;x=x+8){
		for(y=80;y<320;y=y+8){
			DisegnaPixel(x,y,x+8,y+8,White);
		}}
}

void drawDeath(void){
	int y,x,xM,yM;
	uint16_t var=White, var2=Magenta;
	
for(y=0;y<30;y++){
	for(x=0;x<42;x++){
		if(MatriceSchermo[x][y]==var2){
			MatriceSchermo[x][y]=Grey;
		}
	if(MatriceSchermo[x][y]!=var){
	DisegnaPixel(xM,yM,(xM+8),(yM+8),MatriceSchermo[x][y]);}
		yM=yM+8;
}
	xM=xM+8;
	yM=0;
}
	LCD_DrawCircle(45,160,40,Black);
	GUI_Text(30, 150, (uint8_t *) "GAME" ,Black, White);
	GUI_Text(30, 170, (uint8_t *) "OVER" ,Black, White);
}

void moveCharacter(void){
	int x,y,xM=0,yM=80;
	
		for(x=50;x<200;x=x+8){
		for(y=80;y<270;y=y+8){
			DisegnaPixel(x,y,x+8,y+8,White);
		}}
	//per aprire la bocca
	MatriceSchermo[25][15]=Black;
	MatriceSchermo[25][16]=Black;
	MatriceSchermo[28][15]=Black;
	MatriceSchermo[28][16]=Black;
	//fino a posizione 7, tutte le righe
	for(y=9;y<25;y++){
		for(x=11;x<34;x++){
		DisegnaPixel(xM,yM,(xM+8),(yM+8),MatriceSchermo[x][y]);
			yM=yM+8;
		}
		yM=80;
		xM=xM+8;
	}
		
	MatriceSchermo[25][15]=White;
	MatriceSchermo[25][16]=White;
	MatriceSchermo[28][15]=White;
	MatriceSchermo[28][16]=White;
}
void deleteAll(void){
	int x,y;
	for(x=0;x<240;x=x+8){
		for(y=0;y<320;y=y+8){
			DisegnaPixel(x,y,x+8,y+8,White);
		}}
}

void drawB(int x){
			if(x==3){
			DisegnaPixel(23,6,26,15,Black);
			DisegnaPixel(29,4,33,17,Black);
			DisegnaPixel(36,2,40,19,Black);
			}
			if(x==2){
			DisegnaPixel(23,6,26,15,Black);
			DisegnaPixel(29,4,33,17,Black);
			}
			if(x==1){
			DisegnaPixel(23,6,26,15,Black);
			}
}


void drawAudio(void){
	int i;
 DisegnaPixel(7,5,17,15,Black);
 for(i=0;i<5;i++){
	 LCD_DrawLine(17+i,5-i,17+i,15+i,Black);
 }

}

void deleteB(int x){
	if(x==0){
			DisegnaPixel(23,6,26,15,White);
			DisegnaPixel(29,4,33,17,White);
			DisegnaPixel(36,2,40,19,White);
	}
	if(x==1){
		DisegnaPixel(29,4,33,17,White);
		DisegnaPixel(36,2,40,19,White);
	}
	if(x==2){
			DisegnaPixel(29,4,33,17,White);
			DisegnaPixel(36,2,40,19,White);
	}
}


void setGame(void){
	
	LCD_Clear(White);
	DrawBackground();
	DrawCharacter();
	GUI_Text(60, 0, (uint8_t *) "Age",Black, White);
	DrawBattery();
	incrementBattery(34);
	incrementBattery(162);
	drawAudio();
	enable_RIT();
}

void resetCharacter(void){
	int x,y;
	int var=Grey;
	
	for(y=0;y<30;y++){
	for(x=0;x<42;x++){
		if(MatriceSchermo[x][y]==var){
			MatriceSchermo[x][y]=Magenta;
		}
	}
}
	}

	//primi xM=5 e yM=180
void drawLove(int xM,int yM){
		int i,j;
		int x=xM,y=yM;
	
		
		for(i=2;i<10;i++){
			for(j=0;j<10;j++){
				if(love[j][i]!=White){
					DisegnaPixel(x,y,(x+8),(y+8),love[j][i]);
				}
				y=y+8;
			}
		y=yM;
		x=x+8;}
	}
		
void deleteLove(void){
	int x,y;
	
	for(x=5;x<60;x=x+8){
		for(y=140;y<240;y=y+8){
			DisegnaPixel(x,y,x+8,y+8,White);
		}}
	
}	


		

