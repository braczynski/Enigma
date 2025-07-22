#ifndef SIMULATION_H
#define SIMULATION_H

#include <QWidget>
#include "enigmasimulator.h"
#include <vector>

namespace Ui {
class simulation;
}

class simulation : public QWidget
{
    Q_OBJECT

public:
    explicit simulation(QWidget *parent = nullptr);
    ~simulation();

    void add_rotor(int initial_position,int notch_position, int ring_position, std::vector<char> combination);
    void add_rotor(int initial_position, int notch_position, int notch_position_2,  int ring_position, std::vector<char> combination);
    void add_reflector(char version, std::vector<char> combination);
    void add_plugboard(std::vector<char> combination);
    bool is_reflector();
    void clear_reflector();
    void save_file(QString filePath);
    void load_file(QString filePath);

private slots:
    void on_Setup_clicked();

    void on_encrypt_clicked();

private:
    Ui::simulation *ui;

    // var for Rotor
    int count_of_rotors = 0;
    std::vector<int> initial_position_rotor;
    std::vector<int> notch_position_on_rotor;
    std::vector<int> notch_position_on_rotor_2;
    std::vector<int> initial_ring_position_rotor;
    std::vector<std::vector<char>> initial_combination_rotor;

    // var for reflector
    char reflector_version;
    std::vector<char> reflector_combination;

    // var for plugboard
    std::vector<char> plugboard_combination;

    QString input_message, output_message;

    QFile file_;

    void print_combination(std::vector<char> combination, int rotor_number);
    void print_combination(std::vector<char> combination, std::string name);
};

#endif // SIMULATION_H
