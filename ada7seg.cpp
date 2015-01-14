#include "ada7seg.h"

const quint8 Ada7Seg::numbertable[] = {
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


Ada7Seg::Ada7Seg(QObject *parent) :
    Ht16k33(parent)
{
}

void Ada7Seg::writeint(qint16 num)
{
    quint16 res, absol;
    qint16 aux[4];
    qint8 sign;

    int i;
    for (i = 0; i<4; i++)
        aux[4] = 0;

    if (num < 0) {
        absol = -num;
        sign = 1;
    } else {
        absol = num;
        sign = 0;
    }

    for (i=0;i<4;i++) {
        res = absol % 10;
        absol /= 10;
        aux[i] = numbertable[res];
        if (!absol) break;
    }

    if (sign && i<3) {
        i++;
        aux[i] = 0x40; // minus sign
    }

    displaybuffer[0] = aux[3];
    displaybuffer[1] = aux[2];
    displaybuffer[3] = aux[1];
    displaybuffer[4] = aux[0];

    displaybuffer[2] = 0; //semi dot (:) off

    writeDisplay(4);


}
