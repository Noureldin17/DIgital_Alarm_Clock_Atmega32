/*
 * Digital_Alarm_Clock.c
 *
 * Created: 2/27/2023 2:42:59 PM
 * Author : noure
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_Interface.h"
#include "DIO_interface.h"
#include "Bit_Math.h"
#include "Std_Types.h"

#define F_CPU 10000000 

#define		MIN_INCREMENT_PIN		PIN3		/* PIN 3 ---> PORT C */
#define		MIN_DECREMENT_PIN		PIN4		/* PIN 4 ---> PORT C */
#define		HOU_INCREMENT_PIN		PIN5		/* PIN 5 ---> PORT C */
#define		HOU_DECREMENT_PIN		PIN6		/* PIN 6 ---> PORT C */
#define		BUZZER_TOGGLE_PIN		PIN0		/* PIN 0 ---> PORT D */
#define		ALARM_TOGGLE_PIN		PIN5		/* PIN 5 ---> PORT A */
#define		ALARM_ADJUST_PIN		PIN7		/* PIN 7 ---> PORT A */ 


void InitTimer(){
	TCCR1B |=(1<<CS12)|(1<<CS10)|(1<<WGM12);  /* setting Pre-scale and CTC mode */
	OCR1A = 15625;
	sei();
	TIMSK |=(1<<OCIE1A);  /* compare match interrupt enable */
}

ISR(TIMER1_COMPA_vect);

static volatile int SEC =0; /*--------------Storing Seconds--------------*/

static volatile int MIN =0; /*--------------Storing Minutes--------------*/

static volatile int HOU =0; /*--------------Storing Hours--------------*/

