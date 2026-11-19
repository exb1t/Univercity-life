
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "game.h"
#include "game_settings.h"

#include <string>
#include <set>
#include <list>
#include <vector>
#include <optional>

namespace file_manager {

    struct SaveInfo {
        std::string title;
        std::string filePath;
    };

    // Настройки программы
    void initialize();

    GameSettings loadSettings();
    void saveSettings(const GameSettings& settings);

    std::set<std::string> loadSpecialties();

    std::list<std::string> loadStudentNames();
    void saveStudentNames(const std::list<std::string>& studentNames);

    // Сохранения игры
    bool saveGame(
        const std::string& title,
        const game::Student& student,
        int currentDay
    );

    std::vector<SaveInfo> listSaves();

    std::optional<game::Student> loadGame(
        const SaveInfo& save,
        int& currentDay
    );

    bool deleteSave(const SaveInfo& save);

}

#endif
