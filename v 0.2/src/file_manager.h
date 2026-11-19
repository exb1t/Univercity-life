
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "game_settings.h"

#include <string>
#include <set>
#include <list>

namespace file_manager {

    // Инициализация папки с файлами
    void initialize();

    // Работа с настройками
    GameSettings loadSettings();
    void saveSettings(const GameSettings& settings);

    // Работа со специальностями
    std::set<std::string> loadSpecialties();

    // Работа с именами студентов
    std::list<std::string> loadStudentNames();
    void saveStudentNames(const std::list<std::string>& studentNames);

}

#endif
