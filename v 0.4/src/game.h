
#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <cstddef>

namespace game {

    struct Question {
        std::string text;
        std::vector<std::string> options;
        int correctOption;
    };

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

        // Восстановление прогресса предмета
        void setProgress(int knowledge, int attended, int skipped);
    };


    class Student {
    private:
        std::string name;
        std::string specialty;

        int energy = 100;
        int discipline = 50;
        int problemSolving = 20;

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

        std::size_t getSubjectsCount() const;

        Subject& getSubject(std::size_t index);
        const Subject& getSubject(std::size_t index) const;

        void attendSubject(std::size_t index);
        void skipSubject(std::size_t index);

        void spendEnergy(int value);
        void restoreEnergy(int value);

        void changeDiscipline(int value);
        void improveProblemSolving(int value);

        // Восстановление характеристик студента
        void setCharacteristics(
            int energy,
            int discipline,
            int problemSolving
        );

        int calculateGrade(const Subject& subject) const;
    };


    enum class ActionType {
        STUDY,
        SOLVE_TASKS,
        REST
    };


    class Action {
    private:
        ActionType type;

    public:
        explicit Action(ActionType type);

        void execute(Student& student, Subject* subject = nullptr) const;
    };

}

#endif