int main(void)
{
	
    /*-------- Setting the Ports Directions (INPUT/OUTPUT) -------------- */
	
	DIO_voidSetPortDirection(PORT_D, OUTPUT);
	DIO_voidSetPortDirection(PORT_B, OUTPUT);
	DIO_voidSetPortDirection(PORT_C, INPUT);
	DIO_voidSetPortDirection(PORT_A, INPUT);
	
	DIO_voidSetPinValue(PORT_D,BUZZER_TOGGLE_PIN,0);
	
	/*------------- Initializing Timer & LCD Component ---------------- */
	InitTimer();
	LCD_voidInit8Bit();

	char SHOW_SEC [2]; /*--------------Buffer for Displaying Seconds--------------*/

	char SHOW_MIN [2]; /*--------------Buffer for Displaying Minutes--------------*/

	char SHOW_HOU [2]; /*--------------Buffer for Displaying Hours--------------*/
	
	
	int ALARM_SEC = 0; /*--------------Storing Alarm Seconds--------------*/

	int ALARM_MIN = 0; /*--------------Storing Alarm Minutes--------------*/

	int ALARM_HOU = 0; /*--------------Storing Alarm Hours--------------*/
	
	
	char SHOW_ALARM_SEC [2]; /*--------------Buffer for Alarm Displaying Seconds--------------*/
	
	char SHOW_ALARM_MIN [2]; /*--------------Buffer for Alarm Displaying Minutes--------------*/

	char SHOW_ALARM_HOU [2]; /*--------------Buffer for Alarm Displaying Hours--------------*/
	
	
	/*----------------Flags (Indicators) for Pressed Buttons (Pressed = 1 / Not Pressed = 0)------------*/
	
	int MIN_INC_PRESS = 0;
	
	int MIN_DEC_PRESS = 0;
	
	int HOU_INC_PRESS = 0;
	
	int HOU_DEC_PRESS = 0;
		
    while (1) 
    {
		/*----------------Displaying Hours on LCD-----------------*/
		
		LCD_voidGoToXY(1,0);
		
		itoa(HOU/10, SHOW_HOU, 10);
		
		LCD_voidWriteString(SHOW_HOU);
		
		itoa(HOU%10, SHOW_HOU, 10);
		
		LCD_voidWriteString(SHOW_HOU);
		
		LCD_voidWriteString(":");
		
		/*----------------Displaying Minutes on LCD-----------------*/
		
		LCD_voidGoToXY(1,3);
		
		itoa(MIN/10,SHOW_MIN,10);
		
		LCD_voidWriteString(SHOW_MIN);
		
		itoa(MIN%10,SHOW_MIN,10);
		
		LCD_voidWriteString(SHOW_MIN);
		
		LCD_voidWriteString(":");
		
		/*----------------Displaying Seconds on LCD-----------------*/
		
		LCD_voidGoToXY(1,6);
		
		itoa(SEC/10,SHOW_SEC,10);
		
		LCD_voidWriteString(SHOW_SEC);
		
		itoa(SEC%10,SHOW_SEC,10);
		
		LCD_voidWriteString(SHOW_SEC);
		
		LCD_voidGoToXY(1,8);
		
		/*--------------Displaying Alarm Status on LCD--------------*/
		
		if(DIO_u8GetPinValue(PORT_A,ALARM_TOGGLE_PIN)){
			
			LCD_voidWriteString(" ALM:ON ");
			
			if ((ALARM_HOU==HOU) & (ALARM_MIN==MIN) & (ALARM_SEC==SEC)){
								
				DIO_voidSetPinValue(PORT_D,BUZZER_TOGGLE_PIN,HIGH);
								
			}
		}
		
		if(!DIO_u8GetPinValue(PORT_A,ALARM_TOGGLE_PIN)){
			
			LCD_voidWriteString(" ALM:OFF");
					
			DIO_voidSetPinValue(PORT_D,BUZZER_TOGGLE_PIN,LOW);
			
		}
		
		LCD_voidGoToXY(2,0);
		
		LCD_voidWriteString("ALARM: ");
		
		/*----------------Displaying Alarm Hours on LCD-----------------*/
		
		LCD_voidGoToXY(2,7);
		
		itoa(ALARM_HOU/10, SHOW_ALARM_HOU, 10);
		
		LCD_voidWriteString(SHOW_ALARM_HOU);
		
		itoa(ALARM_HOU%10, SHOW_ALARM_HOU, 10);
		
		LCD_voidWriteString(SHOW_ALARM_HOU);
		
		/*----------------Displaying Alarm Minutes on LCD-----------------*/
		
		LCD_voidWriteString(":");
		
		LCD_voidGoToXY(2,10);
		
		itoa(ALARM_MIN/10,SHOW_ALARM_MIN,10);
		
		LCD_voidWriteString(SHOW_ALARM_MIN);
		
		itoa(ALARM_MIN%10,SHOW_ALARM_MIN,10);
		
		LCD_voidWriteString(SHOW_ALARM_MIN);
		
		/*----------------Displaying Alarm Seconds on LCD-----------------*/
		
		LCD_voidWriteString(":");
		
		LCD_voidGoToXY(2,13);
		
		itoa(ALARM_SEC/10,SHOW_ALARM_SEC,10);
		
		LCD_voidWriteString(SHOW_ALARM_SEC);
		
		itoa(ALARM_SEC%10,SHOW_ALARM_SEC,10);
		
		LCD_voidWriteString(SHOW_ALARM_SEC);
		
		if(DIO_u8GetPinValue(PORT_A,ALARM_ADJUST_PIN)){
			
			LCD_voidWriteString("<");
		}
		else{
			LCD_voidWriteString(" ");
		}
		
		
		/*----------------Checking Minutes Increment Button------------------*/
		
		if(!DIO_u8GetPinValue(PORT_A,ALARM_ADJUST_PIN))
		{
			if(!DIO_u8GetPinValue(PORT_C,MIN_INCREMENT_PIN)){
				
				if(MIN<60 && MIN_INC_PRESS == 0){
					MIN_INC_PRESS ++;
					MIN ++; 
				}
				
				if(MIN == 60){
					if(HOU < 24){
						HOU ++;
					}
					MIN = 0; 
				}
				
			}
			else MIN_INC_PRESS = 0;
			
			/*----------------Checking Minutes Decrement Button------------------*/
			
			if (!DIO_u8GetPinValue(PORT_C,MIN_DECREMENT_PIN))  {
				if(MIN>0 && MIN_DEC_PRESS == 0){
					MIN_DEC_PRESS ++;
					MIN --; 
				}
			} else MIN_DEC_PRESS = 0;
			
			/*----------------Checking Hours Increment Button------------------*/
			
			if(!DIO_u8GetPinValue(PORT_C,HOU_INCREMENT_PIN)){
				if(HOU<24 && HOU_INC_PRESS == 0){
					HOU_INC_PRESS ++;
					HOU++; 
				}
								
				if(HOU == 24){
					HOU = 0;
				}
			}else HOU_INC_PRESS = 0;
			
			/*----------------Checking Hours Decrement Button------------------*/
			
			if(!DIO_u8GetPinValue(PORT_C,HOU_DECREMENT_PIN)){
				if(HOU > 0 && HOU_DEC_PRESS == 0){
					HOU_DEC_PRESS ++;
					HOU --;
				}
			}else HOU_DEC_PRESS = 0;
		}
		
		/*------------------------------------------*/
		
		if(DIO_u8GetPinValue(PORT_A,ALARM_ADJUST_PIN))
		{
			if(!DIO_u8GetPinValue(PORT_C,MIN_INCREMENT_PIN)){
				
				if(ALARM_MIN<60 && MIN_INC_PRESS == 0){
					MIN_INC_PRESS ++;
					ALARM_MIN ++;
				}
				
				if(ALARM_MIN == 60){
					if(ALARM_HOU < 24){
						ALARM_HOU ++;
					}
					ALARM_MIN = 0;
				}
			} else MIN_INC_PRESS = 0;
			
			if(!DIO_u8GetPinValue(PORT_C,MIN_DECREMENT_PIN)){
				if(ALARM_MIN>0 && MIN_DEC_PRESS == 0){
					MIN_DEC_PRESS ++;
					ALARM_MIN --;
				}
			} else MIN_DEC_PRESS = 0;
			
			if(!DIO_u8GetPinValue(PORT_C,HOU_INCREMENT_PIN)){
				if(ALARM_HOU<24 && HOU_INC_PRESS == 0){
					HOU_INC_PRESS ++;
					ALARM_HOU ++;
				}
				
				
				if(ALARM_HOU == 24){
					ALARM_HOU = 0;
				}
			} else HOU_INC_PRESS = 0;
			
			if(!DIO_u8GetPinValue(PORT_C,HOU_DECREMENT_PIN)){
				if(ALARM_HOU > 0 && HOU_DEC_PRESS == 0){
					HOU_DEC_PRESS ++;
					ALARM_HOU --;
				}
			}else HOU_DEC_PRESS = 0;
		}
		
		/*------------------------------------------*/
		
    }
}


/*--------Interrupt Service Routine (ISR) Function  Executed Every Second---------*/

ISR(TIMER1_COMPA_vect){

	if (SEC<60){
		SEC++;
	}

	if (SEC==60){
		if (MIN<60){
			MIN++;
		}
		SEC=0;
	}

	if (MIN==60){
		if (HOU<24){
			HOU++;
		}
		MIN=0;
	}
	
	if (HOU==24){
		HOU=0;
	}
}

