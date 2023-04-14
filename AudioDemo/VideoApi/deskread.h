#ifndef DESKREAD_H
#define DESKREAD_H

#include <QObject>

class DeskRead : public QObject
{
    Q_OBJECT
public:
    explicit DeskRead(QObject *parent = nullptr);

signals:

};

#endif // DESKREAD_H
