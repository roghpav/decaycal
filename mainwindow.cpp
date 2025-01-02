#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>



CalcEnviroment calEnv;
Dispenser dispEnv;
AppEnviroment appEnv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

    {
    ui->setupUi(this);



    calEnv.isotope = "F18";
    calEnv.units = "mCi";
    calEnv.initialAct = 0.0;
    calEnv.decayArgument = 109.77;
    QTime iniT = ui->timeEdit->time();
    calEnv.initialTime = (qint64)iniT.msecsSinceStartOfDay();
    QTime finT = ui->timeEdit->time();
    calEnv.initialTime = (qint64)finT.msecsSinceStartOfDay();
    ui->doubleSpinBox_2->setValue(dispEnv.volume);

    this->UpdateCalcWin();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::UpdateCalcWin(){
    ui->label->setText(calEnv.units);
    ui->label_2->setText(calEnv.units);
    ui->label_10->setText(calEnv.units);

    double timeElapsed = (double)calEnv.finalTime/60000 - (double)calEnv.initialTime/60000;
    double argument = (timeElapsed/calEnv.decayArgument);
    double dfactor = (double)powf64(0.5,argument);
    calEnv.finalAct = calEnv.initialAct*dfactor;
    QString valueAsString = QString::number(calEnv.finalAct);
    //QString valueAsString = QString::number(timeElapsed);
    ui->textBrowser->setText(valueAsString);

    //Dispenser part
    dispEnv.concentration = calEnv.initialAct / dispEnv.volume;
    dispEnv.correctedConcentration = calEnv.finalAct / dispEnv.volume;
    QString concentrationAsString = QString::number(dispEnv.concentration);
    QString corrconcentrationAsString = QString::number(dispEnv.correctedConcentration);
    ui->label_concen->setText(concentrationAsString+" "+calEnv.units+"/mL");
    ui->label_corrcon->setText(corrconcentrationAsString+" "+calEnv.units+"/mL");

    dispEnv.actRequested = ui->doubleSpinBox_3->value();
    double tempVol = dispEnv.actRequested / dispEnv.correctedConcentration;
    dispEnv.volToDipense = tempVol;

    ui->doubleSpinBox_3->setValue(dispEnv.actRequested);
    ui->doubleSpinBox_4->setValue(dispEnv.volToDipense);

}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    calEnv.isotope = ui->comboBox->currentText();
    if(calEnv.isotope == "F18"){
        calEnv.decayArgument = 109.77;
    }else if(calEnv.isotope == "Tc99m"){
        calEnv.decayArgument = 360.59999999999997;
    }else if(calEnv.isotope == "C11"){
        calEnv.decayArgument = 20.39;
    }else if(calEnv.isotope == "Cu64"){
        calEnv.decayArgument = 762.0;
    }

    UpdateCalcWin();
}


void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    calEnv.units = ui->comboBox_2->currentText();
    UpdateCalcWin();
}


void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    calEnv.initialAct = ui->doubleSpinBox->value();
    UpdateCalcWin();
}


void MainWindow::on_timeEdit_userTimeChanged(const QTime &time)
{
    QTime iniT = ui->timeEdit->time();
    calEnv.initialTime = (qint64)iniT.msecsSinceStartOfDay();
    UpdateCalcWin();
}


void MainWindow::on_timeEdit_2_userTimeChanged(const QTime &time)
{
    QTime finT = ui->timeEdit_2->time();
    calEnv.finalTime = (qint64)finT.msecsSinceStartOfDay();
    UpdateCalcWin();
}


void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    dispEnv.volume = ui->doubleSpinBox_2->value();
    UpdateCalcWin();
}


void MainWindow::on_doubleSpinBox_3_valueChanged(double arg1)
{
    dispEnv.actRequested = ui->doubleSpinBox_3->value();
    double tempVol = dispEnv.actRequested / dispEnv.correctedConcentration;
    dispEnv.volToDipense = tempVol;
    ui->doubleSpinBox_4->setValue(tempVol);
    //UpdateCalcWin();
}


void MainWindow::on_doubleSpinBox_4_textChanged(const QString &arg1)
{
    //
}


void MainWindow::on_doubleSpinBox_4_valueChanged(double arg1)
{
    dispEnv.volToDipense = ui->doubleSpinBox_4->value();
    double tempAct = dispEnv.volToDipense * dispEnv.correctedConcentration;
    dispEnv.actRequested = tempAct;
    ui->doubleSpinBox_3->setValue(tempAct);
    //UpdateCalcWin();
}


void MainWindow::on_pushButton_clicked()
{

    appEnv.rows++;
    QTime t_init = QTime::fromMSecsSinceStartOfDay(calEnv.initialTime);
    QTime t_final = QTime::fromMSecsSinceStartOfDay(calEnv.finalTime);
    QString itemAdd = calEnv.isotope + " C: " + QString::number(dispEnv.concentration) + " " + calEnv.units + "/mL At: " + t_init.toString() +
            "\tC: " + QString::number(dispEnv.correctedConcentration) + " " + calEnv.units + "/mL At: " + t_final.toString() +
            "\tAct: " + QString::number(dispEnv.actRequested) + " " + calEnv.units +
            "\tVol: " + QString::number(dispEnv.volToDipense) + "mL";
    ui->listWidget->addItem(itemAdd);
}


void MainWindow::on_pushButton_4_clicked()
{
    QTime t_init = QTime::fromMSecsSinceStartOfDay(calEnv.initialTime);
    QTime t_final = QTime::fromMSecsSinceStartOfDay(calEnv.finalTime);
    QString itemAdd = calEnv.isotope + " A: " + QString::number(calEnv.initialAct) + " " + calEnv.units + " At: " + t_init.toString() +
            "\tA: " + QString::number(calEnv.finalAct) + " " + calEnv.units + " At: " + t_final.toString() ;
    ui->listWidget->addItem(itemAdd);

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->listWidget->clear();
}

