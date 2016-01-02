#ifndef QTEMPFILTER_H
#define QTEMPFILTER_H

#include <QObject>
#include <QQueue>

class QTempFilter : public QObject
{
    Q_OBJECT
public:
    explicit QTempFilter(QObject *parent = 0);
    double FilterTemperature(double temperature);

signals:

private:
    void AddTemperature(int temperature);

    QQueue<int> m_queue;
    int m_consecOutliers;
    int m_sum;

    static const int TEMP_MAX_DEVIATION = 5;
    static const int OUTLIERS_LIMIT = 3;
    static const int QUEUE_MAX_LENGTH = 5;
    static const int PRECISION_FACTOR = 100000;
};

#endif // QTEMPFILTER_H
