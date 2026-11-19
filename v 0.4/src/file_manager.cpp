
#include "file_manager.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <algorithm>

using namespace std;

namespace file_manager {

    namespace fs = std::filesystem;

    const string DATA_PATH = "data/";
    const string SAVES_PATH = "saves/";

    const int SAVE_VERSION = 1;
    const int STUDY_DAYS = 5;


    // ==============================
    // ИНИЦИАЛИЗАЦИЯ ФАЙЛОВ
    // ==============================

    void initialize() {

        fs::create_directories(DATA_PATH);
        fs::create_directories(SAVES_PATH);

        // Создание файла специальностей
        ifstream specialtiesFile(DATA_PATH + "specialties.txt");

        if (!specialtiesFile.is_open()) {

            ofstream file(DATA_PATH + "specialties.txt");

            file << "Программная инженерия\n";
            file << "Информационные системы\n";
            file << "Информационная безопасность\n";
            file << "Компьютерные науки\n";
        }

        // Создание файла имен
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


    // ==============================
    // РАБОТА С НАСТРОЙКАМИ
    // ==============================

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

            file.close();
            saveSettings(settings);

            return settings;
        }

        stringstream ss(subjectsLine);

        int subjects;
        string extra;

        if (!(ss >> subjects) || (ss >> extra) || subjects < 0) {

            file.close();
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


    // ==============================
    // РАБОТА СО СПЕЦИАЛЬНОСТЯМИ
    // ==============================

    set<string> loadSpecialties() {

        set<string> specialties;

        ifstream file(DATA_PATH + "specialties.txt");

        string specialty;

        while (getline(file, specialty)) {

            if (!specialty.empty()) {
                specialties.insert(specialty);
            }
        }

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


    // ==============================
    // РАБОТА С ИМЕНАМИ
    // ==============================

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


    // ==============================
    // СОЗДАНИЕ СОХРАНЕНИЯ
    // ==============================

    bool saveGame(
        const string& title,
        const game::Student& student,
        int currentDay
    ) {

        if (title.empty() || student.getSubjectsCount() == 0) {
            return false;
        }

        // Создаем папку сохранений
        error_code ec;

        fs::create_directories(SAVES_PATH, ec);

        if (ec) {
            return false;
        }

        // Генерируем уникальное имя файла
        auto now = chrono::system_clock::now();

        auto timestamp = chrono::duration_cast<chrono::microseconds>(
            now.time_since_epoch()
        ).count();

        string filename = "save_" + to_string(timestamp) + ".sav";

        fs::path filePath = fs::path(SAVES_PATH) / filename;

        int suffix = 1;

        while (fs::exists(filePath)) {

            filename = "save_" + to_string(timestamp) +
                       "_" + to_string(suffix) + ".sav";

            filePath = fs::path(SAVES_PATH) / filename;

            suffix++;
        }

        ofstream file(filePath);

        if (!file.is_open()) {
            cerr << "Ошибка создания сохранения!\n";
            return false;
        }

        // Запись версии формата
        file << SAVE_VERSION << '\n';

        // Название сохранения
        file << quoted(title) << '\n';

        // Текущий день и характеристики студента
        file << currentDay << ' '
             << student.getEnergy() << ' '
             << student.getDiscipline() << ' '
             << student.getProblemSolving() << '\n';

        // Имя и специальность
        file << quoted(student.getName()) << '\n';
        file << quoted(student.getSpecialty()) << '\n';

        // Количество предметов
        file << student.getSubjectsCount() << '\n';

        // Прогресс каждого предмета
        for (
            size_t i = 0;
            i < student.getSubjectsCount();
            i++
        ) {

            const game::Subject& subject = student.getSubject(i);

            file << subject.getKnowledge() << ' '
                 << subject.getAttendedDays() << ' '
                 << subject.getSkippedDays() << '\n';
        }

        file.close();

        if (file.fail()) {
            return false;
        }

        return true;
    }


    // ==============================
    // СПИСОК СОХРАНЕНИЙ
    // ==============================

    vector<SaveInfo> listSaves() {

        vector<SaveInfo> saves;

        error_code ec;

        fs::create_directories(SAVES_PATH, ec);

        if (ec) {
            return saves;
        }

        // Перебираем все файлы в папке saves
        for (
            const auto& entry : fs::directory_iterator(SAVES_PATH, ec)
        ) {

            if (ec) {
                break;
            }

            if (!entry.is_regular_file()) {
                continue;
            }

            if (entry.path().extension() != ".sav") {
                continue;
            }

            ifstream file(entry.path());

            if (!file.is_open()) {
                continue;
            }

            int version;
            string title;

            // Читаем версию и название сохранения
            if (file >> version >> quoted(title)) {

                if (version == SAVE_VERSION && !title.empty()) {

                    saves.push_back({
                        title,
                        entry.path().string()
                    });
                }
            }
        }

        // Сортировка по имени файла
        sort(
            saves.begin(),
            saves.end(),
            [](const SaveInfo& a, const SaveInfo& b) {
                return a.filePath > b.filePath;
            }
        );

        return saves;
    }


    // ==============================
    // ЗАГРУЗКА СОХРАНЕНИЯ
    // ==============================

    optional<game::Student> loadGame(
        const SaveInfo& save,
        int& currentDay
    ) {

        ifstream file(save.filePath);

        if (!file.is_open()) {
            return nullopt;
        }

        int version;
        string title;

        int savedDay;
        int energy;
        int discipline;
        int problemSolving;

        string studentName;
        string specialty;

        int subjectsCount;

        // Чтение основной информации
        if (!(file >> version >> quoted(title))) {
            return nullopt;
        }

        if (version != SAVE_VERSION || title != save.title) {
            return nullopt;
        }

        if (!(file >> savedDay
                   >> energy
                   >> discipline
                   >> problemSolving)) {
            return nullopt;
        }

        // Проверка характеристик
        if (
            savedDay < 1 ||
            savedDay > STUDY_DAYS + 1 ||
            energy < 0 || energy > 100 ||
            discipline < 0 || discipline > 100 ||
            problemSolving < 0 || problemSolving > 100
        ) {
            return nullopt;
        }

        // Чтение имени и специальности
        if (!(file >> quoted(studentName) >> quoted(specialty))) {
            return nullopt;
        }

        // Чтение количества предметов
        if (!(file >> subjectsCount)) {
            return nullopt;
        }

        if (subjectsCount <= 0 || subjectsCount > 1000) {
            return nullopt;
        }

        // Создаем студента с сохраненными данными
        game::Student student(
            studentName,
            specialty,
            subjectsCount
        );

        student.setCharacteristics(
            energy,
            discipline,
            problemSolving
        );

        // Восстанавливаем прогресс каждого предмета
        for (int i = 0; i < subjectsCount; i++) {

            int knowledge;
            int attended;
            int skipped;

            if (!(file >> knowledge >> attended >> skipped)) {
                return nullopt;
            }

            if (
                knowledge < 0 || knowledge > 100 ||
                attended < 0 ||
                skipped < 0 ||
                attended + skipped > STUDY_DAYS
            ) {
                return nullopt;
            }

            student.getSubject(i).setProgress(
                knowledge,
                attended,
                skipped
            );
        }

        currentDay = savedDay;

        return student;
    }


    // ==============================
    // УДАЛЕНИЕ СОХРАНЕНИЯ
    // ==============================

    bool deleteSave(const SaveInfo& save) {

        error_code ec;

        bool removed = fs::remove(save.filePath, ec);

        if (ec || !removed) {
            return false;
        }

        return true;
    }

}
