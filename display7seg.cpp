#include "display7seg.h"

/*
 * The DISP3 and DISP6 7-Segment displays are based on the ht16k33 chip.
 * The leds are of the type common cathode (-).
 * The electrical connection of the digits in the display is:
 * [COM5][COM4][COM3][COM2][COM1][COM0]
 *  [#.]  [#.]   [#.]  [#.]  [#.] [#.]
 * The segments of the digits are connected as:
 * ROW  7 6 5 4 3 2 1 0   15 14 13 12 11 10 9 8
 * SEG  . g f e d c b a    x  x  x  x  x  x x x
 *
 * The logical mapping of the COM registers is:
 *         ROWs Byte 0          ROWs Byte 1
 * COMx 7 6 5 4 3 2 1 0   15 14 13 12 11 10 9 8
 *
 */

const quint8 Display7seg::numbertable[] = {
        0x3F, /* 0 */
        0x06, /* 1 */
        0x5B, /* 2 */
        0x4F, /* 3 */
        0x66, /* 4 */
        0x6D, /* 5 */
        0x7D, /* 6 */
        0x07, /* 7 */
        0x7F, /* 8 */
        0x6F, /* 9 */
        0x77, /* a */
        0x7C, /* b */
        0x39, /* C */
        0x5E, /* d */
        0x79, /* E */
        0x71, /* F */
};


Display7seg::Display7seg(QObject *parent) :
    Ht16k33(parent)
{
}

void Display7seg::writeint(qint16 num)
{
    quint16 res,absol;
    qint16 aux[6];
    quint8 sign;

    int i;
    for (i=0;i<6;i++)
        aux[i] = 0;


    if (num < 0) {
        sign = 1;
        absol = (-num);
    } else {
        sign = 0;
        absol = num;
    }

    for (i=0;i<6;i++) {
        res = absol%10;
        absol /= 10;
        aux[i] = numbertable[res];
        if (!absol) break;
    }

    if (sign && i<5) {
        i++;
        aux[i] = 0x40;
    }

    for (i = 0; i < 6; i++) {
        displaybuffer[i] = aux[i];
    }


    writeDisplay(6);

}
