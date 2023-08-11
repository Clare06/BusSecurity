#define F_CPU 8000000UL		/* define Clock Frequency */
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define SREG   _SFR_IO8(0x3F)
#include<avr/io.h> // AVR header
#include<util/delay.h> // delay header
#include "USART.h"	/* include USART Header file */
#include "LCD.h"	/* include LCD Header file */
#include "USART_Interrupt.h"	/* include USART Header file */
#define LCD_DATA PORTB // port B is selected as LCD data port
#define ctrl PORTD // port D is selected as LCD command port
#define en PD7 // enable signal is connected to port D pin 7
#define rw PD6 // read/write signal is connected to port D pin 6
#define rs PD3 // register select signal is connected to port D pin 5

void GSM_Begin();							
void GSM_Delete_All_Msg();
void GSM_Send_Msg(char* , char*);
void lcd();
void rfid_reader();
char buff[160];			/* buffer to store responses and messages */
char *retrieve(char *rfid);
volatile int buffer_pointer;            
char number[14]="7645675345";		/* store mobile no. of received message */
char message[60]="You left child in the bus";	/* save received message */
int position = 0;		/* save location of current message */
char data[5][30];
char g[100]="fail";
char r[100]="Your ID card doesn't match with database";


int main()
{		
	DDRA = 0xC1; //Set PORTA Input and Output pins
	DDRB = 0xFF; //Set PORTB Input and Output pins
	DDRC = 0x00; //Set PORTC Input and Output pins
	DDRD = 0xF8; //Set PORTD Input and Output pins
	
	servo_motor();
		
	while(1)
	{
		if(PINA & (1<<1)) //If switch is pressed
		{
			_delay_ms(500);
			OCR1B = 374;	// Set servo shaft at 180 position  b
			lcd();
			rfid_reader();
		}

		if(!(PINA & (1<<1))) //If switch is off
		{
			_delay_ms(500);
			OCR1B = 124;	// Set servo shaft at 0 position  b
			pir_vibration_buzzer();
		}
	}
	return 0;
}


