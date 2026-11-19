
#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include <set>
#include <list>

#include "game_settings.h"

namespace output {

    // Ввод данных
    int readNumber(const std::string& prompt);
    std::string readText(const std::string& prompt);
    void waitForEnter();

    // Главное меню
    void mainMenu(
        GameSettings& settings,
        const std::set<std::string>& specialties,
        std::list<std::string>& studentNames
    );

    // Подменю настроек
    void settingsMenu(
        GameSettings& settings,
        const std::set<std::string>& specialties,
        std::list<std::string>& studentNames
    );

    // Изменение настроек
    void changeSpecialty(
        GameSettings& settings,
        const std::set<std::string>& specialties
    );

    void changeName(
        GameSettings& settings,
        std::list<std::string>& studentNames
    );

    void changeSubjects(GameSettings& settings);

    // Вывод информации
    void showAbout();
    void showStartGame(const GameSettings& settings);
    void showLoadGame();

    // Получение данных
    int chooseSpecialty(const std::set<std::string>& specialties);

    std::string askStudentName(
        const std::list<std::string>& studentNames
    );

    int askSubjects();

}

#endif
