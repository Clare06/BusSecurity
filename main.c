#define F_CPU 12000000UL		/* define Clock Frequency */
#include <avr/io.h>					
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "USART_Interrupt.h"	/* include USART Header file */

#define SREG   _SFR_IO8(0x3F)

void GSM_Begin();							

void GSM_Response();

void GSM_Msg_Read(int);

void GSM_Send_Msg(char* , char*);

char buff[160];			/* buffer to store responses and messages */
//char status_flag = 0;		/* for checking any new message */
volatile int buffer_pointer;            
char Mobile_no[14];		/* store mobile no. of received message */
char message_received[60];	/* save received message */
int position = 0;		/* save location of current message */


int main(void)
{
	buffer_pointer = 0;

	memset(message_received, 0, 60);
        
	USART_init(9600);	/* initialize USART */
	sei();
	
	_delay_ms(3000);
	
	//GSM_Begin();		/* Start GSM with AT*/
	char p[11]="0719234568";
	char msg[30]="\n hello";
    GSM_Send_Msg(p,msg);
   // USART_SendString("ATE0\r");
   /* char a='A';
    USART_TxChar(a);*/
	}
		
		
		


void GSM_Begin()
{

	while(1)
	{
		
		USART_SendString("ATE0\r"); /* send ATE0 to check module is ready or not */
		_delay_ms(500);
		if(strstr(buff,"OK"))
		{
			//GSM_Response();
			memset(buff,0,160);
			break;
		}
		
	}
	_delay_ms(1000);

	
	USART_SendString("AT+CMGF=1\r"); /* select message format as text */
	//GSM_Response();
	_delay_ms(1000);
}

void GSM_Msg_Delete(unsigned int position)
{
	buffer_pointer=0;
	char delete_cmd[20];

      /* delete message at specified position */
	sprintf(delete_cmd,"AT+CMGD=%d\r",position);  
	USART_SendString(delete_cmd);
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
   //status_flag = 1;		/* flag for new message arrival */
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







void GSM_Msg_Read(int position)
{
	char read_cmd[10];
	sprintf(read_cmd,"AT+CMGR=%d\r",position);
	USART_SendString(read_cmd);	/* read message at specified location/position */
	
}

