#ifndef HARDWARE_CONF_H
#define HARDWARE_CONF_H

//Raspberry pin definitions
#define MCP23017_INTA 17
#define MCP23017_INTB 18

//Mcp23017 extender Hardware definitions

#define TRISA 0xFF
#define TRISB 0xFC

#define A_PULLUP 0xFF
#define B_PULLUP 0xFC

//Some Macro definitions
#define LED_B0_OFF myext.writePin(PORTB,0,false)
#define LED_B0_ON myext.writePin(PORTB,0,true)

#define LED_B1_OFF myext.writePin(PORTB,1,false)
#define LED_B1_ON myext.writePin(PORTB,1,true)

#define READ_GPA5 myext.readPin(PORTA,5)

//Interruption configuration
#define INTA_PINS 0xE0
#define INTB_PINS 0x04

#endif // HARDWARE_CONF_H
