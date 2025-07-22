#include <QTableWidgetItem>
#include <vector>
#include <algorithm>
#include <QMessageBox>
#include "simulation.h"
#include "setup_historical.h"
#include "ui_setup_historical.h"

setup_historical::setup_historical(QWidget *parent, simulation *logic)
    : QWidget(parent)
    , ui(new Ui::setup_historical)
    , main(logic)
    , plugboard_combination(26)
{
    ui->setupUi(this);
}

setup_historical::~setup_historical()
{
    delete ui;
}

void setup_historical::on_model_currentTextChanged(const QString &arg1)
{
    model = arg1;


    int rotors_count;
    bool fourth_rotor = false;

    QStringList versions, end_rotor_version;

    if(arg1 == "Enigma M3") {
        rotors_count = 3;

        versions = {"-", "I", "II", "III", "IV", "V"};
    } else if(arg1 == "Enigma M4"){
        fourth_rotor = true;
        rotors_count = 4;

        versions = {"-", "I", "II", "III", "IV", "V", "VI", "VII"};
        end_rotor_version = {"-", "GAMMA", "BETA"};
    } else {
        rotors_count = 0;
    }

    ui->RotorsList->setRowCount(0);

    int row = ui->RotorsList->rowCount();

    for (int i = 0; i < rotors_count; i++) {
        ui->RotorsList->insertRow(row);


        QStringList positions =
            {"-", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
             "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

        QComboBox *combo = new QComboBox();

        if(fourth_rotor && i == 3) {
            combo->addItems(end_rotor_version);
        }else {
            combo->addItems(versions);
        }

        ui->RotorsList->setCellWidget(row, 0, combo);

        int col = 0;

        connect(combo, &QComboBox::currentTextChanged, this, [this, row, col](const QString &text){
            handleRotorCellChanged(row, col, text);
        });

        for (col = 1; col < 3; ++col) {
            QComboBox *combo = new QComboBox();
            combo->addItems(positions);

            ui->RotorsList->setCellWidget(row, col, combo);
            connect(combo, &QComboBox::currentTextChanged, this, [this, row, col](const QString &text){
                handleRotorCellChanged(row, col, text);
            });
        }

        row = ui->RotorsList->rowCount();
    }

}


void setup_historical::on_reflector_currentTextChanged(const QString &arg1)
{

    const std::vector<std::vector<char>> historical_refrector = {
        // Version B
        {'Y', 'R', 'U', 'H', 'Q', 'S', 'L', 'D', 'P', 'X', 'N', 'G', 'O',
        'K', 'M', 'I', 'E', 'B', 'F', 'Z', 'C', 'W', 'V', 'J', 'A', 'T'},

        // Version C Kriegsmarine
        {'F', 'V', 'P', 'J', 'I', 'A', 'O', 'Y', 'E', 'D', 'R', 'Z','X',
        'W','G', 'C', 'T', 'K', 'U', 'Q', 'S', 'B', 'N', 'M', 'H', 'L'},
    };

    if(main == nullptr) {
        QMessageBox::warning(this, "ERROR", "Failed to add reflector");
        return;
    }

    if(main->is_reflector()) {
        main->clear_reflector();
    }

    if(arg1 == "UKW B") {
        main->add_reflector('B', historical_refrector[0]);
    } else if(arg1 == "UKW C"){
        main->add_reflector('B', historical_refrector[1]);
    }
}

#define FIRSTCOLUMN 0
#define SECONDCOLUMN 1
#define THIRDCOLUMN 2

void setup_historical::handleRotorCellChanged(int row, int column, const QString &Value)
{
    if(main == nullptr) {
        QMessageBox::warning(this, "ERROR", "Failed to add rotors");
        return;
    }

    switch(column)  {
    case FIRSTCOLUMN:
        if(rotors_version.size() > row) {
            rotors_version[row] = Value.toStdString();
        } else {
            rotors_version.push_back(Value.toStdString());
        }

        break;
    case SECONDCOLUMN:
        if(rotors_position.size() > row) {
            rotors_position[row] = (Value.toStdString()[0] - 'A');
        } else {
            rotors_position.push_back((Value.toStdString()[0] - 'A'));
        }

        break;
    case THIRDCOLUMN:
        if(rotors_ring.size() > row) {
            rotors_ring[row] = (Value.toStdString()[0] - 'A');
        } else {
            rotors_ring.push_back((Value.toStdString()[0] - 'A'));
        }

        break;

    }

    qDebug() << "Zmieniono komórkę:" << row << column << "->" << Value;
}

#define COUNT_LETTER_ALPHABET 26

void setup_historical::on_add_clicked()
{
    if(main == nullptr) {
        QMessageBox::warning(this, "ERROR", "Failed to add rotors");
        return;
    }

    QString Qpair = ui->Combination_Edit->text().trimmed().toUpper();

    std::string pair =  Qpair.toStdString();

    char first_letter = pair[0], second_letter = pair[1];

    if (first_letter > second_letter) {
        first_letter = pair[1];
        second_letter = pair[0];
    }

    if(pair.size() > 2) {
        QMessageBox::warning(this, "ERROR", "Enter exactly 2 uppercase letters, e.g. AB");
        return;
    }

    if ((std::find(plugboard_combination.begin(), plugboard_combination.end(), first_letter) != plugboard_combination.end())
        || (std::find(plugboard_combination.begin(), plugboard_combination.end(), second_letter) != plugboard_combination.end())) {

        QMessageBox::warning(this, "ERROR", "You've already entered this pair");
        return;
    }

    for (int i = 0; i < COUNT_LETTER_ALPHABET; ++i) {
        if(!((first_letter >= 'A' && first_letter <= 'Z') ||(second_letter >= 'A' && second_letter <= 'Z'))) {
            QMessageBox::warning(this, "ERROR", "Enter exactly 2 uppercase letters, e.g. AB");
            return;
        }

        if((first_letter - 'A') == i) {
            plugboard_combination[i] = second_letter;
        }

        if((second_letter - 'A') == i) {
            plugboard_combination[i] = first_letter;
        }

    }

    ui->Plugboard->addItem(Qpair);
    ui->Plugboard->sortItems(Qt::AscendingOrder);
    ui->Combination_Edit->clear();
}

void setup_historical::on_Plugboard_itemClicked(QListWidgetItem *item)
{
    QString Qpair = item->text();
    std::string pair = Qpair.toStdString();

    char first_letter = pair[0], second_letter = pair[1];

    if (QMessageBox::question(this, "Delete", "Remove this pair: " + item->text() + "?") == QMessageBox::Yes) {

        auto first_it = std::find(plugboard_combination.begin(), plugboard_combination.end(), first_letter);
        auto second_it = std::find(plugboard_combination.begin(), plugboard_combination.end(), second_letter);

        if(first_it != plugboard_combination.end()) {
            *first_it = 0;
        }

        if(second_it != plugboard_combination.end()) {
            *second_it = 0;
        }

        delete item;
        ui->Plugboard->sortItems(Qt::AscendingOrder);
        return;
    }
}


void setup_historical::on_Returnhistorical_clicked()
{
    if(main == nullptr) {
        QMessageBox::warning(this, "ERROR", "Failed to end setup");
        return;
    }

    if(!main->is_reflector()) {
        QMessageBox::warning(this, "ERROR", "Firstly add reflector");
        return;
    }

    int rotor_count;

    if(model == "Enigma M3") {
        rotor_count = 3;
    } else if(model == "Enigma M4"){
        rotor_count = 4;
    }

    const std::vector<std::vector<char>> historical_rotors = {
        // Rotor I
        {'E', 'K', 'M', 'F', 'L', 'G', 'D', 'Q', 'V', 'Z', 'N', 'T', 'O',
         'W', 'Y', 'H', 'X', 'U', 'S', 'P', 'A', 'I', 'B', 'R', 'C', 'J'},

        // Rotor II
        {'A', 'J', 'D', 'K', 'S', 'I', 'R', 'U', 'X', 'B', 'L', 'H','W',
         'T','M', 'C', 'Q', 'G', 'Z', 'N', 'P', 'Y', 'F', 'V', 'O', 'E'},

        // Rotor III
        {'B', 'D', 'F', 'H', 'J', 'L', 'C', 'P', 'R', 'T', 'X', 'V', 'Z',
         'N', 'Y', 'E', 'I', 'W', 'G', 'A', 'K', 'M', 'U', 'S', 'Q', 'O'},

        // Rotor IV
        {'E', 'S', 'O', 'V', 'P', 'Z', 'J', 'A', 'Y', 'Q', 'U', 'I', 'R',
         'H', 'X', 'L', 'N', 'F', 'T', 'G', 'K', 'D', 'C', 'M', 'W', 'B'},

        // Rotor V
        {'V', 'Z', 'B', 'R', 'G', 'I', 'T', 'Y', 'U', 'P', 'S', 'D', 'N',
         'H', 'L', 'X', 'A', 'W', 'M', 'J', 'Q', 'O', 'F', 'E', 'C', 'K'},

        // Rotor VI
        {'J', 'P', 'G', 'V', 'O', 'U', 'M', 'F', 'Y', 'Q', 'B', 'E', 'N',
         'H', 'Z', 'R', 'D', 'K', 'A', 'S', 'X', 'L', 'I', 'C', 'T', 'W'},

        // Rotor VII
        {'N', 'Z', 'J', 'H', 'G', 'R', 'C', 'X', 'M', 'Y', 'S', 'W','B',
         'O', 'U', 'F', 'A', 'I', 'V', 'L', 'P', 'E', 'K', 'Q', 'D', 'T'},

        // Rotor VIII
        {'F', 'K', 'Q', 'H', 'T', 'L', 'X', 'O', 'C', 'B', 'J', 'S', 'P',
         'D', 'Z', 'R', 'A', 'M', 'E', 'W', 'N', 'I', 'U', 'Y', 'G', 'V'},

        // Rotor BETA
        {'L', 'E', 'Y', 'J', 'V', 'C', 'N', 'I', 'X', 'W', 'P', 'B', 'Q',
         'M', 'D', 'R', 'T', 'A', 'K', 'Z', 'G', 'F', 'U', 'H', 'O', 'S'},

        // Rotor GAMMA
        {'F', 'S', 'O', 'K', 'A', 'N', 'U', 'E', 'R', 'H', 'M', 'B', 'T',
         'I', 'Y', 'C', 'W', 'L', 'Q', 'P', 'Z', 'X', 'V', 'G', 'J', 'D'}

    };

    for (int i = 0; i < rotor_count; i++) {
        if(model == "Enigma M3") {

            int notch;
            std::vector<char> combination;

            if(rotors_version[i] == "I") {
                notch = 16;
                combination = historical_rotors[0];
            } else if (rotors_version[i] == "II") {
                notch = 4;
                combination = historical_rotors[1];
            } else if (rotors_version[i] == "III") {
                notch = 21;
                combination = historical_rotors[2];
            } else if (rotors_version[i] == "IV") {
                notch = 9;
                combination = historical_rotors[3];
            } else if (rotors_version[i] == "V") {
                notch = 5;
                combination = historical_rotors[4];
            } else {
                QMessageBox::warning(this, "ERROR", "Firstly add rotor information");
                return;
            }

            main->add_rotor(rotors_position[i], notch, rotors_ring[i], combination);
        } else if (model == "Enigma M4") {

            int notch1, notch2;
            std::vector<char> combination;

            if(rotors_version[i] == "I") {
                notch1 = 16;
                notch2 = -1;
                combination = historical_rotors[0];
            } else if (rotors_version[i] == "II") {
                notch1 = 4;
                notch2 = -1;
                combination = historical_rotors[1];
            } else if (rotors_version[i] == "III") {
                notch1 = 21;
                notch2 = -1;
                combination = historical_rotors[2];
            } else if (rotors_version[i] == "IV") {
                notch1 = 9;
                notch2 = -1;
                combination = historical_rotors[3];
            } else if (rotors_version[i] == "V") {
                notch1 = 25;
                notch2 = -1;
                combination = historical_rotors[4];
            } else if(rotors_version[i] == "VI") {
                notch1 = 0;
                notch2 = 13;
                combination = historical_rotors[5];
            } else if (rotors_version[i] == "VII") {
                notch1 = 0;
                notch2 = 13;
                combination = historical_rotors[6];
            } else if (rotors_version[i] == "VIII") {
                notch1 = 0;
                notch2 = 13;
                combination = historical_rotors[7];
            } else if (rotors_version[i] == "GAMMA") {
                notch1 = -1;
                notch2 = -1;
                combination = historical_rotors[8];
            } else if (rotors_version[i] == "BETA") {
                notch1 = -1;
                notch2 = -1;
                combination = historical_rotors[9];
            } else {
                QMessageBox::warning(this, "ERROR", "Firstly add rotor information");
                return;
            }

            main->add_rotor(rotors_position[i], notch1, notch2, rotors_ring[i], combination);
        } else {
            QMessageBox::warning(this, "ERROR", "Firstly Select Model");
            return;
        }
    }

    for (int i = 0; i < COUNT_LETTER_ALPHABET; ++i) {
        if(plugboard_combination[i] == 0) {
            plugboard_combination[i] = i + 'A';
        }
    }

    main->add_plugboard(plugboard_combination);

    this->close();
    main->show();
}
