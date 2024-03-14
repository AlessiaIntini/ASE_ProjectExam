#ifndef __lib_draw_H
#define __lib_draw_H

void DrawCharacter(void);
void DrawBackground(void);
void DrawBattery(void);
void incrementBattery(int x);
void deleteBattery(int x);
void drawMeal(void);
int ReturnColor(int time);
void deleteAction(void);
void drawSnack(void);
void incrementBattery_color(int x,int color);
void printAge(int life);
void deleteCharacter(void);
void drawDeath(void);
void moveCharacter(void);
void deleteAll(void);
void setGame(void);
void resetCharacter(void);
void drawLove(int xM,int yM);
void deleteLove(void);
void drawAudio(void);
void drawB(int x);
void deleteB(int x);
#endif
