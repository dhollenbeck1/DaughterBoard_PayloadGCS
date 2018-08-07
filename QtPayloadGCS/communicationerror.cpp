#include "communicationerror.h"
#include "ui_communicationerror.h"

CommunicationError::CommunicationError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommunicationError)
{
    ui->setupUi(this);
    ui->errorText->setReadOnly( true );
    connect( ui->closeButton, SIGNAL( clicked() ), this, SLOT( closeErrorWindow() ) );
}

CommunicationError::~CommunicationError()
{
    delete ui;
}

void CommunicationError::closeErrorWindow() {
    this->close();
}
