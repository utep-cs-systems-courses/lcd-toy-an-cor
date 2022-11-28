#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "buzzer.h"


void update_shape();
void song1();
void song2();
void song3();
void song4();
void song5();
void start_screen();
void choose_song();
unsigned short rand = 0;
int BG_COLOR = COLOR_BLUE;
void main()
{
  P1DIR |= LED;/**< Green led on when CPU on */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  buzzer_init();
  switch_init();
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);              /**< GIE (enable interrupts) */
  clearScreen(BG_COLOR);
  while (1) {/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      update_shape();
    }
    P1OUT &= ~LED;/* led off */
    or_sr(0x10);/**< CPU OFF */
    P1OUT |= LED;/* led on */
  }
}
//square size
static unsigned int size = screenWidth/3;

//buzzer sounds for kick, right, left
static short a5S = 880;
static short b5S = 988;
static short c6S = 1047;
static short d6S = 1175;
static short e6S = 1318;
static short f6S = 1397;
static short g6S = 1568;
static short a6S = 1760;
static short b6S = 1976;
static short c7S = 2093;

static short kickS = 700;
static short rightS = 1000;
static short leftS = 1300;

//holds which switch was last pressed
static unsigned char sw1pressed = 0;
static unsigned char sw2pressed = 0;
static unsigned char sw3pressed = 0;
static unsigned char sw4pressed = 0;
static unsigned char nopressed =  1;
    
