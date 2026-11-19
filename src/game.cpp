
#include "game.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

using namespace std;

namespace game {

    // Ограничение характеристик от 0 до 100
    int limitValue(int value) {
        return max(0, min(100, value));
    }


    // ==============================
    // SUBJECT
    // ==============================

    Subject::Subject(const string& name, const Question& question)
        : name(name), question(question) {
    }

    const string& Subject::getName() const {
        return name;
    }

    const Question& Subject::getQuestion() const {
        return question;
    }

    int Subject::getKnowledge() const {
        return knowledge;
    }

    int Subject::getAttendedDays() const {
        return attendedDays;
    }

    int Subject::getSkippedDays() const {
        return skippedDays;
    }

    bool Subject::isCorrectAnswer(int answer) const {
        return answer == question.correctOption;
    }

    // Посещение занятия
    void Subject::attend() {
        attendedDays++;
        addKnowledge(8);
    }

    // Пропуск занятия
    void Subject::skip() {
        skippedDays++;
    }

    // Увеличение знаний
    void Subject::addKnowledge(int value) {
        knowledge = limitValue(knowledge + value);
    }


    // ==============================
    // STUDENT
    // ==============================

    Student::Student(
        const string& name,
        const string& specialty,
        int subjectsCount
    ) : name(name), specialty(specialty) {

        if (subjectsCount < 0) {
            throw invalid_argument(
                "Количество предметов не может быть отрицательным"
            );
        }

        // Каталог предметов
        vector<Subject> catalog = {

            Subject("Программирование", {
                "Какой оператор проверяет равенство в C++?",
                {"=", "==", "!="},
                2
            }),

            Subject("Математика", {
                "Чему равна производная функции x^2?",
                {"2x", "x", "x^3"},
                1
            }),

            Subject("Физика", {
                "В каких единицах измеряется сила?",
                {"Ньютон", "Джоуль", "Ватт"},
                1
            }),

            Subject("КПО", {
                "Что означает аббревиатура ООП?",
                {
                    "Объектно-ориентированное программирование",
                    "Общее описание программы",
                    "Основной оператор программы"
                },
                1
            }),

            Subject("Информационная безопасность", {
                "Что такое уязвимость?",
                {
                    "Слабое место системы безопасности",
                    "Резервная копия данных",
                    "Программа для защиты компьютера"
                },
                1
            }),

            Subject("Английский язык", {
                "Как переводится слово Library?",
                {"Библиотека", "Магазин", "Университет"},
                1
            }),

            Subject("История", {
                "В каком году была провозглашена независимость Республики Беларусь?",
                {"1991", "1945", "2000"},
                1
            })

        };

        // Добавление предметов студенту
        for (int i = 0; i < subjectsCount; i++) {

            if (i < static_cast<int>(catalog.size())) {
                subjects.push_back(catalog[i]);
            }
            else {
                subjects.emplace_back(
                    "Предмет " + to_string(i + 1),
                    Question{
                        "Что помогает лучше усвоить учебный материал?",
                        {
                            "Регулярная практика",
                            "Игнорирование занятий",
                            "Отказ от повторения"
                        },
                        1
                    }
                );
            }
        }
    }

    const string& Student::getName() const {
        return name;
    }

    const string& Student::getSpecialty() const {
        return specialty;
    }

    int Student::getEnergy() const {
        return energy;
    }

    int Student::getDiscipline() const {
        return discipline;
    }

    int Student::getProblemSolving() const {
        return problemSolving;
    }

    size_t Student::getSubjectsCount() const {
        return subjects.size();
    }

    Subject& Student::getSubject(size_t index) {
        return subjects.at(index);
    }

    const Subject& Student::getSubject(size_t index) const {
        return subjects.at(index);
    }

    // Посещение предмета
    void Student::attendSubject(size_t index) {
        subjects.at(index).attend();

        changeDiscipline(5);
        spendEnergy(8);
    }

    // Пропуск предмета
    void Student::skipSubject(size_t index) {
        subjects.at(index).skip();

        changeDiscipline(-6);
    }

    // Уменьшение энергии
    void Student::spendEnergy(int value) {
        energy = limitValue(energy - value);
    }

    // Восстановление энергии
    void Student::restoreEnergy(int value) {
        energy = limitValue(energy + value);
    }

    // Изменение дисциплины
    void Student::changeDiscipline(int value) {
        discipline = limitValue(discipline + value);
    }

    // Развитие навыка решения задач
    void Student::improveProblemSolving(int value) {
        problemSolving = limitValue(problemSolving + value);
    }

    // Расчет итоговой оценки
    int Student::calculateGrade(const Subject& subject) const {

        double score =
            subject.getKnowledge() * 0.65 +
            discipline * 0.15 +
            problemSolving * 0.15 +
            energy * 0.05;

        int grade = 2 + static_cast<int>(round(score * 8.0 / 100.0));

        return max(2, min(10, grade));
    }


    // ==============================
    // ACTION
    // ==============================

    Action::Action(ActionType type) : type(type) {
    }

    // Выполнение действия
    void Action::execute(Student& student, Subject* subject) const {

        switch (type) {

            case ActionType::STUDY:

                if (subject == nullptr) {
                    return;
                }

                subject->addKnowledge(18);

                student.spendEnergy(12);
                student.changeDiscipline(2);

                break;


            case ActionType::SOLVE_TASKS:

                if (subject == nullptr) {
                    return;
                }

                subject->addKnowledge(12);

                student.spendEnergy(18);
                student.improveProblemSolving(15);

                break;


            case ActionType::REST:

                student.restoreEnergy(30);

                break;
        }
    }

}
