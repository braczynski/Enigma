#ifndef SETUP_CUSTOM_H
#define SETUP_CUSTOM_H

#include <QWidget>
#include <QListWidgetItem>
#include "simulation.h"

namespace Ui {
class setup_custom;
}

class setup_custom : public QWidget
{
    Q_OBJECT

public:
    explicit setup_custom(QWidget *parent = nullptr, simulation *logic = nullptr);
    ~setup_custom();

private slots:
    void on_Rotor_Co_valueChanged(int arg1);

    void on_add_reflector_clicked();

    void on_plugboard_combination_itemClicked(QListWidgetItem *item);

    void on_add_plugboard_clicked();

    void handleRotorCellChanged(int row, int column, const QString &value);

    void on_ReturnCustom_clicked();

private:
    Ui::setup_custom *ui;

    int rotor_count;
    std::vector<std::vector<char>> rotors_combination;
    std::vector<int> rotors_position;
    std::vector<int> rotors_ring;
    std::vector<int> rotors_notch;

    std::vector<char> plugboard_pair;
    std::vector<char> reflector_combination;

    simulation *main;
};

#endif // SETUP_CUSTOM_H
