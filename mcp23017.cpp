#include "mcp23017.h"

#include <wiringPiI2C.h>
#include <wiringPi.h>

//Other definitions
//#include "hardware_conf.h"


Mcp23017::Mcp23017(QObject *parent) :
    QObject(parent)
{
    porta = 0;
    portb = 0;
}

/*
 * Function: open
 *-----------------
 * Open i2c connection with a MC23017 chip
 *
 * _addr: i2c address of the MC23017
 *
 * returns: 0 if the device was opened correctly
 *          -1 if the device was not opened correctly
 */

int Mcp23017::open(quint8 _addr)
{
    fd = wiringPiI2CSetup(_addr);

    qDebug("fd = %d",fd);
    if (fd == -1) {
            qDebug("Could not create a i2c handle fd= %d",fd);
            return -1;
    }

    //Configure IOCON, disable sequential operation
    int ret = wiringPiI2CWriteReg8(fd,MCP23017_IOCON,0x20);
    qDebug("ret = %d",ret);

    porta = 0;
    portb = 0;

    return 0;
}

/*
 * Function: setTris
 * ------------------
 * Configures the 8 pins of port A/B as inputs/outputs.
 *
 * port: Either PORTA or PORTB
 * tris: 8-bit mask [bit7,bit6,5bit,bit4,bit3,bit2,bit1,bit0].
 *       Inputs are "1", Outputs are "0"
 *
 * return: 0 if successful,
 *         -1 if the i2c failed,
 *         -2 if the port argument was wrong
 */

int Mcp23017::setTris(quint8 port, quint8 tris)
{
    int ret;

    if (port == PORTA) {

        //Configure I/O portA
        ret = wiringPiI2CWriteReg8(fd,MCP23017_IODIRA,tris);
        qDebug("ret = %d",ret);
        return ret;

    } else if (port == PORTB) {

        //Configure I/O portB
        ret = wiringPiI2CWriteReg8(fd,MCP23017_IODIRB,tris);
        qDebug("ret= %d",ret);
        return ret;
    }

    return -2;
}

/*
 * Function writePort
 * ------------------
 * Write 8 bits to port A or B
 *
 * port: Either PORTA or PORTB
 * data: 8 bit data
 *
 * returns: 0 if the write was successful
 *         -1 if the i2c comm. failed
 *         -2 if the port argument was wrong
 */

int Mcp23017::writePort(quint8 port, quint8 data)
{
    int ret;

    if (port == PORTA) {

        //Write to port A
        porta = data;
        ret = wiringPiI2CWriteReg8(fd,MCP23017_GPIOA,data);
        qDebug("ret = %d",ret);

        return ret;
    } else if (port == PORTB) {

        //Write to port B
        portb = data;
        ret = wiringPiI2CWriteReg8(fd,MCP23017_GPIOB,data);
        qDebug("ret = %d",ret);

        return ret;
    }

    return -2;
}

/*
 * Function: writePin
 * -------------------
 * Writes to an individual pin in port A or B
 *
 * port: Either PORTA or PORTB
 * pin:  integer number from 0-7. It selects one of the pins
 *       of the port (port0 - port7)
 * data: true or false (1 or 0)
 *
 * returns: 0 if the write was successful
 *         -1 if the i2c comm. was unsuccesful
 *         -2 if the port argument was wrong
 */

int Mcp23017::writePin(quint8 port, quint8 pin, quint8 data)
{
    int ret;
    quint8 aux;

    if (port == PORTA) {
        if (data == true) {
            porta |= (1 << pin);
        } else {
            aux = ~(1 << pin);
            porta &= aux;
        }

        ret = wiringPiI2CWriteReg8(fd,MCP23017_GPIOA,porta);

        return ret;

    } else if (port == PORTB) {
        if (data == true) {
            portb |= (1 << pin);
        } else {
            aux = ~(1 << pin);
            portb &= aux;
        }

        ret = wiringPiI2CWriteReg8(fd,MCP23017_GPIOB,portb);

        return ret;
    }

    return -2;
}

/*
 * Function: setPullup
 * -------------------
 * Configures the 100k pull-up resistors for pins that are defined as inputs
 *
 * port: Either PORTA or PORTB
 * pullup: 8-bit mask number [bit7,...,bit0]. The pull-up resistor is enabled
 * when bitx = 1, and disabled when bitx = 0.
 *
 * returns: 0 if the configuration was successful
 *         -1 if the i2c comm. was unsuccesful
 *         -2 if the port argument is wrong
 *
 */

