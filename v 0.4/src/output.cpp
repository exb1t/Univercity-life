
#include "output.h"

#include "file_manager.h"
#include "game.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <vector>

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

    const int STUDY_DAYS = 5;


    // ==============================
    // ВВОД И ВЫВОД
    // ==============================

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


    string readText(const string& prompt) {

        string input;

        cout << prompt;
        getline(cin, input);

        return input;
    }


    void waitForEnter() {

        cout << "\nНажмите Enter, чтобы продолжить...";
        cin.get();
    }


    // ==============================
    // МЕНЮ
    // ==============================

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


    void showAbout() {

        cout << "\n========== О ПРОГРАММЕ ==========\n";
        cout << "Название: Моя веселая жизнь в универе\n";
        cout << "Версия: 0.4\n";
        cout << "Разработчик: Песков Дмитрий\n";

        waitForEnter();
    }


    // ==============================
    // ИЗМЕНЕНИЕ НАСТРОЕК
    // ==============================

    int chooseSpecialty(const set<string>& specialties) {

        cout << "\n========== СПЕЦИАЛЬНОСТИ ==========\n";

        int index = 1;

        for (const string& specialty : specialties) {

            cout << index << ". " << specialty << endl;
            index++;
        }

        return readNumber("\nВыберите специальность: ");
    }


    void changeSpecialty(
        GameSettings& settings,
        const set<string>& specialties
    ) {

        int choice = chooseSpecialty(specialties);

        if (choice < 1 ||
            choice > static_cast<int>(specialties.size())) {

            cout << "Неверный номер специальности!\n";
            return;
        }

        auto it = specialties.begin();

        advance(it, choice - 1);

        settings.specialty = *it;

        file_manager::saveSettings(settings);

        cout << "Специальность успешно изменена!\n";
    }


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


    int askSubjects() {

        int number;

        do {

            number = readNumber("\nВведите количество предметов: ");

            if (number <= 0 || number > 1000) {
                cout << "Введите количество от 1 до 1000!\n";
            }

        } while (number <= 0 || number > 1000);

        return number;
    }


    void changeSubjects(GameSettings& settings) {

        settings.subjects = askSubjects();

        file_manager::saveSettings(settings);

        cout << "Количество предметов успешно изменено!\n";
    }


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


    // ==============================
    // ВЫБОР ПРЕДМЕТА
    // ==============================

    size_t chooseSubjectForAction(const game::Student& student) {

        cout << "\nВыберите предмет:\n";

        for (size_t i = 0; i < student.getSubjectsCount(); i++) {

            cout << i + 1 << ". "
                 << student.getSubject(i).getName() << endl;
        }

        int choice;

        do {

            choice = readNumber("Ваш выбор: ");

            if (
                choice < 1 ||
                choice > static_cast<int>(student.getSubjectsCount())
            ) {
                cout << "Неверный номер предмета!\n";
            }

        } while (
            choice < 1 ||
            choice > static_cast<int>(student.getSubjectsCount())
        );

        return static_cast<size_t>(choice - 1);
    }


    // ==============================
    // ИГРОВОЙ ПРОЦЕСС
    // ==============================

    // student - объект студента
    // currentDay - день, с которого продолжается игра
    void playGame(game::Student& student, int currentDay) {

        // Учебные дни
        for (int day = currentDay; day <= STUDY_DAYS; day++) {

            cout << "\n================================\n";
            cout << "             ДЕНЬ " << day << "\n";
            cout << "================================\n";

            cout << "Энергия: " << student.getEnergy() << endl;
            cout << "Дисциплина: " << student.getDiscipline() << endl;

            cout << "Решение задач: "
                 << student.getProblemSolving() << endl;


            // Расписание занятий
            cout << "\n========== РАСПИСАНИЕ ==========\n";

            for (
                size_t i = 0;
                i < student.getSubjectsCount();
                i++
            ) {

                const game::Subject& subject = student.getSubject(i);

                cout << "\nПредмет: " << subject.getName() << endl;
                cout << "1. Посетить\n";
                cout << "2. Прогулять\n";

                int choice;

                do {

                    choice = readNumber("Ваш выбор: ");

                    if (choice != 1 && choice != 2) {
                        cout << "Выберите 1 или 2!\n";
                    }

                } while (choice != 1 && choice != 2);


                if (choice == 1) {

                    student.attendSubject(i);

                    cout << "Вы посетили занятие!\n";
                }
                else {

                    student.skipSubject(i);

                    cout << "Вы прогуляли занятие!\n";
                }
            }


            // Домашние дела
            cout << "\n========== ДОМАШНИЕ ДЕЛА ==========\n";

            cout << "1. Учиться\n";
            cout << "2. Решать задачи\n";
            cout << "3. Отдыхать\n";

            int activity;

            do {

                activity = readNumber("Чем займётесь дома? ");

                if (activity < 1 || activity > 3) {
                    cout << "Выберите действие от 1 до 3!\n";
                }

            } while (activity < 1 || activity > 3);


            switch (activity) {

                case 1: {

                    size_t index = chooseSubjectForAction(student);

                    game::Action action(game::ActionType::STUDY);

                    action.execute(
                        student,
                        &student.getSubject(index)
                    );

                    cout << "Вы позанимались выбранным предметом!\n";

                    break;
                }

                case 2: {

                    size_t index = chooseSubjectForAction(student);

                    game::Action action(
                        game::ActionType::SOLVE_TASKS
                    );

                    action.execute(
                        student,
                        &student.getSubject(index)
                    );

                    cout << "Вы решили несколько задач!\n";

                    break;
                }

                case 3: {

                    game::Action action(game::ActionType::REST);

                    action.execute(student);

                    cout << "Вы хорошо отдохнули!\n";

                    break;
                }
            }


            // Сохранение после завершения дня
            cout << "\n========== СЛЕДУЮЩИЙ ШАГ ==========\n";

            cout << "1. Продолжить игру\n";
            cout << "2. Сохранить игру и выйти в главное меню\n";

            int choice;

            do {

                choice = readNumber("Выберите действие: ");

                if (choice != 1 && choice != 2) {
                    cout << "Выберите 1 или 2!\n";
                }

            } while (choice != 1 && choice != 2);


            if (choice == 2) {

                string title;

                do {

                    title = readText("Введите название сохранения: ");

                    if (title.empty()) {
                        cout << "Название не может быть пустым!\n";
                    }

                } while (title.empty());


                // Сохраняем следующий день
                bool saved = file_manager::saveGame(
                    title,
                    student,
                    day + 1
                );

                if (saved) {
                    cout << "\nИгра успешно сохранена!\n";
                }
                else {
                    cout << "\nОшибка сохранения игры!\n";
                }

                waitForEnter();

                return;
            }
        }


        // ==============================
        // СЕССИЯ
        // ==============================

        cout << "\n================================\n";
        cout << "          НАЧАЛАСЬ СЕССИЯ!\n";
        cout << "================================\n";

        int totalGrade = 0;

        for (
            size_t i = 0;
            i < student.getSubjectsCount();
            i++
        ) {

            game::Subject& subject = student.getSubject(i);

            cout << "\n================================\n";

            cout << "Предмет: " << subject.getName() << endl;

            cout << "Посещено занятий: "
                 << subject.getAttendedDays() << endl;

            cout << "Пропущено занятий: "
                 << subject.getSkippedDays() << endl;

            cout << "Знания по предмету: "
                 << subject.getKnowledge() << endl;


            // Расчёт предварительной оценки
            int grade = student.calculateGrade(subject);

            cout << "\nВаша предварительная оценка: "
                 << grade << endl;


            // Экзаменационный вопрос
            const game::Question& question = subject.getQuestion();

            cout << "\nЭкзаменационный вопрос:\n";
            cout << question.text << endl;

            for (
                size_t j = 0;
                j < question.options.size();
                j++
            ) {

                cout << j + 1 << ". "
                     << question.options[j] << endl;
            }

            int answer;

            do {

                answer = readNumber("Ваш ответ: ");

                if (
                    answer < 1 ||
                    answer > static_cast<int>(question.options.size())
                ) {
                    cout << "Выберите один из предложенных вариантов!\n";
                }

            } while (
                answer < 1 ||
                answer > static_cast<int>(question.options.size())
            );


            // Проверка ответа
            if (subject.isCorrectAnswer(answer)) {

                cout << "\nПравильно! Дополнительный балл!\n";

                grade = min(10, grade + 1);
            }
            else {

                cout << "\nНеправильно!\n";

                cout << "Правильный ответ: "
                     << question.correctOption << ". "
                     << question.options[question.correctOption - 1]
                     << endl;
            }

            cout << "Итоговая оценка: " << grade << endl;

            totalGrade += grade;
        }


        // Итоговые результаты
        double averageGrade =
            static_cast<double>(totalGrade) /
            student.getSubjectsCount();

        cout << "\n================================\n";
        cout << "        СЕССИЯ ЗАВЕРШЕНА!\n";
        cout << "================================\n";

        cout << "Студент: " << student.getName() << endl;

        cout << "Средний балл: "
             << fixed << setprecision(1)
             << averageGrade << endl;

        cout << "\nИтоговые характеристики:\n";

        cout << "Энергия: " << student.getEnergy() << endl;
        cout << "Дисциплина: " << student.getDiscipline() << endl;

        cout << "Решение задач: "
             << student.getProblemSolving() << endl;

        waitForEnter();
    }


    // ==============================
    // НАЧАЛО НОВОЙ ИГРЫ
    // ==============================

    void startGame(const GameSettings& settings) {

        if (settings.subjects <= 0) {

            cout << "\nНевозможно начать игру!\n";
            cout << "Сначала установите количество предметов в настройках.\n";

            waitForEnter();
            return;
        }

        game::Student student(
            settings.studentName,
            settings.specialty,
            settings.subjects
        );

        cout << "\n================================\n";
        cout << "       СЕМЕСТР НАЧИНАЕТСЯ!\n";
        cout << "================================\n";

        cout << "Студент: " << student.getName() << endl;
        cout << "Специальность: " << student.getSpecialty() << endl;

        cout << "Количество предметов: "
             << student.getSubjectsCount() << endl;

        playGame(student, 1);
    }


    // ==============================
    // ЗАГРУЗКА И УДАЛЕНИЕ СОХРАНЕНИЙ
    // ==============================

    void manageSaves() {

        while (true) {

            vector<file_manager::SaveInfo> saves =
                file_manager::listSaves();

            cout << "\n========== СОХРАНЕНИЯ ==========\n";

            if (saves.empty()) {

                cout << "Сохранения не найдены.\n";

                waitForEnter();
                return;
            }

            // Вывод списка сохранений
            for (size_t i = 0; i < saves.size(); i++) {

                cout << i + 1 << ". "
                     << saves[i].title << endl;
            }

            cout << "0. Назад\n";

            int choice = readNumber("\nВыберите сохранение: ");

            if (choice == 0) {
                return;
            }

            if (
                choice < 1 ||
                choice > static_cast<int>(saves.size())
            ) {

                cout << "Неверный номер сохранения!\n";
                continue;
            }

            // Получение выбранного сохранения
            const file_manager::SaveInfo& selectedSave =
                saves[choice - 1];

            cout << "\nВыбрано сохранение: "
                 << selectedSave.title << endl;

            cout << "\n1. Загрузить игру\n";
            cout << "2. Удалить сохранение\n";
            cout << "3. Назад\n";

            int action = readNumber("Выберите действие: ");


            switch (action) {

                // Загрузка сохранения
                case 1: {

                    int currentDay = 1;

                    optional<game::Student> student =
                        file_manager::loadGame(
                            selectedSave,
                            currentDay
                        );

                    if (!student.has_value()) {

                        cout << "\nНе удалось загрузить сохранение!\n";

                        waitForEnter();
                        break;
                    }

                    cout << "\nСохранение успешно загружено!\n";

                    cout << "Студент: "
                         << student->getName() << endl;

                    cout << "Продолжение с дня: "
                         << currentDay << endl;

                    playGame(*student, currentDay);

                    return;
                }


                // Удаление сохранения
                case 2: {

                    cout << "\nВы действительно хотите удалить сохранение \""
                         << selectedSave.title << "\"?\n";

                    cout << "1. Да\n";
                    cout << "2. Нет\n";

                    int confirm = readNumber("Ваш выбор: ");

                    if (confirm == 1) {

                        if (file_manager::deleteSave(selectedSave)) {

                            cout << "\nСохранение успешно удалено!\n";
                        }
                        else {

                            cout << "\nОшибка удаления сохранения!\n";
                        }
                    }
                    else {

                        cout << "\nУдаление отменено.\n";
                    }

                    break;
                }


                // Возвращение к списку сохранений
                case 3:
                    break;

                default:
                    cout << "\nНеверный пункт меню!\n";
            }
        }
    }


    // ==============================
    // ГЛАВНОЕ МЕНЮ
    // ==============================

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
                    startGame(settings);
                    break;

                case LOAD_GAME:
                    manageSaves();
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
