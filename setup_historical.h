#ifndef SETUP_HISTORICAL_H
#define SETUP_HISTORICAL_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QListWidgetItem>
#include <vector>
#include "simulation.h"

namespace Ui {
class setup_historical;
}

class setup_historical : public QWidget
{
    Q_OBJECT

public:
    explicit setup_historical(QWidget *parent = nullptr, simulation *logic = nullptr);
    ~setup_historical();

private slots:
    void on_model_currentTextChanged(const QString &arg1);

    void on_reflector_currentTextChanged(const QString &arg1);

    void handleRotorCellChanged(int row, int column, const QString &value);

    void on_add_clicked();

    void on_Plugboard_itemClicked(QListWidgetItem *item);

    void on_Returnhistorical_clicked();

private:
    Ui::setup_historical *ui;

    QString model;

    int row;
    std::vector<std::string> rotors_version;
    std::vector<int> rotors_position;
    std::vector<int> rotors_ring;

    std::vector<char> plugboard_combination;

    simulation *main;


};

#endif // SETUP_HISTORICAL_H