int Mcp23017::setPullup(quint8 port, quint8 pullup)
{
    int ret;
    ret = -2;

    if (port == PORTA) {
       ret = wiringPiI2CWriteReg8(fd,MCP23017_GPPUA,pullup);

    } else if (port == PORTB) {
       ret = wiringPiI2CWriteReg8(fd,MCP23017_GPPUB,pullup);
    }

    return ret;
}

/*
 * Function: readPort
 * ------------------
 * Reads the value of the 8 pins in a port.
 *
 * port: Either PORTA or PORTB
 *
 * returns: if successful, it returns the value of pins
 *          in the port [pin7,...,pin0] 0x00 to 0xff.
 *          -2 if the i2c comm. was unsuccessful
 *
 */

int Mcp23017::readPort(quint8 port)
{
    int ret;
    ret = -2;

    if (port == PORTA) {
        ret = wiringPiI2CReadReg8(fd, MCP23017_GPIOA);
        porta = ret;
    } else if (port == PORTB) {
        ret = wiringPiI2CReadReg8(fd, MCP23017_GPIOB);
        portb = ret;
    }

    return ret;
}

/*
 * Function: readPin
 * ------------------
 * Reads the digital value of a pin in a port
 *
 * port: Either PORTA or PORTB
 * pin: number from 0-7 which represents the address of
 *      the pin the port [pin7,....,pin0]
 *
 * returns 1 or 0 if the read was sucessful
 *        -1 if the i2c comm. was unsuccessful
 */

int Mcp23017::readPin(quint8 port, quint8 pin)
{
    int ret;

    if (port == PORTA) {
        ret = wiringPiI2CReadReg8(fd, MCP23017_GPIOA);
        if (ret & (1 << pin)) {
            return 1;
        } else {
            return 0;
        }

    } else if (port == PORTB) {
        ret = wiringPiI2CReadReg8(fd, MCP23017_GPIOB);
        if (ret & (1 << pin)) {
            return 1;
        } else {
            return 0;
        }
    }

    return -1;

}

/*
 * Function: setISR
 * -----------------
 * Configure input pins that will produce interrupt-on-change. Interrupts pins INTA
 * and INTB are separated. The output interrupt pins have active output drivers and are
 * configured Active-low.
 *
 * port: Either PORTA or PORTB
 * intmask: 8 bit mask number [bit7,...,bit0]. Interrupt enabled if bitx = 1.
 *          Interrupt disabled if bitx = 0.
 *
 * return: 0 if the last write was successful
 *        -1 if the i2c comm in the last write failed
 *        -2 if the port argument was wrong
 */
int Mcp23017::setISR(quint8 port, quint8 intmask)
{
    int ret;
    ret = -2;

    if (port == PORTA) {
        ret = wiringPiI2CWriteReg8(fd,MCP23017_GPINTENA,intmask);
        ret = wiringPiI2CWriteReg8(fd,MCP23017_INTCONA,0x00); //pin compared against previous value

    } else if (port == PORTB){
        ret = wiringPiI2CWriteReg8(fd,MCP23017_GPINTENB,intmask);
        ret = wiringPiI2CWriteReg8(fd,MCP23017_INTCONB,0x00); //pin compared against previous value
    }

    return ret;
}

/*
 * Virtual function: ISR
 * This function is triggered from any interrupt service routine declared
 * in mcp23017_isr.h. It is necessary that this function reads the gpiox or
 * the intcapx register in order to re-enable the interrupt!
 * The purpose of this virtual function is to glue any particular logic in a derived
 * class.
 */

int Mcp23017::ISRA()
{
    int ret;

    ret = wiringPiI2CReadReg8(fd, MCP23017_INTCAPA);
    qDebug("intcapa value = %X",ret);

    emit interrupt_A(ret);

    return ret;

}

int Mcp23017::ISRB()
{
    int ret;

    ret = wiringPiI2CReadReg8(fd, MCP23017_INTCAPB);
    qDebug("intcapb value = %X",ret);

    emit interrupt_B(ret);

    return ret;

}