void servo_motor()
{
	TCNT1 = 0;		/* Set timer1 count zero */
	ICR1 = 2499;		/* Set TOP count for timer1 in ICR1 register */

	/* Set Fast PWM, TOP in ICR1, Clear OC1A and OCR1B on compare match, clk/64 */
	TCCR1A = (1<<WGM11)|(1<<COM1A1)|(1<<COM1B1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
}


void pir_vibration_buzzer()
{
	if(!(PINC&(1<<0)))   // check vibration sensor
	{
			
		if((PINC&(1<<1)) || (PINC&(1<<2)) || (PINC&(1<<3)))            // check for sensor pin PC.0 using bit
		{
			PORTA=0x01;           // buzzer on
			_delay_ms(750);
			PORTA=0x00;
			_delay_ms(150);
			
			GSM_Send_Msg(number,message);
		}
		else
			PORTA=0x00;  // buzzer off
	}
}


void lcd()
{  // int k="";
	init_LCD(); // initialize LCD
	_delay_ms(10); // delay of 100 Milli seconds
	LCD_cmd(0x0C); // display on, cursor off
	_delay_ms(10);
	
	LCD_Write_String("Show Your");
	_delay_ms(50);
	LCD_cmd(0xC0); // move cursor to the start of 2nd line
	_delay_ms(100);
	LCD_Write_String("RFID Card");
}


void rfid_reader()
{
	PORTA = PORTA & (~(1<<6));
	PORTA = PORTA & (~(1<<7));
	// setting demultiplexer for RFID
	
	unsigned char id[12];
		
	uart_init();
	_delay_ms(100);
	
	for(int i=0;i<12;i++) // reading RFID tag number
	{
		id[i]=rx_data();
	}
		
	PORTA = PORTA | (1<<6);  // setting demultiplexer for GSM
		
	buffer_pointer = 0; //buffer 0 index

	USART_init(9600);	/* initialize USART */
	sei(); //global interrupt function enable
	_delay_ms(3000);
	GSM_Begin();	/* Start GSM with AT*/
	retrieve (id);	//Sending the RFID number to database
		
	if(!strstr(buff,"false"))
	{
		char l[100]="student";
		sprintf(l,"Student %s",data[0]);	// fetching student name
		LCD_cmd(0x01);
		_delay_ms(1);
		LCD_Write_String(l);
		_delay_ms(50);
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		_delay_ms(100);
		LCD_Write_String("Attendance Done");
		_delay_ms(5000);
		LCD_cmd(0x01); // make display ON, cursor ON
		_delay_ms(1);
		
		char msg[100]="Your child has arrived the bus";
		GSM_Send_Msg(data[1],msg);	//GSM sending message to the specific number
	}else{
        LCD_cmd(0x01);
		_delay_ms(1);
		LCD_Write_String("ID doesn't match with any data");
		_delay_ms(50);
        LCD_cmd(0x01); // make display ON, cursor ON
		_delay_ms(1);
    }
		
	PORTA = PORTA & (~(1<<6));  // setting demultiplexer for RFID

}


void GSM_Begin()
{
	while(1)
	{	
		USART_SendString("ATE0\r"); /* send ATE0 to check module is ready or not */
		_delay_ms(500);
		if(strstr(buff,"OK"))
		{			
			memset(buff,0,160);
			GSM_Delete_All_Msg();
			break;
		}		
	}
	_delay_ms(1000);	
	USART_SendString("AT+CMGF=1\r"); /* select message format as text */	
	_delay_ms(1000);	
}


void GSM_Delete_All_Msg()
{
	USART_SendString("AT+CMGDA=\"DEL ALL\"\r"); /* delete all messages of SIM */
}



/* ISR routine to save responses/new message */
ISR(USART_RXC_vect)
{
	buff[buffer_pointer] = UDR;	/* copy UDR (received value) to buffer */
	buffer_pointer++;
}


void GSM_Send_Msg(char *num,char *sms)
{
	char sms_buffer[35];
	buffer_pointer=0;
	sprintf(sms_buffer,"AT+CMGS=\"%s\"\r",num);
	USART_SendString(sms_buffer); /*send command AT+CMGS="Mobile No."\r */
	_delay_ms(200);
	while(1)
	{
		if(buff[buffer_pointer]==0x3e) /* wait for '>' character*/
		{
			buffer_pointer = 0;
			memset(buff,0,strlen(buff));
			USART_SendString(sms);	/* send msg to given no. */
			USART_TxChar(0x1a);		/* send Ctrl+Z */
			break;
		}
		buffer_pointer++;
	}
	_delay_ms(300);
	buffer_pointer = 0;
	memset(buff,0,strlen(buff));
	memset(sms_buffer,0,strlen(sms_buffer));
}


char *retrieve(char *rfid){
	buffer_pointer=0;
	
	USART_SendString("AT+CGATT=1\r");
	_delay_ms(300);
	if(strstr(buff,"OK")){
		
		memset(buff,0,strlen(buff));
		USART_SendString("AT+SAPBR-3,1,\"CONTYPE\",\"GPRS\"\r");
		_delay_ms(500);
		
		if(strstr(buff,"OK")){
			
			memset(buff,0,strlen(buff));
			USART_SendString("AT+SAPBR-3,1,\"APN\",\"\"\r");
			_delay_ms(500);
			
			if(strstr(buff,"OK")){
				
				memset(buff,0,strlen(buff));
				USART_SendString("AT+SAPBR-1,1\r");
				_delay_ms(500);
				
				if(strstr(buff,"OK")){
					
					memset(buff,0,strlen(buff));
					USART_SendString("AI+HTTPINIT\r");
					_delay_ms(500);
					
				}
				if(strstr(buff,"OK")){
					
					memset(buff,0,strlen(buff));
					USART_SendString("AI+HTTPINIT\r");
					_delay_ms(500);
					
					if(strstr(buff,"OK")){
						char at[100]="AT+HTTPPARA=\"URL\",\"http://localhost/Database/check.php?RFID=\"\r";
						sprintf(at,"AT+HTTPPARA=\"URL\",\"http://localhost/Database/check.php?RFID=%s\"\r",rfid);
						memset(buff,0,strlen(buff));
						USART_SendString(at);
						_delay_ms(1000);
						USART_SendString("AT+HTTPACTION=0\r");
						
						_delay_ms(500);
						
						memset(buff,0,strlen(buff));
						
						USART_SendString("AT+HTTPREAD=0,30\r");
						if(!strstr(buff,"false")){

						int i=0;
						char *w;
						w=strstr(buff,"&");
						while(w[i]!='^'){
							
							data[0][i]=w[i];
							i++;
						}
						i=0;
						char *e;
						e=strstr(buff,"^");
						
						while(e[i]!='@'){
							
							data[1][i]=e[i];
							i++;
						}
						memset(buff,0,strlen(buff));
						USART_SendString("AT+HTTPTERM\r");
						
						return data;
						}else{
                       
                        return r;
                    }

					}					
				}				
			}			
		}				
	}	
	return g;
}


