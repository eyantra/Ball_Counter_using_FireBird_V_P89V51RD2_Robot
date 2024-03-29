/**************************************************************************************************************
		Platform: Fire Bird V P89V51RD2
		lcd.h
		Written by: Pawankumar Suryawanshi, ERTS Lab, IIT Bombay
		Last Modification: 2010-05-25
		Compiled with: uVision3 V3.90; C Compiler: C51.Exe, V8.18
**************************************************************************************************************/	


sbit RS=P2^6; //Register Select
sbit RW=P2^5; //Read Write
sbit EN=P2^4; //Enable line
sbit buzzer=P2^7; //Buzzer Pin

void delay_ms(unsigned int ms)		// Delay Function
{
 unsigned int i, j;
 
 for(i=0;i<ms;i++)
 	for(j=0;j<53;j++);
} 

void pulse(void)	 //Generating Hi-Low Pulse for Enable Pin
{
 EN=1;
 delay_ms(4);
 EN=0;
}

const unsigned char LCD_CLEAR 	  = 0x01;	/* Clear display screen */  
const unsigned char CURSOR_HOME	  = 0x02;	/* Return Home (First line first block) */
const unsigned char DISPLAY_ON 	  = 0x0F;	/* Display ON cursor Blinking */
const unsigned char LINE1 	      = 0x80;	/* Address for Line 1 */ 
const unsigned char LINE2	 	  = 0xC0;	/* Address for Line 2 */

const unsigned char CURSOR_LEFT   = 0x10;	/* Decrement cursor (shift cursor to left) */
const unsigned char CURSOR_RIGHT  = 0x14;	/* Increment cursor (shift cursor to right) */
const unsigned char DISPLAY_LEFT  = 0x18;	/* Shift the entire display to left */ 
const unsigned char DISPLAY_RIGHT = 0x1C;	/* Shift the entire display to right */
const unsigned char DOFF_COFF 	  = 0x08;	/* Display OFF cursor OFF */
const unsigned char DON_COFF 	  = 0x0C;	/* Display ON cursor OFF */

void LCD_CMD(unsigned char cmd)		 //Function To Send Command
{
 P2=(0x00|0x80);
 EN=0;								
 RS=0;								// Command Register Select
 //RW=0;

 P2=(((cmd&0xF0)/0x10)|0x80);		// Send Higher Bits
 pulse();

 P2=((cmd&0x0F)|0x80);				// Send Lower Bits
 pulse();
}

void LCD_INIT(void)
{
 EN=0;
 RS=0;				// Command Register Select
 //RW=0;
 P2=(0x02|0x80);		// 4 bit mode
 pulse();
 LCD_CMD(LCD_CLEAR);		 // Clear LCD 
 LCD_CMD(DISPLAY_ON);
 LCD_CMD(CURSOR_HOME);
}

void LCD_CHAR(unsigned char dat)   //Function for Character write
{
 P2=(0x40|0x80);
 EN=0;
 RS=1;					// Data Register Select
 //RW=0;
 P2=((((dat&0xF0)/0x10)|0x40)|0x80);	  // Send Higher Bits
 pulse();

 P2=(((dat&0x0F)|0x40)|0x80);			  // Send Lower Bits
 pulse();
}

void LCD_WRITE(unsigned char *dat)		  // Function to write Character String
{
 unsigned char i;

 for(i=0;i<16;i++)
 {
 	if(*dat!='\0')
	{
		LCD_CHAR(*dat);					 // Sending each character of string to print
		dat++;
	}
	else
	{
		break;
	}
 }
}

