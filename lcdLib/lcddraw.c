/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include "lcdutils.h"
#include "lcddraw.h"


/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
		   u_int colorBGR)
{
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}

void fillTeehee(){
  clearScreen(COLOR_BLACK);
  int i = 0;
  while(i < screenHeight){
    for(int j = 0; j < screenWidth;){
      drawString8x12(j,i,"Teehee",COLOR_RED,COLOR_BLACK);
      j += 52;
    }
    i += 12;
  }
}

// Draws a triangle
void fillTriangle(u_char colMin, u_char rowMin, u_char height, u_int colorBGR){
  for(int row = 1; row < height +1; row++){
    for(int col = 1; col < (row + (row-1)); col++){
      drawPixel((col+colMin)+(height-row), row+rowMin, colorBGR);
    }
  }
}

//draws a circle
void fillCircle(u_char colCen, u_char rowCen, u_char radius, u_int colorBGR){
    int x = radius;
    int y = 0;
    int xChange = 1 - (radius << 1);
    int yChange = 0;
    int radiusError = 0;
    
    while (x >= y){
      for (int i = colCen - x; i <= colCen + x; i++){
	drawPixel(i, rowCen + y, colorBGR);
	drawPixel(i, rowCen - y, colorBGR);
      }
      for (int i = colCen - y; i <= colCen + y; i++){
	drawPixel(i, rowCen + x, colorBGR);
	drawPixel(i, rowCen - x, colorBGR);
      }
      y++;
      radiusError += yChange;
      yChange += 2;
      if (((radiusError << 1) + xChange) > 0){
	x--;
	radiusError += xChange;
	xChange += 2;
      }
    }
  }

void drawFace(){
  fillCircle(screenWidth/2, screenHeight/2 +35, 70, COLOR_YELLOW);
  fillCircle(30, screenHeight/2+15, 27, COLOR_BLACK);
  fillCircle(90, screenHeight/2+15, 27, COLOR_BLACK);
  fillCircle(20, screenHeight/2,10,COLOR_WHITE);
  fillCircle(80, screenHeight/2,10,COLOR_WHITE);
  fillRectangle(20,135,90,3,COLOR_BLACK);
}

void drawMoon(){
  fillCircle(50,50,15,COLOR_PINK);
}

void songBGR(){
  drawString8x12(10,60,"Its pretty", COLOR_GREEN, COLOR_BLUE);
  drawString8x12(30,72,"huh", COLOR_GREEN, COLOR_BLUE);
  fillTriangle(10,10,10,COLOR_YELLOW);
  fillTriangle(30,110,45,COLOR_YELLOW);
  fillTriangle(70,25,25,COLOR_ORANGE);
}
/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR) 
{
  u_char w = screenWidth;
  u_char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 8x12 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar8x12(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_int row = 0;
  u_char bit = 0x80;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 7, rrow + 12); /* relative to requested col/row */
  while (row < 12) {
    while (col < 8) {
      u_int colorBGR = (font_8x12[oc][row] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
      bit >>= 1;
    }
    col = 0;
    bit = 0x80;
    row++;
  }
}

void drawString8x12(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar8x12(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 9;
  }
}


/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar5x7(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */
  while (row < 8) {
    while (col < 5) {
      u_int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

/** Draw string at col,row
 *  Type:
 *  FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString5x7(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar5x7(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 6;
  }
}


/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR)
{
  /**< top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorBGR);
  fillRectangle(colMin, rowMin + height, width, 1, colorBGR);

  /**< left & right */
  fillRectangle(colMin, rowMin, 1, height, colorBGR);
  fillRectangle(colMin + width, rowMin, 1, height, colorBGR);
}

