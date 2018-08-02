#include "windsensorselect.h"
#include "ui_windsensorselect.h"

WindSensorSelect::WindSensorSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WindSensorSelect)
{
    ui->setupUi(this);
    connect( ui->selectButton, SIGNAL( clicked() ), this, SLOT( setWindSensorType() ) );
}

WindSensorSelect::~WindSensorSelect()
{
    delete ui;
}

void WindSensorSelect::setWindSensorType() {
    windSensorType = ui->windTypeComboBox->currentIndex();
    this->close();
}

int WindSensorSelect::getWindSensorType() {
    return windSensorType;
}
