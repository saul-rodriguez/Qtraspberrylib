#include "ht16k33.h"

#include <wiringPi.h>
#include <wiringPiI2C.h>

Ht16k33::Ht16k33(QObject *parent) :
    QObject(parent)
{
    fd = 0;

    for (int i=0; i<8; i++)
        displaybuffer[i] = 0;
}

/*
 * Function: open
 * ---------------
 * Open the i2c comm. with the ht16k33 module and starts its
 * internal oscillator.
 *
 * _addr: i2c address of the ht16k33 IC.
 *
 * Returns 0 if the i2c module handler was successfully opened
 *        -1 if the the handler could not be opened
 *        -2 if the ht16k33 oscillator could not be setup
 */

int Ht16k33::open(quint8 _addr)
{
    i2c_addr = _addr;

    //Get the handler
    fd = wiringPiI2CSetup(i2c_addr);

    if (fd == -1) {
        qDebug("Could not create a i2c handle fd= %d",fd);
        return -1;
    }

    //Start the ht16k33 oscillator (page 30)
    int op = wiringPiI2CWrite(fd,0x21);

    if (op <  0) {
        qDebug("oscillator = %d",op);
        return -2;
    }

    return 0;
}

/*
 * Function: setBrightness
 * ------------------------
 * Set the brightness of the ht16k33 IC. The device should have
 * already been opened (::open) before calling this function.
 *
 * b: set the brightness of the leds using duty-cycles. Param. b
 * takes values from 1 (1/16 duty cycle) to 16 (16/16 duty-cycle)
 * more info in page datasheet page31.
 *
 */

void Ht16k33::setBrightness(quint8 b)
{
    if (b > 16)
            b = 16;

        int bright = HT16K33_BRIGHTNESS | b;
        int op = wiringPiI2CWrite(fd, bright);
        if (op < 0) {
            qDebug("bright = %d",op);
        }
}

/*
 * Function: setBlinkRate
 * ----------------------
 * Turns on the display and sets the blink rate of the display. The
 * device should be opened (::open) before calling this function.
 *
 * b: The parameter b can take the following values (page 30):
 * 0 -> 00 (No blink)
 * 1 -> 01 (2 Hz)
 * 2 -> 10 (1 Hz)
 * 3 -> 11 (0.5 Hz)
 */

void Ht16k33::setBlinkRate(quint8 b)
{
    quint8 aux;
    aux = b;

    if (aux > 3)
         aux = 3;

    int blink = HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (aux << 1);

    int op = wiringPiI2CWrite(fd,blink);

    if (op < 0) {
        qDebug("blink = %d",op);
    }

}

/*
 * Function: writeDisplay
 * ----------------------
 * Writes data directly to the display memory of the ht16k33 and
 * updates the display. Mapping of the memory is described in page 13
 * Each of the 8 COM handle 16 ROWs (2bytes each). The logical mapping of the COM registers is:
 *         ROWs Byte 0          ROWs Byte 1
 * COMx 7 6 5 4 3 2 1 0   15 14 13 12 11 10 9 8
 * Each write to memory first places the mem. address and then the 16 bits (2bytes) of the row.
 */
void Ht16k33::writeDisplay(quint8 num)
{
    if (num > 8) // Can not exceed the number of COMs
        num = 8;

    for (quint8 i = 0; i < num; i++) {
        wiringPiI2CWriteReg16(fd, i*2,displaybuffer[i]);
    }
    /*
    int op;

        op = wiringPiI2CWriteReg16(fd, 0x00,displaybuffer[0]); //com0
        op = wiringPiI2CWriteReg16(fd, 0x02,displaybuffer[1]); //com1
        op = wiringPiI2CWriteReg16(fd, 0x04,displaybuffer[2]); //com2
        op = wiringPiI2CWriteReg16(fd, 0x06,displaybuffer[3]); //com3
        op = wiringPiI2CWriteReg16(fd, 0x08,displaybuffer[4]); //com4
    */
}
