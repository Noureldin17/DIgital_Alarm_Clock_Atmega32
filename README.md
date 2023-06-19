# DIgital_Alarm_Clock_Atmega32
This Project is a Digital Alarm Clock embedded system using Atmega32 microcontroller. 

## Circuit Components 
- 4 push buttons 
- LCD Display 
- Buzzer 
- 2N2222 Transistor 
- 2 22pf Capacitors 
- 16MHz Crystal Oscillator

## Implementation 

The time of the Alarm and Clock are both dependent on the timer of the microcontroller. The timer feature is used in CTC mode and preloaded the OCR1A register with 15625 as we have a 16MHz oscillator and the 1024 prescaler was used. The time on the LCD is updated every seconed by utilizing the interrupt feature. The whole program is running continuously and the Alarm time and Clock time are compared (if the alarm is on) to signal the Buzzer if they match. 

### Circuit Diagram
<img width="545" alt="Screenshot 2023-06-19 203052" src="https://github.com/Noureldin17/DIgital_Alarm_Clock_Atmega32/assets/90275962/7d65f381-8313-4dd6-86b9-ec18ec79e76c">

### Results Video

https://github.com/Noureldin17/DIgital_Alarm_Clock_Atmega32/assets/90275962/1dad958a-89ea-43f9-8595-7d2f136080b6

