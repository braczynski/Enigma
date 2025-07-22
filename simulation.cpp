#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include "simulation.h"
#include "ui_simulation.h"
#include "setup_historical.h"
#include "setup_custom.h"
#include "enigma.h"
#include "enigma_m4.h"
#include "enigma_custom.h"
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"

void simulation::add_rotor(int initial_position, int notch_position, int ring_position, std::vector<char> combination)
{
    count_of_rotors++;

    initial_position_rotor.push_back(initial_position);
    notch_position_on_rotor.push_back(notch_position);
    initial_ring_position_rotor.push_back(ring_position);
    initial_combination_rotor.push_back(combination);
}

void simulation::add_rotor(int initial_position, int notch_position, int notch_position_2,  int ring_position, std::vector<char> combination)
{
    count_of_rotors++;

    initial_position_rotor.push_back(initial_position);
    notch_position_on_rotor.push_back(notch_position);
    notch_position_on_rotor_2.push_back(notch_position_2);
    initial_ring_position_rotor.push_back(ring_position);
    initial_combination_rotor.push_back(combination);
}

void simulation::add_reflector(char version, std::vector<char> combination)
{
    reflector_version = version;

    reflector_combination = std::move(combination);
}

void simulation::add_plugboard(std::vector<char> combination)
{
    plugboard_combination = std::move(combination);
}

bool simulation::is_reflector()
{
    return !reflector_combination.empty();
}

void simulation::clear_reflector()
{
    reflector_version = 0;

    reflector_combination.clear();
}

simulation::simulation(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::simulation)
{
    ui->setupUi(this);
}

simulation::~simulation()
{
    delete ui;
}

void simulation::on_Setup_clicked()
{
    EnigmaSimulator *main = qobject_cast<EnigmaSimulator*>(this->parent());

    if(main->show_mode() == "Historical"){
        simulation* simptr = this;
        setup_historical *historical = new setup_historical(this, simptr);
        historical->setWindowFlags(Qt::Window);
        historical->show();
    } else {
        simulation* simptr = this;
        setup_custom *custom = new setup_custom(this, simptr);
        custom->setWindowFlags(Qt::Window);
        custom->show();
    }
}


void simulation::on_encrypt_clicked()
{
    input_message = ui->InputText->toPlainText();
    std::string message;

    if(count_of_rotors == 3) {
        rotor Rotor1(initial_position_rotor[0], notch_position_on_rotor[0], initial_ring_position_rotor[0], initial_combination_rotor[0]);
        rotor Rotor2(initial_position_rotor[1], notch_position_on_rotor[1], initial_ring_position_rotor[1], initial_combination_rotor[1]);
        rotor Rotor3(initial_position_rotor[2], notch_position_on_rotor[2], initial_ring_position_rotor[2], initial_combination_rotor[2]);

        reflector Reflector(reflector_version, reflector_combination);

        plugboard Plugboard(plugboard_combination);

        enigma_m3 Enigma_m3(Rotor1, Rotor2, Rotor3, Reflector, Plugboard);

        message = Enigma_m3.encrypt_the_message(input_message.toStdString());
    } else if(count_of_rotors == 4) {
        rotor Rotor1(initial_position_rotor[0], notch_position_on_rotor[0], initial_ring_position_rotor[0], initial_combination_rotor[0]);
        rotor Rotor2(initial_position_rotor[1], notch_position_on_rotor[1], initial_ring_position_rotor[1], initial_combination_rotor[1]);
        rotor Rotor3(initial_position_rotor[2], notch_position_on_rotor[2], initial_ring_position_rotor[2], initial_combination_rotor[2]);
        rotor Rotor4(initial_position_rotor[3], notch_position_on_rotor[3], initial_ring_position_rotor[3], initial_combination_rotor[3]);

        reflector Reflector(reflector_version, reflector_combination);

        plugboard Plugboard(plugboard_combination);

        enigma_m4 Enigma_m4(Rotor1, Rotor2, Rotor3, Rotor4, Reflector, Plugboard);

        message = Enigma_m4.encrypt_the_message(input_message.toStdString());
    } else if(count_of_rotors != 0){
        std::vector<rotor> Rotors;
        for(int i = 0; i < count_of_rotors; i++) {
            rotor Rotor(initial_position_rotor[i], notch_position_on_rotor[i], initial_ring_position_rotor[i], initial_combination_rotor[i]);
            Rotors.push_back(Rotor);
        }

        reflector Reflector(reflector_version, reflector_combination);

        plugboard Plugboard(plugboard_combination);

        enigma_custom Enigma_custom(Rotors, Reflector, Plugboard);

        message = Enigma_custom.encrypt_the_message(input_message.toStdString());
    }

    output_message = output_message.fromStdString(message);
    ui->OutputText->setPlainText(output_message);

}

