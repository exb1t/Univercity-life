
#include "output.h"
#include "file_manager.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

namespace output {

    // Константы главного меню
    const int START_GAME = 1;
    const int LOAD_GAME = 2;
    const int SETTINGS = 3;
    const int ABOUT = 4;
    const int EXIT = 5;

    // Константы меню настроек
    const int CHANGE_SPECIALTY = 1;
    const int CHANGE_NAME = 2;
    const int CHANGE_SUBJECTS = 3;
    const int BACK = 4;


    // Безопасный ввод числа
    int readNumber(const string& prompt) {
        string input;
        int number;

        while (true) {
            cout << prompt;
            getline(cin, input);

            stringstream ss(input);

            if (ss >> number && !(ss >> input)) {
                return number;
            }

            cout << "Ошибка! Введите целое число.\n";
        }
    }


    // Ввод строки
    string readText(const string& prompt) {
        string input;

        cout << prompt;
        getline(cin, input);

        return input;
    }


    // Ожидание Enter
    void waitForEnter() {
        cout << "\nНажмите Enter, чтобы вернуться в главное меню...";
        cin.get();
    }


    // Вывод главного меню
    void showMainMenu() {
        cout << "\n================================\n";
        cout << "   МОЯ ВЕСЕЛАЯ ЖИЗНЬ В УНИВЕРЕ\n";
        cout << "================================\n";
        cout << "1. Начать игру\n";
        cout << "2. Загрузить игру\n";
        cout << "3. Настройки\n";
        cout << "4. О программе\n";
        cout << "5. Выход\n";
        cout << "================================\n";
    }


    // Вывод меню настроек
    void showSettingsMenu(const GameSettings& settings) {
        cout << "\n========== НАСТРОЙКИ ==========\n";

        cout << "1. Выбрать специальность ("
             << settings.specialty << ")\n";

        cout << "2. Изменить имя студента ("
             << settings.studentName << ")\n";

        cout << "3. Изменить количество предметов ("
             << settings.subjects << ")\n";

        cout << "4. Назад\n";
    }


    // Информация о программе
    void showAbout() {
        cout << "\n========== О ПРОГРАММЕ ==========\n";
        cout << "Название: Моя веселая жизнь в универе\n";
        cout << "Версия: 2.0\n";
        cout << "Разработчик: Ваше имя и фамилия\n";

        waitForEnter();
    }


    // Начало игры
    void showStartGame(const GameSettings& settings) {
        cout << "\n=== НАЧАЛО ИГРЫ ===\n";
        cout << "Добро пожаловать в университет!\n";

        cout << "Студент: " << settings.studentName << endl;
        cout << "Специальность: " << settings.specialty << endl;
        cout << "Количество предметов: " << settings.subjects << endl;

        waitForEnter();
    }


    // Загрузка игры
    void showLoadGame() {
        cout << "\nЗагрузка игры пока недоступна.\n";
        cout << "Эта функция появится в ближайших обновлениях!\n";

        waitForEnter();
    }


    // Выбор специальности
    int chooseSpecialty(const set<string>& specialties) {
        cout << "\n========== СПЕЦИАЛЬНОСТИ ==========\n";

        int index = 1;

        for (const string& specialty : specialties) {
            cout << index << ". " << specialty << endl;
            index++;
        }

        return readNumber("\nВыберите специальность: ");
    }


    // Изменение специальности
    void changeSpecialty(
        GameSettings& settings,
        const set<string>& specialties
    ) {
        int choice = chooseSpecialty(specialties);

        if (choice < 1 || choice > specialties.size()) {
            cout << "Неверный номер специальности!\n";
            return;
        }

        auto it = specialties.begin();
        advance(it, choice - 1);

        settings.specialty = *it;

        file_manager::saveSettings(settings);

        cout << "Специальность успешно изменена!\n";
    }


    // Получение имени студента
    string askStudentName(const list<string>& studentNames) {
        cout << "\n========== ИМЕНА СТУДЕНТОВ ==========\n";

        if (studentNames.empty()) {
            cout << "Список имен пока пуст.\n";
        }
        else {
            cout << "Ранее введенные имена:\n";

            for (const string& name : studentNames) {
                cout << "- " << name << endl;
            }
        }

        return readText("\nВведите имя студента: ");
    }


    // Изменение имени студента
    void changeName(
        GameSettings& settings,
        list<string>& studentNames
    ) {
        string newName = askStudentName(studentNames);

        if (newName.empty()) {
            cout << "Имя не может быть пустым!\n";
            return;
        }

        settings.studentName = newName;

        auto it = find(
            studentNames.begin(),
            studentNames.end(),
            newName
        );

        if (it == studentNames.end()) {
            studentNames.push_back(newName);

            file_manager::saveStudentNames(studentNames);
        }

        file_manager::saveSettings(settings);

        cout << "Имя успешно изменено!\n";
    }


    // Получение количества предметов
    int askSubjects() {
        int number;

        do {
            number = readNumber("\nВведите количество предметов: ");

            if (number <= 0) {
                cout << "Количество предметов должно быть больше нуля!\n";
            }

        } while (number <= 0);

        return number;
    }


    // Изменение количества предметов
    void changeSubjects(GameSettings& settings) {
        settings.subjects = askSubjects();

        file_manager::saveSettings(settings);

        cout << "Количество предметов успешно изменено!\n";
    }


    // Подменю настроек
    void settingsMenu(
        GameSettings& settings,
        const set<string>& specialties,
        list<string>& studentNames
    ) {
        int choice;

        do {
            showSettingsMenu(settings);

            choice = readNumber("Выберите пункт: ");

            switch (choice) {
                case CHANGE_SPECIALTY:
                    changeSpecialty(settings, specialties);
                    break;

                case CHANGE_NAME:
                    changeName(settings, studentNames);
                    break;

                case CHANGE_SUBJECTS:
                    changeSubjects(settings);
                    break;

                case BACK:
                    cout << "\nВозвращение в главное меню...\n";
                    break;

                default:
                    cout << "Неверный пункт меню!\n";
            }

        } while (choice != BACK);
    }


    // Главное меню
    void mainMenu(
        GameSettings& settings,
        const set<string>& specialties,
        list<string>& studentNames
    ) {
        int choice;

        do {
            showMainMenu();

            choice = readNumber("Выберите пункт меню: ");

            switch (choice) {
                case START_GAME:
                    showStartGame(settings);
                    break;

                case LOAD_GAME:
                    showLoadGame();
                    break;

                case SETTINGS:
                    settingsMenu(settings, specialties, studentNames);
                    break;

                case ABOUT:
                    showAbout();
                    break;

                case EXIT:
                    cout << "\nЗавершение работы программы...\n";
                    break;

                default:
                    cout << "\nНеверный пункт меню! Попробуйте снова.\n";
            }

        } while (choice != EXIT);
    }

}
