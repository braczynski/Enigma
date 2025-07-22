#include <QMessageBox>
#include <QComboBox>
#include "setup_custom.h"
#include "ui_setup_custom.h"
#include "simulation.h"

setup_custom::setup_custom(QWidget *parent, simulation *logic)
    : QWidget(parent)
    , ui(new Ui::setup_custom)
    , main(logic)
    , plugboard_pair(26)
{
    ui->setupUi(this);
}

setup_custom::~setup_custom()
{
    delete ui;
}

void setup_custom::on_Rotor_Co_valueChanged(int arg1)
{
    rotor_count = arg1;

    ui->Rotors_List->setRowCount(0);

    int row = ui->Rotors_List->rowCount();

    QStringList positions =
        {"-", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
         "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

    for (int i = 0; i < rotor_count; i++) {
        ui->Rotors_List->insertRow(row);

        QPlainTextEdit *plainTextEdit = new QPlainTextEdit();

        ui->Rotors_List->setCellWidget(row, 0, plainTextEdit);

        int col = 0;

        connect(plainTextEdit, &QPlainTextEdit::textChanged, this, [this, plainTextEdit, row, col](){
            QString text = plainTextEdit->toPlainText().trimmed().toUpper();
            handleRotorCellChanged(row, col, text);
        });

        for (col = 1; col < 4; ++col) {
            QComboBox *combo = new QComboBox();
            combo->addItems(positions);

            ui->Rotors_List->setCellWidget(row, col, combo);
            connect(combo, &QComboBox::currentTextChanged, this, [this, row, col](const QString &text){
                handleRotorCellChanged(row, col, text);
            });
        }

        row = ui->Rotors_List->rowCount();
    }

}

#define FIRSTCOLUMN 0
#define SECONDCOLUMN 1
#define THIRDCOLUMN 2
#define FOURTHCOLUMN 3
#define COUNT_LETTER_ALPHABET 26

void setup_custom::handleRotorCellChanged(int row, int column, const QString &Value) {
    if(main == nullptr) {
        QMessageBox::warning(this, "ERROR", "Failed to add rotors");
        return;
    }

    std::vector<char> combiniaton;

    for(char i : Value.toStdString()) {
        combiniaton.push_back(i);
    }

    switch(column)  {
    case FIRSTCOLUMN:
        if(Value.size() == COUNT_LETTER_ALPHABET) {
            if(rotors_combination.size() > row) {
                if(rotors_combination[row].size() == COUNT_LETTER_ALPHABET) {
                    int column = 0;
                    for(char i : Value.toStdString()) {
                        rotors_combination[row][column] = i;
                        column++;
                    }
                } else {
                    for(char i : Value.toStdString()) {
                        rotors_combination[row].push_back(i);
                    }
                }
            } else {
                rotors_combination.push_back(combiniaton);
            }
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
    case FOURTHCOLUMN:
        if(rotors_notch.size() > row) {
            rotors_notch[row] = (Value.toStdString()[0] - 'A');
        } else {
            rotors_notch.push_back((Value.toStdString()[0] - 'A'));
        }

        break;
    }

    qDebug() << "Zmieniono komórkę:" << row << column << "->" << Value;
}

void setup_custom::on_add_reflector_clicked()
{
    QString Qpair = ui->reflector->toPlainText().trimmed().toUpper();

    std::string pair =  Qpair.toStdString();

    if(pair.size() == COUNT_LETTER_ALPHABET) {
        if( reflector_combination.size() == COUNT_LETTER_ALPHABET) {
            int column = 0;
            for(char i : pair) {
                reflector_combination[column] = i;
                column++;
            }
        } else {
            for(char i : pair) {
                reflector_combination.push_back(i);
            }
        }
    } else {
        QMessageBox::warning(this, "ERROR", "Enter exactly 26 uppercase letters");
        return;
    }
}

void setup_custom::on_add_plugboard_clicked()
{
    if(main == nullptr) {
        QMessageBox::warning(this, "ERROR", "Failed to add rotors");
        return;
    }

    QString Qpair = ui->plugboard->text().trimmed().toUpper();

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

    if ((std::find(plugboard_pair.begin(), plugboard_pair.end(), first_letter) != plugboard_pair.end())
        || (std::find(plugboard_pair.begin(), plugboard_pair.end(), second_letter) != plugboard_pair.end())) {

        QMessageBox::warning(this, "ERROR", "You've already entered this pair");
        return;
    }

    for (int i = 0; i < COUNT_LETTER_ALPHABET; ++i) {
        if(!((first_letter >= 'A' && first_letter <= 'Z') ||(second_letter >= 'A' && second_letter <= 'Z'))) {
            QMessageBox::warning(this, "ERROR", "Enter exactly 2 uppercase letters, e.g. AB");
            return;
        }

        if((first_letter - 'A') == i) {
            plugboard_pair[i] = second_letter;
        }

        if((second_letter - 'A') == i) {
           plugboard_pair[i] = first_letter;
        }

    }

    ui->plugboard_combination->addItem(Qpair);
    ui->plugboard_combination->sortItems(Qt::AscendingOrder);
    ui->plugboard->clear();
}

void setup_custom::on_plugboard_combination_itemClicked(QListWidgetItem *item)
{
    QString Qpair = item->text();
    std::string pair = Qpair.toStdString();

    char first_letter = pair[0], second_letter = pair[1];

    if (QMessageBox::question(this, "Delete", "Remove this pair: " + item->text() + "?") == QMessageBox::Yes) {

        auto first_it = std::find(plugboard_pair.begin(),plugboard_pair.end(), first_letter);
        auto second_it = std::find(plugboard_pair.begin(), plugboard_pair.end(), second_letter);

        if(first_it != plugboard_pair.end()) {
            *first_it = 0;
        }

        if(second_it !=plugboard_pair.end()) {
            *second_it = 0;
        }

        delete item;
        ui->plugboard_combination->sortItems(Qt::AscendingOrder);
        return;
    }
}


void setup_custom::on_ReturnCustom_clicked()
{
    if(main == nullptr) {
        QMessageBox::warning(this, "ERROR", "Failed to end setup");
        return;
    }

    for (int i = 0; i < rotor_count; i++) {
        main->add_rotor(rotors_position[i], rotors_notch[i], rotors_ring[i], rotors_combination[i]);
    }

    for (int i = 0; i < COUNT_LETTER_ALPHABET; i++) {
        if(plugboard_pair[i] == 0) {
            plugboard_pair[i] = i + 'A';
        }
    }

    main->add_plugboard(plugboard_pair);

    main->add_reflector('Z', reflector_combination);

    this->close();
    main->show();
}
