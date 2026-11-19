
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <limits>

using namespace std;

// Константы главного меню
const int START_GAME = 1;
const int LOAD_GAME = 2;
const int SETTINGS = 3;а
const int ABOUT = 4;
const int EXIT = 5;

// Константы меню настроек
const int CHANGE_SPECIALTY = 1;
const int CHANGE_NAME = 2;
const int CHANGE_SUBJECTS = 3;
const int BACK = 4;

// Данные игры
struct GameSettings {
    string specialty = "Не выбрана";
    string studentName = "Не указано";
    int subjects = 5;
};

// Функция безопасного ввода числа
int readNumber() {
    string input;
    int number;
    
    while (true) {
        getline(cin, input);
        stringstream ss(input);

        if (ss >> number && !(ss >> input)) {
            return number;
        }

        cout << "Ошибка! Введите число: ";
    }
}

// Функция начала игры
void waitForEnter() {
    cout << "\nНажмите Enter, чтобы вернуться в главное меню...";
    cin.get();
}

void startGame(const GameSettings& settings) {
    cout << "\n=== НАЧАЛО ИГРЫ ===\n";
    cout << "Добро пожаловать в университет!\n";

    waitForEnter();
}

void loadGame() {
    cout << "\nЗагрузка игры пока недоступна.\n";
    cout << "Эта функция появится в ближайших обновлениях!\n";

    waitForEnter();
}

void about() {
    cout << "\n========== О ПРОГРАММЕ ==========\n";
    cout << "Название: Моя веселая жизнь в универе\n";
    cout << "Версия: 0.2\n";
    cout << "Разработчик: Песков Дмитрий\n";

    waitForEnter();
}

// Функция изменения специальности
void changeSpecialty(GameSettings& settings) {
    cout << "\nВведите название специальности: ";
    getline(cin, settings.specialty);

    cout << "Специальность успешно изменена!\n";
}

// Функция изменения имени студента
void changeName(GameSettings& settings) {
    cout << "\nВведите имя студента: ";
    getline(cin, settings.studentName);

    cout << "Имя успешно изменено!\n";
}

// Функция изменения количества предметов
void changeSubjects(GameSettings& settings) {
    cout << "\nВведите количество предметов: ";

    int number;

    do {
        number = readNumber();

        if (number <= 0) {
            cout << "Количество предметов должно быть больше нуля: ";
        }

    } while (number <= 0);

    settings.subjects = number;

    cout << "Количество предметов успешно изменено!\n";
}

// Подменю настроек
void settingsMenu(GameSettings& settings) {
    int choice;

    do {
        cout << "\n========== НАСТРОЙКИ ==========\n";
        cout << "1. Выбрать специальность (" << settings.specialty << ")\n";
        cout << "2. Изменить имя студента (" << settings.studentName << ")\n";
        cout << "3. Изменить количество предметов (" << settings.subjects << ")\n";
        cout << "4. Назад\n";
        cout << "Выберите пункт: ";

        choice = readNumber();

        switch (choice) {
            case CHANGE_SPECIALTY:
                changeSpecialty(settings);
                break;

            case CHANGE_NAME:
                changeName(settings);
                break;

            case CHANGE_SUBJECTS:
                changeSubjects(settings);
                break;

            case BACK:
                cout << "\nВозвращение в главное меню...\n";
                break;

            default:
                cout << "\nНеверный пункт меню!\n";
        }

    } while (choice != BACK);
}

// Главное меню
void mainMenu() {
    GameSettings settings;
    int choice;

    do {
        cout << "\n================================\n";
        cout << "   МОЯ ВЕСЕЛАЯ ЖИЗНЬ В УНИВЕРЕ\n";
        cout << "================================\n";
        cout << "1. Начать игру\n";
        cout << "2. Загрузить игру\n";
        cout << "3. Настройки\n";
        cout << "4. О программе\n";
        cout << "5. Выход\n";
        cout << "================================\n";
        cout << "Выберите пункт меню: ";

        choice = readNumber();

        switch (choice) {
            case START_GAME:
                startGame(settings);
                break;

            case LOAD_GAME:
                loadGame();
                break;

            case SETTINGS:
                settingsMenu(settings);
                break;

            case ABOUT:
                about();
                break;

            case EXIT:
                cout << "\nЗавершение работы программы...\n";
                break;

            default:
                cout << "\nНеверный пункт меню! Попробуйте снова.\n";
        }

    } while (choice != EXIT);
}

int main() {
    SetConsoleCP(65001);       // Ввод в UTF-8
    SetConsoleOutputCP(65001); // Вывод в UTF-8

    mainMenu();

    return 0;
}
