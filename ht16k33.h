#ifndef HT16K33_H
#define HT16K33_H

#include <QObject>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#define HT16K33_CMD_BRIGHTNESS 0x0E
#define HT16K33_BLINK_CMD 0x80
#define HT16K33_BLINK_DISPLAYON 0x01
#define HT16K33_BLINK_OFF 0
#define HT16K33_BLINK_2HZ 1
#define HT16K33_BLINK_1HZ 2
#define HT16K33_BLINK_HALFHZ 3
#define HT16K33_BRIGHTNESS 0xE0

class Ht16k33 : public QObject
{
    Q_OBJECT
public:
    explicit Ht16k33(QObject *parent = 0);
    
    int open(quint8 _addr);
    void setBrightness(quint8 b);
    void setBlinkRate(quint8 b);
    void writeDisplay(quint8 num);

public:
    quint16 displaybuffer[8]; // Each of the 8 COMs can handle up to 16 leds
    quint8 i2c_addr;    //i2c Address of the device
    int fd; //handler to the i2c device


signals:
    
public slots:
    
};

#endif // HT16K33_H
