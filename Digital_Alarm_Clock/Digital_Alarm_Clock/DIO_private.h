#ifndef			DIO_PRIVATE_H
#define			DIO_PRIVATE_H

/*				PORTA Registers							*/
#define				PORTA_REG			*((volatile u8 *)0x3B)
#define				DDRA_REG			*((volatile u8 *)0x3A)
#define				PINA_REG			*((volatile u8 *)0x39)

/*				PORTB Registers							*/
#define				PORTB_REG			*((volatile u8 *)0x38)
#define				DDRB_REG			*((volatile u8 *)0x37)
#define				PINB_REG			*((volatile u8 *)0x36)

/*				PORTC Registers							*/
#define				PORTC_REG			*((volatile u8 *)0x35)
#define				DDRC_REG			*((volatile u8 *)0x34)
#define				PINC_REG			*((volatile u8 *)0x33)

/*				PORTD Registers							*/
#define				PORTD_REG			*((volatile u8 *)0x32)
#define				DDRD_REG			*((volatile u8 *)0x31)
#define				PIND_REG			*((volatile u8 *)0x30)


#define NULL ( (void *) 0)

#endif