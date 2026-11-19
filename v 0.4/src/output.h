
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

    // Настройки
    void settingsMenu(
        GameSettings& settings,
        const std::set<std::string>& specialties,
        std::list<std::string>& studentNames
    );

    void changeSpecialty(
        GameSettings& settings,
        const std::set<std::string>& specialties
    );

    void changeName(
        GameSettings& settings,
        std::list<std::string>& studentNames
    );

    void changeSubjects(GameSettings& settings);

    // Информация о программе
    void showAbout();

    // Игровой процесс
    void startGame(const GameSettings& settings);

    // Работа с сохранениями
    void manageSaves();

    // Получение данных
    int chooseSpecialty(const std::set<std::string>& specialties);

    std::string askStudentName(
        const std::list<std::string>& studentNames
    );

    int askSubjects();

}

#endif
