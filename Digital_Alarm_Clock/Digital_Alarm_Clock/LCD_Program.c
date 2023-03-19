/*
 * LCD_Program.c
 *
 * Created: 2/27/2023 2:57:20 PM
 *  Author: noure
 */ 
#include "Std_Types.h"
#include "LCD_Interface.h"
#include "Bit_Math.h"
#include "DIO_interface.h"
#include <util/delay.h>

#define		LCD_CONTROL_PORT	PORT_D
#define		LCD_EN				PIN5
#define		LCD_RS				PIN6
#define		LCD_RW				PIN7
#define		LCD_DATA_PORT		PORT_B


void LCD_voidInit8Bit(void){
	/* Delay 35ms */
	_delay_ms(35); 
	
	/* For 5*7 font size & Number of Lines = 2 */
	LCD_voidSendCMD8Bit(0x38);
	
	_delay_ms(1); 
	
	/* For Display on and Cursor On and Blinking */
	//LCD_voidSendCMD8Bit(0x0F);
	//_delay_ms(1);
	
	/* */
	LCD_voidSendCMD8Bit(0b00001100);
	_delay_ms(1);
	
	/* Clear Display */
	LCD_voidSendCMD8Bit(0x01);
	_delay_ms(2);
	
	/* Entry Mode */
	LCD_voidSendCMD8Bit(0x06);	
}
void LCD_voidWriteChar8Bit(u8 Data){
	
	/* RS = 1 to Write Data */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS, HIGH);
	
	/* RW = 0 to Write Data */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW, LOW);
	
	/* En = Latch  */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, HIGH);
	_delay_ms(3);
	
	/* Send 8-bit Data */
	DIO_voidSetPortValue(LCD_DATA_PORT, Data);
	
	/* En = Latch  */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, LOW);
	_delay_ms(3);
	
}
void LCD_voidSendCMD8Bit(u8 CMD){
	/* RS = 0 to Write CMD */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS, LOW);

	/* RW = 0 to Write CMD */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW, LOW);
	
	/* En = Latch  */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, HIGH);
	_delay_ms(3);
	
	/* Send 8-bit CMD */
	DIO_voidSetPortValue(LCD_DATA_PORT, CMD);
	
	/* En = Latch  */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN, LOW);
	_delay_ms(3);
}

void LCD_voidWriteString(u8* str){
	
	if(*str != NULL){	
		while(*str != '\0'){
			LCD_voidWriteChar8Bit(*str);
			str++;
		}	
	}
}

void LCD_voidGoToXY(u8 Line, u8 Position){
	
	if(Line == 1){
		LCD_voidSendCMD8Bit((0x80 + Position));
	}
	else if(Line == 2){
		LCD_voidSendCMD8Bit((0xC0 + Position));
	}
}
