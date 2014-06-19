#include<intrins.h>
#include"p89v51rx2.h"
#include"lcd.h"

sbit touch_sensor=P1^7; //Touch Sensor connected to Pin 1.7

void counter_display(unsigned char number)
{
 unsigned char temp;
 temp=number/10;
 LCD_CMD(0xC7);
 LCD_CHAR(temp+48);
 temp=number%10;
 LCD_CMD(0xC8);
 LCD_CHAR(temp+48);
}

void main(void)
{
 unsigned char count=0;	// Counter variable
 LCD_INIT();
 LCD_CMD(LINE1);
 LCD_WRITE("**BALL-COUNTER**");
 LCD_CMD(DON_COFF);
 counter_display(count);

 while(1)
 {
	 if(touch_sensor==0)//If Touch detected
	 {
	 count++;  //Counter incremented
	 counter_display(count); //Display Number
	 buzzer=0;	//Buzzer ON
	 delay_ms(1000); //Delay for correction if any
	 }
	 else
	 {
	  buzzer=1;	//Buzzer OFF
	 }
 } 
}