void update_shape()
{
  //if it's been at least 30 seconds without any interaction go to start screen
  if(secondsW >= 30 || nopressed){
    sw1pressed = 0;
    sw2pressed = 0;
    sw3pressed = 0;
    sw4pressed = 0;
    nopressed = 1;
    start_screen();
  }
  //when switch 1 is pressed
  if (switches & SW1){
    clearScreen(COLOR_BLUE);
    sw1pressed = 1;
    sw2pressed = 0;
    sw3pressed = 0;
    sw4pressed = 0;
    nopressed = 0;
    secondsW = 0;
    
  }
  //when switch 2 is pressed
  if (switches & SW2){
    clearScreen(COLOR_BLUE);
    sw1pressed = 0;
    sw2pressed = 1;
    sw3pressed = 0;
    sw4pressed = 0;
    nopressed = 0;
    secondsW = 0;
    
  }
  //when switch 3 is pressed
  if (switches & SW3){
    clearScreen(COLOR_BLUE);
    sw1pressed = 0;
    sw2pressed = 0;
    sw3pressed = 1;
    sw4pressed = 0;
    nopressed = 0;
    secondsW = 0;
    
  }
  //when switch 4 is pressed
  if (switches & SW4){
    clearScreen(COLOR_BLUE);
    sw1pressed = 0;
    sw2pressed = 0;
    sw3pressed = 0;
    sw4pressed = 1;
    nopressed = 0;
    secondsW = 0;
  }
    choose_song();
}
//choose song state machine that corresponds to the switch pressed
void choose_song(){
  if(sw1pressed){
    song1();
  }
  else if(sw2pressed){
    song2();
  }
  else if(sw3pressed){
    song3();
  }
  else if(sw4pressed){
    song4();
  }
}
//song: twinkle twinkle little star
void song1(){
  static unsigned char state = 0;
  switch(state){
  case 0://C
    clearScreen(COLOR_RED);
    fillRectangle(0,screenHeight/3,size,size,color_picker(secondsW));
    buzzer_set_period(c6S);
    state = 1;
    break;
  case 1://quiet
    fillRectangle(0,screenHeight/3,size,size,COLOR_RED);//clear screen
    turn_buzzer_off();//shut off buzzer
    state = 2;
    break;
  case 2://C
    fillRectangle(0,screenHeight/3,size,size,color_picker(secondsW));
    buzzer_set_period(c6S);
    state = 3;
    rand +=2;
    break;
  case 3://quiet
    fillRectangle(0,screenHeight/3,size,size,COLOR_RED);
    turn_buzzer_off();
    state = 4;
    break;
  case 4://G
    fillRectangle(screenWidth*2/3,screenHeight/3,size,size,color_picker(secondsW));
    buzzer_set_period(g6S);
    state = 5;
    break;
  case 5://quiet
    fillRectangle(screenWidth*2/3,screenHeight/3,size,size,COLOR_RED);
    turn_buzzer_off();
    rand ^=49;
    state = 6;
    break;
  case 6://G
    fillRectangle(screenWidth*2/3,screenHeight/3,size,size,color_picker(secondsW));
    buzzer_set_period(g6S);
    state = 7;
    break;
  case 7://quiet
    fillRectangle(screenWidth*2/3,screenHeight/3,size,size,COLOR_RED);
    turn_buzzer_off();
    state = 8;
    break;
  case 8://A
    fillRectangle(screenWidth/3,screenHeight/3,size,size,color_picker(secondsW));
    buzzer_set_period(a6S);
    state = 9;
    break;
  case 9://quiet
    fillRectangle(screenWidth/3,screenHeight/3,size,size,COLOR_RED);
    turn_buzzer_off();
    rand ^=49;
    state = 10;
    break;
  case 10://A
    fillRectangle(screenWidth/3,screenHeight/3,size,size,color_picker(secondsW));
    buzzer_set_period(a6S);
    state = 11;
    break;
  case 11://quiet
    fillRectangle(screenWidth/3,screenHeight/3,size,size,COLOR_RED);
    turn_buzzer_off();
    state = 12;
    break;
  case 12://G
    fillRectangle(screenWidth*2/3,screenHeight/3,size,size,color_picker(secondsW));
    buzzer_set_period(g6S);
    state = 13;
    break;
  case 13://G
    fillRectangle(screenWidth*2/3,screenHeight/3,size,size,color_picker(secondsW));
    buzzer_set_period(g6S);
    state = 14;
    break;
  case 14://quiet
    fillRectangle(screenWidth*2/3,screenHeight/3,size,size,COLOR_RED);
    turn_buzzer_off();
    state = 0;
    break;
  }
}
//song: mystery tone
void song2(){
  static unsigned char state = 0;
  switch(state){
  case 0://E
    clearScreen(COLOR_STEEL_BLUE);
    fillRectangle(0,0,size,size,color_picker(secondsW));
    buzzer_set_period(e6S);
    state = 1;
    break;
  case 1://G
    clearScreen(COLOR_STEEL_BLUE);
    fillRectangle(0,screenHeight-40,size,size,color_picker(secondsW));
    buzzer_set_period(g6S);
    state = 2;
    rand +=2;
    break;
  case 2://C
    clearScreen(COLOR_STEEL_BLUE);
    fillRectangle(screenWidth-40,screenHeight-40,size,size,color_picker(secondsW));
    buzzer_set_period(c6S);
    state = 3;
    break;
  case 3://D
    clearScreen(COLOR_STEEL_BLUE);
    fillRectangle(screenWidth-40,0,size,size,color_picker(secondsW));
    buzzer_set_period(d6S);
    state = 4;
    break;
  case 4://F
    clearScreen(COLOR_STEEL_BLUE);
    fillRectangle((screenWidth/2)-20,(screenHeight/2)-20,size,size,color_picker(secondsW));
    buzzer_set_period(f6S);
    state = 0;
    break;
  }
}

//song: siren
void song3(){
  static unsigned char state = 0;
  unsigned int current_color = COLOR_RED;
  switch(state){
  case 0://right
    clearScreen(COLOR_LIME_GREEN);
    drawString5x7(screenWidth/2-10,screenHeight/4,"WEE",COLOR_BLACK,COLOR_LIME_GREEN);
    fillRectangle(0,0,size,size,COLOR_LIME_GREEN);
    fillRectangle(0,screenHeight/3,size,size,COLOR_LIME_GREEN);
    fillRectangle(0,screenHeight*2/3,size,size,COLOR_LIME_GREEN);
    current_color = color_picker(secondsW);
    fillRectangle(screenWidth*2/3,0,size,size,current_color);
    fillRectangle(screenWidth*2/3,screenHeight/3,size,size,current_color);
    fillRectangle(screenWidth*2/3,screenHeight*2/3,size,size,current_color);
    buzzer_set_period(rightS);
    state = 1;
    break;
  case 1://left
    clearScreen(COLOR_LIME_GREEN);
    drawString5x7(screenWidth/2-10,screenHeight*3/4,"WOO",COLOR_BLACK,COLOR_LIME_GREEN);
    fillRectangle(screenWidth*2/3,0,size,size,COLOR_LIME_GREEN);
    fillRectangle(screenWidth*2/3,screenHeight/3,size,size,COLOR_LIME_GREEN);
    fillRectangle(screenWidth*2/3,screenHeight*2/3,size,size,COLOR_LIME_GREEN);
    current_color = color_picker(secondsW);
    fillRectangle(0,0,size,size,current_color);
    fillRectangle(0,screenHeight/3,size,size,current_color);
    fillRectangle(0,screenHeight*2/3,size,size,current_color);
    buzzer_set_period(leftS);
    rand +=7;
    state = 0;
    break;
  }
}

