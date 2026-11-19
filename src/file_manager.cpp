
#include "file_manager.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>

using namespace std;

namespace file_manager {

    const string DATA_PATH = "data/";

    // Создание папки и файлов при первом запуске
    void initialize() {
        filesystem::create_directories(DATA_PATH);

        // Создание файла специальностей
        ifstream specialtiesFile(DATA_PATH + "specialties.txt");

        if (!specialtiesFile.is_open()) {
            ofstream file(DATA_PATH + "specialties.txt");

            file << "Программная инженерия\n";
            file << "Информационные системы\n";
            file << "Информационная безопасность\n";
            file << "Компьютерные науки\n";
        }

        // Создание пустого файла имен
        ifstream studentsFile(DATA_PATH + "students.txt");

        if (!studentsFile.is_open()) {
            ofstream file(DATA_PATH + "students.txt");
        }

        // Создание настроек по умолчанию
        ifstream settingsFile(DATA_PATH + "settings.txt");

        if (!settingsFile.is_open()) {
            GameSettings settings;
            saveSettings(settings);
        }
    }

    // Сохранение настроек
    void saveSettings(const GameSettings& settings) {
        ofstream file(DATA_PATH + "settings.txt");

        if (!file.is_open()) {
            cerr << "Ошибка сохранения настроек!\n";
            return;
        }

        file << settings.specialty << endl;
        file << settings.studentName << endl;
        file << settings.subjects << endl;
    }

    // Загрузка настроек
    GameSettings loadSettings() {
        GameSettings settings;

        ifstream file(DATA_PATH + "settings.txt");

        if (!file.is_open()) {
            return settings;
        }

        string specialty;
        string studentName;
        string subjectsLine;

        if (!getline(file, specialty) ||
            !getline(file, studentName) ||
            !getline(file, subjectsLine)) {

            cout << "Ошибка чтения настроек. Используются значения по умолчанию.\n";

            saveSettings(settings);
            return settings;
        }

        stringstream ss(subjectsLine);

        int subjects;
        string extra;

        if (!(ss >> subjects) || (ss >> extra) || subjects <= 0) {
            cout << "Некорректное количество предметов. Используются значения по умолчанию.\n";

            saveSettings(settings);
            return settings;
        }

        if (!specialty.empty()) {
            settings.specialty = specialty;
        }

        if (!studentName.empty()) {
            settings.studentName = studentName;
        }

        settings.subjects = subjects;

        return settings;
    }

    // Загрузка специальностей в Set
    set<string> loadSpecialties() {
        set<string> specialties;

        ifstream file(DATA_PATH + "specialties.txt");

        string specialty;

        while (getline(file, specialty)) {
            if (!specialty.empty()) {
                specialties.insert(specialty);
            }
        }

        // Если файл пустой, восстанавливаем значения по умолчанию
        if (specialties.empty()) {
            ofstream output(DATA_PATH + "specialties.txt");

            output << "Программная инженерия\n";
            output << "Информационные системы\n";
            output << "Информационная безопасность\n";
            output << "Компьютерные науки\n";

            specialties.insert("Программная инженерия");
            specialties.insert("Информационные системы");
            specialties.insert("Информационная безопасность");
            specialties.insert("Компьютерные науки");
        }

        return specialties;
    }

    // Загрузка имен студентов в List
    list<string> loadStudentNames() {
        list<string> studentNames;

        ifstream file(DATA_PATH + "students.txt");

        string name;

        while (getline(file, name)) {
            if (!name.empty()) {
                studentNames.push_back(name);
            }
        }

        return studentNames;
    }

    // Сохранение имен студентов
    void saveStudentNames(const list<string>& studentNames) {
        ofstream file(DATA_PATH + "students.txt");

        if (!file.is_open()) {
            cerr << "Ошибка сохранения имен студентов!\n";
            return;
        }

        for (const string& name : studentNames) {
            file << name << endl;
        }
    }

}
