#ifndef ENIGMASIMULATOR_H
#define ENIGMASIMULATOR_H

#include <QMainWindow>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui {
class EnigmaSimulator;
}
QT_END_NAMESPACE

class EnigmaSimulator : public QMainWindow
{
    Q_OBJECT

public:
    EnigmaSimulator(QWidget *parent = nullptr);
    ~EnigmaSimulator();

    std::string show_mode();

private:
    QString filePath;
    QFile file;

    std::string mode;

    Ui::EnigmaSimulator *ui;
    void CreateFile();
    void SimulationWindow();

private slots:
    void on_actionNew_configuration_triggered();
    void on_actionLoad_configuration_triggered();
    void on_actionSave_configuration_triggered();
    void on_actionClose_triggered();
    void on_actionAbout_triggered();
    void on_actionUser_Manual_triggered();
    void on_actionCustom_triggered();
    void on_actionHistorical_triggered();
    void on_radioHistorical_clicked();
    void on_radioCustom_clicked();
};

#endif // ENIGMASIMULATOR_H