//song: Hot Cross Buns
void song4(){
  static unsigned char state = 0;
  switch(state){
  case 0://E
    clearScreen(COLOR_HOT_PINK);
    drawString5x7(screenWidth/2,screenHeight/4,"HOT",COLOR_BLACK,COLOR_HOT_PINK);
    fillRectangle(0,0,size,size,color_picker(secondsW));
    buzzer_set_period(e6S);
    state = 1;
    break;
  case 1://E
    clearScreen(COLOR_HOT_PINK);
    drawString5x7(screenWidth/2,screenHeight/4,"HOT",COLOR_BLACK,COLOR_HOT_PINK);
    fillRectangle(0,0,size,size,color_picker(secondsW));
    buzzer_set_period(e6S);
    state = 2;
    break;
  case 2://D
    clearScreen(COLOR_HOT_PINK);
    drawString5x7(screenWidth/2,screenHeight/4,"CROSS",COLOR_BLACK,COLOR_HOT_PINK);
    fillRectangle(screenWidth*2/3,screenHeight/3,size,size,color_picker(secondsW));
    buzzer_set_period(d6S);
    state = 3;
    rand +=2;
    break;
  case 3://D
    clearScreen(COLOR_HOT_PINK);
    drawString5x7(screenWidth/2,screenHeight/4,"CROSS",COLOR_BLACK,COLOR_HOT_PINK);
    fillRectangle(screenWidth*2/3,screenHeight/3,size,size,color_picker(secondsW));
    buzzer_set_period(d6S);
    state = 4;
    break;
  case 4://C
    clearScreen(COLOR_HOT_PINK);
    drawString5x7(screenWidth/2,screenHeight/4,"BUNS",COLOR_BLACK,COLOR_HOT_PINK);
    fillRectangle(0,screenWidth-10,size,size,color_picker(secondsW));
    buzzer_set_period(c6S);
    state = 5;
    break;
  case 5://C
    clearScreen(COLOR_HOT_PINK);
    drawString5x7(screenWidth/2,screenHeight/4,"BUNS",COLOR_BLACK,COLOR_HOT_PINK);
    fillRectangle(0,screenWidth-10,size,size,color_picker(secondsW));
    buzzer_set_period(c6S);
    rand ^=49;
    state = 6;
    break;
  case 6://quiet
    clearScreen(COLOR_HOT_PINK);
    turn_buzzer_off();
    state = 7;
    break;
  case 7://quiet
    turn_buzzer_off();
    state = 0;
    break;
  }
}

//displays start screen
void start_screen(){
  turn_buzzer_off();//turn buzzer off
  rand = 0;//reset rand
  clearScreen(COLOR_BLACK);//set screen to black
  drawString5x7(0,0,"1. Twinkle Star",COLOR_PINK,COLOR_BLACK);//display instruction
  drawString5x7(0,screenHeight/4,"2. Mystery Tone",COLOR_PINK,COLOR_BLACK);//display instruction
  drawString5x7(0,screenHeight/2,"3. Siren",COLOR_PINK,COLOR_BLACK);//display instruction
  drawString5x7(0,screenHeight*3/4,"4. Hot Cross Buns",COLOR_PINK,COLOR_BLACK);//display instruction
  drawString5x7(0,screenHeight*7/8,"1      2      3     4",COLOR_PINK,COLOR_BLACK);//display instruction
}

//final step in randomizing rand
extern short random(){
  rand ^=67;//xor it
  rand +=COLOR_PINK;//add pink int to it
  return rand;//return
}
  
