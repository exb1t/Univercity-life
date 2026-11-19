
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "game_settings.h"

#include <string>
#include <set>
#include <list>

namespace file_manager {

    void initialize();

    GameSettings loadSettings();
    void saveSettings(const GameSettings& settings);

    std::set<std::string> loadSpecialties();

    std::list<std::string> loadStudentNames();
    void saveStudentNames(const std::list<std::string>& studentNames);

}

#endif
