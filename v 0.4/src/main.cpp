
#include <iostream>
#include <windows.h>
#include <set>
#include <list>

#include "game_settings.h"
#include "output.h"
#include "file_manager.h"

using namespace std;

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Инициализация файлов
    file_manager::initialize();

    // Загрузка настроек
    GameSettings settings = file_manager::loadSettings();

    // Загрузка специальностей
    set<string> specialties =
        file_manager::loadSpecialties();

    // Загрузка имен студентов
    list<string> studentNames =
        file_manager::loadStudentNames();

    // Запуск главного меню
    output::mainMenu(
        settings,
        specialties,
        studentNames
    );

    return 0;
}
