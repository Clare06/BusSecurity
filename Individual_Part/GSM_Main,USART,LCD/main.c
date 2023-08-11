#define F_CPU 8000000UL		/* define Clock Frequency */
#include <avr/io.h>					
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<util/delay.h>
#include "LCD.h"
#include "USART_Interrupt.h"	/* include USART Header file */
/*#define LCD_DATA PORTB // port B is selected as LCD data port
#define ctrl PORTD // port D is selected as LCD command port
#define en PD7 // enable signal is connected to port D pin 7
#define rw PD6 // read/write signal is connected to port D pin 6
#define rs PD5 */
#define SREG   _SFR_IO8(0x3F)

void GSM_Begin();							
void lcd();
void GSM_Send_Msg(char* , char*);
char *retrieve(char *rfid);
char buff[160];			/* buffer to store responses and messages */
volatile int buffer_pointer;            
char Mobile_no[14];		/* store mobile no. of received message */
char message_received[60];	/* save received message */
int position = 0;		/* save location of current message */
char data[5][30];
char r[100]="Your ID card doesn't match with database";
int main(void)
{
	buffer_pointer = 0;
	memset(message_received, 0, 60);       
	USART_init(9600);	/* initialize USART */
	sei();
	_delay_ms(3000);
	lcd();
	GSM_Begin();		/* Start GSM with AT*/
	char p[11]="0719234568";
	char msg[30]="hello";
    GSM_Send_Msg(p,msg);
    char rfid[100]="13006FA337F5";
    memset(message_received, 0, 60);
    retrieve(rfid);
    if(!strstr(buff,"false")){  
            char l[100]="student";
            sprintf(l,"Student %s",data[0]);
			LCD_Command(0x01);
			_delay_ms(1);
			LCD_String (l);
			_delay_ms(50);
			LCD_Command(0xC0); // move cursor to the start of 2nd line
			_delay_ms(100);
			LCD_String ("Attendance Done");
			_delay_ms(5000);
			LCD_Command(0x01); // make display ON, cursor ON
			_delay_ms(1);          
            char msg[100]="Your child has arrived the bus";
            GSM_Send_Msg(data[1],msg);          
          } 
    return 0;   
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
		   USART_SendString(sms); /* send msg to given no. */
		   USART_TxChar(0x1a); /* send Ctrl+Z */
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
    memset(buff,0,160);
    USART_SendString("AT+CGATT=1\r");
    _delay_ms(1000);
   
        memset(buff,0,160);
        USART_SendString("AT+SAPBR-3,1,\"CONTYPE\",\"GPRS\"\r");
        _delay_ms(1000);
        
            memset(buff,0,160);
            USART_SendString("AT+SAPBR-3,1,\"APN\",\"\"\r");
            _delay_ms(1000);
                           
                memset(buff,0,160);
                USART_SendString("AT+SAPBR-1,1\r");
                _delay_ms(1000);
                           
                memset(buff,0,160);
                USART_SendString("AI+HTTPINIT\r");
                _delay_ms(1000);
                
                    char at[100]="AT+HTTPPARA=\"URL\",\"http://localhost/Database/check.php?RFID=\"\r";
                    sprintf(at,"AT+HTTPPARA=\"URL\",\"http://localhost/Database/check.php?RFID=%s\"\r",rfid);
                    memset(buff,0,160);
                    USART_SendString(at);
                    _delay_ms(1000);
                    USART_SendString("AT+HTTPACTION=0\r");
                    memset(buff,0,160);
                    _delay_ms(1000);
                    
                    memset(buff,0,160);
                    
                    USART_SendString("AT+HTTPREAD=0,30\r");
                    _delay_ms(5000);
                    
                    if(!strstr(buff,"false")){                   
                    int i=1;
                    char *w;
                    w=strstr(buff,"&");
                    while(w[i]!='^'){                       
                        data[0][i-1]=w[i];
                       i++; 
                    }
                    i=1;
                    char *e;
                    e=strstr(buff,"^");                   
                    while(e[i]!='@'){                       
                        data[1][i-1]=e[i];
                       i++; 
                    }
                    memset(buff,0,160);
                    USART_SendString("AT+HTTPTERM\r");                   
                    return data;
                    }else{                      
                        return r;
                    }                                                                                                   
}      
void lcd()
{  
	//DDRB=0xFF; // set LCD data port as output
	//DDRB=0xE0; // set LCD signals (RS, RW, E) as out put
	LCD_Init (); // initialize LCD
	_delay_ms(10); // delay of 100 Milli seconds
	LCD_Command(0x0C); // display on, cursor off
	_delay_ms(10);	
	LCD_String ("Show Your");
	_delay_ms(50);
	LCD_Command(0xC0); // move cursor to the start of 2nd line
	_delay_ms(100);
	LCD_String ("RFID Card");
}


