#ifndef ADA7SEG_H
#define ADA7SEG_H

#include "ht16k33.h"

#include <QObject>

class Ada7Seg : public Ht16k33
{
    Q_OBJECT
public:
    explicit Ada7Seg(QObject *parent = 0);

    void writeint(qint16 num);
    
    static const quint8 numbertable[];

signals:
    
public slots:
    
};

#endif // ADA7SEG_H
