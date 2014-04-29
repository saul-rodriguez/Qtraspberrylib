#ifndef DISPLAY7SEG_H
#define DISPLAY7SEG_H

#include <QObject>

#include "ht16k33.h"
class Display7seg : public Ht16k33
{
    Q_OBJECT
public:
    explicit Display7seg(QObject *parent = 0);
    
    void writeint(qint16 num);

private:
    static const quint8 numbertable[];

signals:
    
public slots:
    
};

#endif // DISPLAY7SEG_H
