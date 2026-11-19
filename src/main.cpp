#include "game_settings.h"
#include "output.h"
#include "file_manager.h"

using namespace std;

int main() {
    // Инициализация файлов
    file_manager::initialize();

    // Загрузка данных
    GameSettings settings = file_manager::loadSettings();

    set<string> specialties = file_manager::loadSpecialties();

    list<string> studentNames = file_manager::loadStudentNames();

    // Запуск главного меню
    output::mainMenu(settings, specialties, studentNames);

    return 0;
}
