#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_timeEdit_userTimeChanged(const QTime &time);

    void on_timeEdit_2_userTimeChanged(const QTime &time);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

    void on_doubleSpinBox_4_textChanged(const QString &arg1);

    void on_doubleSpinBox_4_valueChanged(double arg1);

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

private:
    void UpdateCalcWin(void);

};


struct CalcEnviroment
{
    double initialAct = 0.0;
    double finalAct;
    QString isotope;
    QString units;
    qint64 initialTime;
    qint64 finalTime;
    //QTime initialTime_t ;
    //QTime finalTime_t;
    double decayArgument;

};

struct Dispenser
{
    double volume = 1.0;
    double actRequested = 0.0;
    double concentration = 0.0;
    double correctedConcentration = 0.0;
    double volToDipense = 0.0;
};

struct AppEnviroment{
    int rows = 0;
};


#endif // MAINWINDOW_H

