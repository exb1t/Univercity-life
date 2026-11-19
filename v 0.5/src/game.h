
#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <cstddef>

namespace game {

    // Продолжительность игры
    constexpr int STUDY_DAYS = 10;
    constexpr int DAYS_PER_MONTH = 5;

    // Финансовые параметры
    constexpr int INITIAL_STIPEND = 500;
    constexpr int MIN_STIPEND = 100;
    constexpr int MAX_STIPEND = 500;


    struct Question {
        std::string text;
        std::vector<std::string> options;
        int correctOption;
    };


    // Учебный предмет
    class Subject {
    private:
        std::string name;
        int knowledge = 0;
        int attendedDays = 0;
        int skippedDays = 0;
        Question question;

    public:
        Subject(const std::string& name, const Question& question);

        const std::string& getName() const;
        const Question& getQuestion() const;

        int getKnowledge() const;
        int getAttendedDays() const;
        int getSkippedDays() const;

        bool isCorrectAnswer(int answer) const;

        void attend();
        void skip();
        void addKnowledge(int value);

        void setProgress(int knowledge, int attended, int skipped);
    };


    // Студент
    class Student {
    private:
        std::string name;
        std::string specialty;

        int energy = 100;
        int discipline = 50;
        int problemSolving = 20;

        // Финансовые характеристики
        int money = 0;
        int monthlyIncome = INITIAL_STIPEND;

        // Результаты контроля знаний за текущий месяц
        int monthlyGradeSum = 0;
        int monthlyControlCount = 0;

        std::vector<Subject> subjects;

    public:
        Student(
            const std::string& name,
            const std::string& specialty,
            int subjectsCount
        );

        const std::string& getName() const;
        const std::string& getSpecialty() const;

        int getEnergy() const;
        int getDiscipline() const;
        int getProblemSolving() const;

        int getMoney() const;
        int getMonthlyIncome() const;
        int getMonthlyGradeSum() const;
        int getMonthlyControlCount() const;

        std::size_t getSubjectsCount() const;

        Subject& getSubject(std::size_t index);
        const Subject& getSubject(std::size_t index) const;

        void attendSubject(std::size_t index);
        void skipSubject(std::size_t index);

        void spendEnergy(int value);
        void restoreEnergy(int value);

        void changeDiscipline(int value);
        void improveProblemSolving(int value);

        // Финансовые операции
        void receiveMonthlyIncome();
        bool spendMoney(int value);

        // Контроль знаний
        void recordControlGrade(int grade);
        double finishMonth();

        // Восстановление данных из сохранения
        void setCharacteristics(
            int energy,
            int discipline,
            int problemSolving
        );

        void setFinancialState(
            int money,
            int monthlyIncome,
            int gradeSum,
            int controlCount
        );

        int calculateGrade(const Subject& subject) const;
    };


    // Типы действий
    enum class ActionType {
        STUDY,
        SOLVE_TASKS,
        REST,
        BUY_TEXTBOOK,
        BUY_FOOD
    };


    // Действие студента
    class Action {
    private:
        ActionType type;

    public:
        explicit Action(ActionType type);

        bool execute(Student& student, Subject* subject = nullptr) const;
    };

}

#endif
