/*
 * LCD_Interface.h
 *
 * Created: 2/27/2023 2:56:54 PM
 *  Author: noure
 */ 

#include "Std_Types.h"
#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

void LCD_voidInit8Bit(void); 
void LCD_voidWriteChar8Bit(u8 Data);
void LCD_voidWriteString(u8* str);
void LCD_voidSendCMD8Bit(u8 CMD);
void LCD_voidGoToXY(u8 Line, u8 Position);
 

#endif /* LCD_INTERFACE_H_ */