bool first_time = true;

void simulation::print_combination(std::vector<char> combination, int rotor_number) {
    QTextStream out(&file_);

    if(first_time == true) {
        first_time = false;
        out << "{" << "\n";
    }

    out << "    \"combination_rotor_" << rotor_number <<"\": " <<"\"";

    for (const char i : combination) {
        out << i;
    }

    out <<"\"," << "\n";
}

void simulation::print_combination(std::vector<char> combination, std::string name) {
    QTextStream out(&file_);

    out << "    \"combination_" << QString::fromStdString(name) << "_\": " <<"\"";

    for (const char i : combination) {
        out << i;
    }

    out <<"\"," << "\n";
}

void simulation::save_file(QString filePath) {
    file_.setFileName(filePath);

    EnigmaSimulator *main = qobject_cast<EnigmaSimulator*>(this->parent());

    if (file_.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file_);

        out << "    \"mode\": " <<"\"" << QString::fromStdString((main->show_mode())) << "\"," << "\n";
        out << "    \"rotor_count\": " << count_of_rotors << ",\n";
        for(int i = 0; i < count_of_rotors; i++) {
            out << "    \"initial_position_" << i << "\": " << initial_position_rotor[i] << ",\n";
            out << "    \"notch_position_" << i << "\": " << notch_position_on_rotor[i] << ",\n";
            if(!notch_position_on_rotor_2.empty()){
                out << "    \"notch_position_2" << i << "\": " << notch_position_on_rotor_2[i] << ",\n";
            } else {
                out << "    \"notch_position_2" << i << "\": " << (-1) << ",\n";
            }
            out << "    \"ring_position_" << i << "\": " << initial_ring_position_rotor[i] << ",\n";

            print_combination(initial_combination_rotor[i], i);
        }

        out << "    \"reflector_version\": " <<"\"" << reflector_version <<"\"" << "\n";
        print_combination(reflector_combination, "reflector");
        print_combination(plugboard_combination, "plugboard");

        out << "}";

        file_.close();
        QMessageBox::information(this, "File", "Saved");
    } else {
        QMessageBox::warning(this, "ERROR", "Failed to save the file.");
    }
}

void simulation::load_file(QString filePath) {
    file_.setFileName(filePath);

    if (!file_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "ERROR", "Failed to open a file");
    }

    QByteArray jsonData = file_.readAll();
    file_.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Błąd parsowania JSON:" << parseError.errorString();
    }

    if (!doc.isObject()) {
        qDebug() << "Plik JSON nie zawiera obiektu głównego.";
    }

    QJsonObject obj = doc.object();
    count_of_rotors = (obj.value("rotor_count").toInt());

    QString pos = "initial_position_", notch1 = "notch_position_", notch2 = "notch_position_2", ring = "ring_position_", comb = "combination_rotor_";
    std::string number = "0";
    for(int i = 0; i < count_of_rotors; i++) {
        pos += number;
        notch1 += number;
        notch2 += number;
        ring += number;
        comb += number;
        initial_position_rotor.push_back(obj.value(pos).toInt());
        notch_position_on_rotor.push_back(obj.value(notch1).toInt());
        notch_position_on_rotor_2.push_back(obj.value(notch2).toInt());
        initial_ring_position_rotor.push_back(obj.value(ring).toInt());
        std::string current_combination = (obj.value(comb).toString()).toStdString();
        std::vector<char> ChrCurrentCombiniaton;

        for(int j = 0;j < current_combination.size(); j++) {
            ChrCurrentCombiniaton.push_back(current_combination[j]);
        }

        initial_combination_rotor.push_back(ChrCurrentCombiniaton);

        pos = "initial_position_";
        notch1 = "notch_position_";
        notch2 = "notch_position_2";
        ring = "ring_position_";
        comb = "combination_rotor_";

        number[0]++;
    }

    std::string current_reflector = (obj.value("combination_reflector_").toString()).toStdString();

    for(char i : current_reflector) {
        reflector_combination.push_back(i);
    }

    std::string current_plugboard = (obj.value("combination_plugboard_").toString()).toStdString();

    for(char i : current_plugboard) {
        plugboard_combination.push_back(i);
    }
}
