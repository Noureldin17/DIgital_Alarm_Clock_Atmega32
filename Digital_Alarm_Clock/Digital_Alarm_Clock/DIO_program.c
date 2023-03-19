/*					Library Includes					*/
#include	"Std_Types.h"
#include	"Bit_Math.h"
/*					MCAL    Includes					*/
#include	"DIO_interface.h"
#include	"DIO_private.h"

/*					FOR ONE PIN										*/
/*			Determine Direction for one pin	(in/out)				*/
/*			DIO_voidSetPinDirection(PORTC,PIN7,OUTPUT);				*/
void	DIO_voidSetPinDirection(u8 PORTID , u8 PINID , u8 Direction)
{
	/*				Range Check										*/
	if( ( PORTID < 4 ) && ( PINID < 8 ) )
	{
		if( Direction == OUTPUT )
		{
			switch(PORTID)
			{
				case	PORT_A	:	SET_BIT(DDRA_REG,PINID);	break;
				case	PORT_B	:	SET_BIT(DDRB_REG,PINID);	break;
				case	PORT_C	:	SET_BIT(DDRC_REG,PINID);	break;
				case	PORT_D	:	SET_BIT(DDRD_REG,PINID);	break;
			}
		}
		else if(Direction == INPUT)
		{
			switch(PORTID)
			{
				case	PORT_A	:	CLR_BIT(DDRA_REG,PINID);	break;
				case	PORT_B	:	CLR_BIT(DDRB_REG,PINID);	break;
				case	PORT_C	:	CLR_BIT(DDRC_REG,PINID);	break;
				case	PORT_D	:	CLR_BIT(DDRD_REG,PINID);	break;
			}			
		}
		else{	/*		Do Nothing		*/	}
	}
	else{	/*		Do Nothing		*/	}
}

/*			Determine (Output) High or Low for one pin	(1/0)		*/
/*			DIO_voidSetPinValue(PORTC,PIN7,HIGH);					*/
void	DIO_voidSetPinValue(u8 PORTID , u8 PINID , u8 Value)
{
	/*				Range Check										*/
	if( ( PORTID < 4 ) && ( PINID < 8 ) )
	{
		if( Value == HIGH )
		{
			switch(PORTID)
			{
				case	PORT_A	:	SET_BIT(PORTA_REG,PINID);	break;
				case	PORT_B	:	SET_BIT(PORTB_REG,PINID);	break;
				case	PORT_C	:	SET_BIT(PORTC_REG,PINID);	break;
				case	PORT_D	:	SET_BIT(PORTD_REG,PINID);	break;
			}
		}
		else if(Value == LOW)
		{
			switch(PORTID)
			{
				case	PORT_A	:	CLR_BIT(PORTA_REG,PINID);	break;
				case	PORT_B	:	CLR_BIT(PORTB_REG,PINID);	break;
				case	PORT_C	:	CLR_BIT(PORTC_REG,PINID);	break;
				case	PORT_D	:	CLR_BIT(PORTD_REG,PINID);	break;
			}			
		}
		else{	/*		Do Nothing		*/	}
	}
	else{	/*		Do Nothing		*/	}	
}

/*			Determine (Input) High or Low for one pin	(1/0)		*/
u8		DIO_u8GetPinValue(u8 PORTID , u8 PINID)
{
	u8 Local_Val = 0xFF;
/*				Range Check										*/
	if( ( PORTID < 4 ) && ( PINID < 8 ) )
	{	
			switch(PORTID)
			{
				case	PORT_A	:	Local_Val	=	GET_BIT(PINA_REG,PINID);	break;
				case	PORT_B	:	Local_Val	=	GET_BIT(PINB_REG,PINID);	break;
				case	PORT_C	:	Local_Val	=	GET_BIT(PINC_REG,PINID);	break;
				case	PORT_D	:	Local_Val	=	GET_BIT(PIND_REG,PINID);	break;
			}	
	}
	else{	/*		Do Nothing		*/	}	
	return Local_Val;
}

/*					FOR ONE PORT(8 pins)								*/
/*			Determine Direction for one port(8 PINS)	(in/out)		*/
/*			DIO_voidSetPortDirection(PORTA , 8)		0b0000 1000;		*/
/*			DIO_voidSetPortDirection(PORTB , 0x0F)		0b0000 1111;	*/
/*			DIO_voidSetPortDirection(PORTB , OUTPUT)		0b1111 1111;*/
void	DIO_voidSetPortDirection(u8 PORTID , u8 Direction)
{
	/*				Range Check										*/
	if(  PORTID < 4  )
	{
		if( Direction == OUTPUT )
		{
			switch(PORTID)
			{
				case	PORT_A	:	DDRA_REG	=	0xFF;	break;
				case	PORT_B	:	DDRB_REG	=	0xFF;	break;
				case	PORT_C	:	DDRC_REG	=	0xFF;	break;
				case	PORT_D	:	DDRD_REG	=	0xFF;	break;
			}
		}
		else if(Direction == INPUT)
		{
			switch(PORTID)
			{
				case	PORT_A	:	DDRA_REG	=	0x00;	break;
				case	PORT_B	:	DDRB_REG	=	0x00;	break;
				case	PORT_C	:	DDRC_REG	=	0x00;	break;
				case	PORT_D	:	DDRD_REG	=	0x00;	break;
			}			
		}
		else
		{
			switch(PORTID)
			{
				case	PORT_A	:	DDRA_REG	=	Direction;	break;
				case	PORT_B	:	DDRB_REG	=	Direction;	break;
				case	PORT_C	:	DDRC_REG	=	Direction;	break;
				case	PORT_D	:	DDRD_REG	=	Direction;	break;
			}				
		}
	}
	else{	/*		Do Nothing		*/	}
	
}
/*			Determine (Output) High or Low for one PORT(8 PINS)	(1/0)*/
void	DIO_voidSetPortValue(u8 PORTID , u8 Value)
{
	/*				Range Check										*/
	if(  PORTID < 4  )
	{
		if( Value == HIGH )
		{
			switch(PORTID)
			{
				case	PORT_A	:	PORTA_REG	=	0xFF;	break;
				case	PORT_B	:	PORTB_REG	=	0xFF;	break;
				case	PORT_C	:	PORTC_REG	=	0xFF;	break;
				case	PORT_D	:	PORTD_REG	=	0xFF;	break;
			}
		}
		else if(Value == LOW)
		{
			switch(PORTID)
			{
				case	PORT_A	:	PORTA_REG	=	0x00;	break;
				case	PORT_B	:	PORTB_REG	=	0x00;	break;
				case	PORT_C	:	PORTC_REG	=	0x00;	break;
				case	PORT_D	:	PORTD_REG	=	0x00;	break;
			}			
		}
		else
		{
			switch(PORTID)
			{
				case	PORT_A	:	PORTA_REG	=	Value;	break;
				case	PORT_B	:	PORTB_REG	=	Value;	break;
				case	PORT_C	:	PORTC_REG	=	Value;	break;
				case	PORT_D	:	PORTD_REG	=	Value;	break;
			}				
		}
	}
	else{	/*		Do Nothing		*/	}	
}

u8 DIO_u8GetPortValue(u8 PORTID)
{
	u8 Local_Value = 0xFF;
	
	if(  PORTID < 4  )
	{

		switch(PORTID)
		{
			case	PORT_A	:	Local_Value = PORTA_REG;    break;
			case	PORT_B	:	Local_Value = PORTB_REG;	break;
			case	PORT_C	:	Local_Value = PORTC_REG;	break;
			case	PORT_D	:	Local_Value = PORTD_REG;	break;
		}

	}
	return Local_Value;
}