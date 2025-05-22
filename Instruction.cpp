#include "Instruction.h"
#include "ui_Instruction.h"

Instruction::Instruction(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Instruction)
{
    ui->setupUi(this);
}

Instruction::~Instruction()
{
    delete ui;
}
