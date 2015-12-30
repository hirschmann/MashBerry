#ifndef QSSRRELAYKERNEL_H
#define QSSRRELAYKERNEL_H

#include "qssrrelay.h"
#include <QFile>

class QSSRrelayKernel : public QSSRrelay
{
    Q_OBJECT
public:
    explicit QSSRrelayKernel(int ssr, bool activeLow = false, QObject *parent = 0);
    virtual void Start();
    virtual void SetPower(int power);

signals:
    
public slots:
    
private:
    QFile *m_ssr;
    bool m_bActiveLow;
};

#endif // QSSRRELAYKERNEL_H
