#include "mcp23017_isr.h"

#include "mcp23017.h"
#include <wiringPi.h>
#include "hardware_conf.h"

Mcp23017* p_extender_1;
Mcp23017* p_extender_2;
Mcp23017* p_extender_3;
/*
 * Function: setupMcp23017_isr_1
 *-------------------------------
 * Configures the interrupt service routine. First, it registers an Mcp23017 object.
 * This object will be tied to the interrupt. Then it calls the setISR public function
 * which setups the pins that are going to be used as interrupts. This is done by
 * using the INTA_PINS constant which should be degined in the hardware_conf.h file.
 * Finally, it assings an input pin from the Raspberry to an interrupt function.
 * This pin is MCP23017_INTA and must be also defined in hardware_conf.
 */

void setupMcp23017_isr_ext1(Mcp23017* pMcp23017)
{
    p_extender_1 = pMcp23017;

    p_extender_1->setISR(PORTA,INTA_PINS1); //Only PORTA configured!
    p_extender_1->setISR(PORTB,INTB_PINS1); //Only PORTB configured!

    //Wire MCP interrupt pin in the raspberry to a function
    wiringPiISR(MCP23017_1_INTA, INT_EDGE_FALLING, &extender1_isrA); //Only INTA configured!
    wiringPiISR(MCP23017_1_INTB, INT_EDGE_FALLING, &extender1_isrB); //Only INTA configured!

    p_extender_1->readPort(PORTA); // Dummy read to reset any glitch interrupt during setup
    p_extender_1->readPort(PORTB); // Dummy read to reset any glitch interrupt during setup

    p_extender_1->porta = p_extender_1->readPort(PORTA); // Dummy read to reset any glitch interrupt during setup
    p_extender_1->portb =p_extender_1->readPort(PORTB); // Dummy read to reset any glitch interrupt during setup
}

/*
 * Function extender1_isrA
 * ----------------------
 * This function is the interrupt service routing that is triggered when INTA signal
 * is activated. It calls the virtual function ISRA.
 */

void extender1_isrA(void)
{
    //int change;

    p_extender_1->ISRA();

    //qDebug("extender1_isr");
    //Here glue your logic
}

/*
 * Function extender1_isrB
 * ----------------------
 * This function is the interrupt service routing that is triggered when INTA signal
 * is activated. It calls the virtual function ISRB.
 */

void extender1_isrB(void)
{
    //int change;

    p_extender_1->ISRB();

    //qDebug("extender2_isr called");
    //Here glue your logic
}

/*
 * Extender2
 */

void setupMcp23017_isr_ext2(Mcp23017* pMcp23017)
{
    p_extender_2 = pMcp23017;

    p_extender_2->setISR(PORTA,INTA_PINS2); //Only PORTA configured!
    p_extender_2->setISR(PORTB,INTB_PINS2); //Only PORTB configured!

    //Wire MCP interrupt pin in the raspberry to a function
    wiringPiISR(MCP23017_2_INTA, INT_EDGE_FALLING, &extender2_isrA); //Only INTA configured!
    wiringPiISR(MCP23017_2_INTB, INT_EDGE_FALLING, &extender2_isrB); //Only INTA configured!

    p_extender_2->readPort(PORTA); // Dummy read to reset any glitch interrupt during setup
    p_extender_2->readPort(PORTB); // Dummy read to reset any glitch interrupt during setup

    p_extender_2->porta = p_extender_2->readPort(PORTA); // Dummy read to reset any glitch interrupt during setup
    p_extender_2->portb =p_extender_2->readPort(PORTB); // Dummy read to reset any glitch interrupt during setup
}

void extender2_isrA(void)
{
    //int change;

    p_extender_2->ISRA();
}

void extender2_isrB(void)
{
    //int change;

    p_extender_2->ISRB();
}


/*
 * Extender3
 */

void setupMcp23017_isr_ext3(Mcp23017* pMcp23017)
{
    p_extender_3 = pMcp23017;

    p_extender_3->setISR(PORTA,INTA_PINS3); //Only PORTA configured!
    p_extender_3->setISR(PORTB,INTB_PINS3); //Only PORTB configured!

    //Wire MCP interrupt pin in the raspberry to a function
    wiringPiISR(MCP23017_3_INTA, INT_EDGE_FALLING, &extender3_isrA); //Only INTA configured!
    wiringPiISR(MCP23017_3_INTB, INT_EDGE_FALLING, &extender3_isrB); //Only INTA configured!

    p_extender_3->readPort(PORTA); // Dummy read to reset any glitch interrupt during setup
    p_extender_3->readPort(PORTB); // Dummy read to reset any glitch interrupt during setup

    p_extender_3->porta = p_extender_2->readPort(PORTA); // Dummy read to reset any glitch interrupt during setup
    p_extender_3->portb =p_extender_2->readPort(PORTB); // Dummy read to reset any glitch interrupt during setup
}

void extender3_isrA(void)
{
    //int change;

    p_extender_3->ISRA();
}

void extender3_isrB(void)
{
    //int change;
    qDebug("EXT 3 INTB called");

    p_extender_3->ISRB();
}

