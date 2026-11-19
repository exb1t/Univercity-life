
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

    void Subject::attend() {
        attendedDays++;
        addKnowledge(8);
    }

    void Subject::skip() {
        skippedDays++;
    }

    void Subject::addKnowledge(int value) {
        knowledge = limitValue(knowledge + value);
    }

    // Восстановление прогресса предмета
    void Subject::setProgress(
        int knowledge,
        int attended,
        int skipped
    ) {
        this->knowledge = limitValue(knowledge);
        attendedDays = max(0, attended);
        skippedDays = max(0, skipped);
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


    // ==============================
    // ПОЛУЧЕНИЕ ХАРАКТЕРИСТИК
    // ==============================

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

    int Student::getMoney() const {
        return money;
    }

    int Student::getMonthlyIncome() const {
        return monthlyIncome;
    }

    int Student::getMonthlyGradeSum() const {
        return monthlyGradeSum;
    }

    int Student::getMonthlyControlCount() const {
        return monthlyControlCount;
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


    // ==============================
    // УЧЕБНЫЙ ПРОЦЕСС
    // ==============================

    void Student::attendSubject(size_t index) {
        subjects.at(index).attend();

        changeDiscipline(5);
        spendEnergy(8);
    }

    void Student::skipSubject(size_t index) {
        subjects.at(index).skip();

        changeDiscipline(-6);
    }

    void Student::spendEnergy(int value) {
        energy = limitValue(energy - value);
    }

    void Student::restoreEnergy(int value) {
        energy = limitValue(energy + value);
    }

    void Student::changeDiscipline(int value) {
        discipline = limitValue(discipline + value);
    }

    void Student::improveProblemSolving(int value) {
        problemSolving = limitValue(problemSolving + value);
    }


    // ==============================
    // ФИНАНСЫ
    // ==============================

    // Получение ежемесячной стипендии
    void Student::receiveMonthlyIncome() {
        money += monthlyIncome;
    }

    // Трата денег
    bool Student::spendMoney(int value) {

        if (value < 0 || money < value) {
            return false;
        }

        money -= value;

        return true;
    }


    // ==============================
    // КОНТРОЛЬ ЗНАНИЙ
    // ==============================

    // Запись оценки за контроль
    void Student::recordControlGrade(int grade) {

        grade = max(2, min(10, grade));

        monthlyGradeSum += grade;
        monthlyControlCount++;
    }


    // Завершение месяца и пересчет стипендии
    double Student::finishMonth() {

        if (monthlyControlCount == 0) {
            return 0.0;
        }

        double averageGrade =
            static_cast<double>(monthlyGradeSum) /
            monthlyControlCount;

        // Плохие оценки уменьшают следующую стипендию
        if (averageGrade < 6.0) {

            monthlyIncome = max(
                MIN_STIPEND,
                monthlyIncome - 100
            );
        }

        // Хорошие оценки позволяют восстановить стипендию
        else if (averageGrade >= 8.0) {

            monthlyIncome = min(
                MAX_STIPEND,
                monthlyIncome + 50
            );
        }

        // Очищаем результаты текущего месяца
        monthlyGradeSum = 0;
        monthlyControlCount = 0;

        return averageGrade;
    }


    // ==============================
    // ВОССТАНОВЛЕНИЕ ДАННЫХ
    // ==============================

    void Student::setCharacteristics(
        int energy,
        int discipline,
        int problemSolving
    ) {
        this->energy = limitValue(energy);
        this->discipline = limitValue(discipline);
        this->problemSolving = limitValue(problemSolving);
    }


    void Student::setFinancialState(
        int money,
        int monthlyIncome,
        int gradeSum,
        int controlCount
    ) {
        this->money = max(0, money);

        this->monthlyIncome = max(
            MIN_STIPEND,
            min(MAX_STIPEND, monthlyIncome)
        );

        this->monthlyGradeSum = max(0, gradeSum);
        this->monthlyControlCount = max(0, controlCount);
    }


    // ==============================
    // РАСЧЕТ ОЦЕНКИ
    // ==============================

    int Student::calculateGrade(const Subject& subject) const {

        double score =
            subject.getKnowledge() * 0.65 +
            discipline * 0.15 +
            problemSolving * 0.15 +
            energy * 0.05;

        int grade =
            2 + static_cast<int>(round(score * 8.0 / 100.0));

        return max(2, min(10, grade));
    }


    // ==============================
    // ACTION
    // ==============================

    Action::Action(ActionType type) : type(type) {
    }


    bool Action::execute(
        Student& student,
        Subject* subject
    ) const {

        switch (type) {

            case ActionType::STUDY:

                if (subject == nullptr) {
                    return false;
                }

                subject->addKnowledge(18);

                student.spendEnergy(12);
                student.changeDiscipline(2);

                return true;


            case ActionType::SOLVE_TASKS:

                if (subject == nullptr) {
                    return false;
                }

                subject->addKnowledge(12);

                student.spendEnergy(18);
                student.improveProblemSolving(15);

                return true;


            case ActionType::REST:

                student.restoreEnergy(30);

                return true;


            case ActionType::BUY_TEXTBOOK:

                if (subject == nullptr) {
                    return false;
                }

                if (!student.spendMoney(100)) {
                    return false;
                }

                subject->addKnowledge(20);

                return true;


            case ActionType::BUY_FOOD:

                if (!student.spendMoney(30)) {
                    return false;
                }

                student.restoreEnergy(25);

                return true;
        }

        return false;
    }

}
