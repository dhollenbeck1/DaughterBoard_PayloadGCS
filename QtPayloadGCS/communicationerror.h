#ifndef COMMUNICATIONERROR_H
#define COMMUNICATIONERROR_H

#include <QDialog>

namespace Ui {
class CommunicationError;
}

class CommunicationError : public QDialog
{
    Q_OBJECT

public:
    explicit CommunicationError(QWidget *parent = nullptr);
    ~CommunicationError();

public slots:
    void closeErrorWindow();

private:
    Ui::CommunicationError *ui;
};

#endif // COMMUNICATIONERROR_H
