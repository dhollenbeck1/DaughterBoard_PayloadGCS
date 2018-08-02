#ifndef WINDSENSORSELECT_H
#define WINDSENSORSELECT_H

#include <QDialog>

namespace Ui {
class WindSensorSelect;
}

class WindSensorSelect : public QDialog
{
    Q_OBJECT

public:
    explicit WindSensorSelect(QWidget *parent = nullptr);
    ~WindSensorSelect();

    int getWindSensorType();

private slots:
    void setWindSensorType();

private:
    Ui::WindSensorSelect *ui;
    int windSensorType; // index 0: FT205, 1: FT742-SM, 2: Trisonica
};

#endif // WINDSENSORSELECT_H
