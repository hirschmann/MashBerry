#ifndef QSSRRELAYFACTORY_H
#define QSSRRELAYFACTORY_H

#include <QObject>
#include "qssrrelay.h"

class QSSRrelayFactory : public QObject
{
    Q_OBJECT
public:
    explicit QSSRrelayFactory(QObject *parent = 0);
    QSSRrelay* GetSSRrelay(int ssr, bool activeLow = false);

signals:
    
public slots:

private:
    bool m_bActiveLow;
};

#endif // QSSRRELAYFACTORY_H
