#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include "enigmasimulator.h"
#include "./ui_enigmasimulator.h"
#include "simulation.h"

simulation *sim;

void EnigmaSimulator::CreateFile()
{
    filePath = QFileDialog::getSaveFileName(
        this,
        "Create new setup",
        QDir::homePath() + "/setup.json",    // domyślna lokalizacja + nazwa
        "Text File (*.json);;All File (*)" // filtry
        );

    if (filePath.isEmpty())
        return;

    file.setFileName(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.close();
        QMessageBox::information(this, "File Created", "Save in:\n" + filePath);
    } else {
        QMessageBox::warning(this, "ERROR", "Failed to create the file.");
    }

}

EnigmaSimulator::EnigmaSimulator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EnigmaSimulator)
{
    ui->setupUi(this);
}

EnigmaSimulator::~EnigmaSimulator()
{
    delete ui;
}

std::string EnigmaSimulator::show_mode() {
    return mode;
}

void EnigmaSimulator::on_actionNew_configuration_triggered()
{
    CreateFile();
}

void EnigmaSimulator::on_actionLoad_configuration_triggered()
{
    if(filePath.isEmpty()) {
        filePath = QFileDialog::getOpenFileName(
            nullptr,
            "Wybierz plik JSON",
            "",
            "Pliki JSON (*.json);;Wszystkie pliki (*)"
            );

        if (filePath.isEmpty()) {
            QMessageBox::warning(this, "ERROR", "Nie wybrano pliku.");
            return;
        }

        file.setFileName(filePath);
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "ERROR", "Failed to open a file");
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Błąd parsowania JSON:" << parseError.errorString();
    }

    if (!doc.isObject()) {
        qDebug() << "Plik JSON nie zawiera obiektu głównego.";
    }

    QJsonObject obj = doc.object();
    mode = (obj.value("mode").toString()).toStdString();

    if (ui->centralwidget) {
        ui->centralwidget->hide();
    }

    sim = new simulation(this);
    sim->load_file(filePath);
    setCentralWidget(sim);
}

void EnigmaSimulator::on_actionSave_configuration_triggered()
{
    sim->save_file(filePath);
}

void EnigmaSimulator::on_actionClose_triggered()
{
    close();
}

void EnigmaSimulator::on_actionAbout_triggered()
{
    //na koneic
}

void EnigmaSimulator::on_actionUser_Manual_triggered()
{
    // na koniec
}

void EnigmaSimulator::SimulationWindow()
{
    if (ui->centralwidget) {
        ui->centralwidget->hide();
    }

    sim = new simulation(this);
    setCentralWidget(sim);
}

void EnigmaSimulator::on_actionCustom_triggered()
{
    mode = "Custom";

    CreateFile();

    SimulationWindow();
}

void EnigmaSimulator::on_actionHistorical_triggered()
{
    mode = "Historical";

    CreateFile();

    SimulationWindow();
}

void EnigmaSimulator::on_radioHistorical_clicked()
{
    mode = "Historical";

    CreateFile();

    SimulationWindow();
}


void EnigmaSimulator::on_radioCustom_clicked()
{
    mode = "Custom";

    CreateFile();

    SimulationWindow();
}

