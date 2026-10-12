use std::io::{self, Write};

const START_GAME: u32 = 1;
const LOAD_GAME: u32 = 2;
const SETTINGS: u32 = 3;
const ABOUT: u32 = 4;
const EXIT: u32 = 5;


struct Settings {
    specialty: String,
    student_name: String,
    subjects_count: u32,
}

fn read_string() -> String {
    let mut input = String::new();

    io::stdin()
        .read_line(&mut input)
        .expect("Ошибка чтения ввода");

    input.trim().to_string()
}

fn read_number() -> u32 {
    loop {
        let input = read_string();

        match input.parse::<u32>() {
            Ok(number) => return number,
            Err(_) => {
                println!("Введите целое число.");
                print!("Ваш выбор: ");
                io::stdout().flush().unwrap();
            }
        }
    }
}

fn start_game(settings: &Settings) {
    println!("\n=== Моя жизнь в университете ===");
    println!("Игра начинается!");
    println!("Студент: {}", settings.student_name);
    println!("Специальность: {}", settings.specialty);
    println!("Количество предметов: {}", settings.subjects_count);

    read_string();
}

fn load_game() {
    println!("\nЗагрузка игры пока недоступна.");
    println!("Данная функция появится в ближайших обновлениях.");

    read_string();
}

fn settings_menu(settings: &mut Settings) {
    loop {
        println!("\n=== Настройки ===");
        println!("1. Специальность: {}", settings.specialty);
        println!("2. Имя студента: {}", settings.student_name);
        println!("3. Количество предметов: {}", settings.subjects_count);
        println!("4. Назад");

        print!("Выберите параметр: ");
        io::stdout().flush().unwrap();

        let choice = read_number();

        match choice {
            1 => {
                print!("Введите специальность: ");
                io::stdout().flush().unwrap();

                settings.specialty = read_string();

                println!("Специальность изменена.");
            }

            2 => {
                print!("Введите имя студента: ");
                io::stdout().flush().unwrap();

                settings.student_name = read_string();

                println!("Имя изменено.");
            }

            3 => {
                print!("Введите количество предметов: ");
                io::stdout().flush().unwrap();

                settings.subjects_count = read_number();

                println!("Количество предметов изменено.");
            }

            4 => {
                break;
            }

            _ => {
                println!("Такого пункта нет.");
            }
        }
    }
}

fn about() {
    println!("\n=== О программе ===");
    println!("Название: Моя жизнь в университете");
    println!("Версия: 0.1");
    println!("Студент: Песков Дмитрий");

    read_string();
}

// Главное меню
fn main_menu(settings: &mut Settings) {
    loop {
        println!("1. Начать игру");
        println!("2. Загрузить игру");
        println!("3. Настройки");
        println!("4. О программе");
        println!("5. Выход");

        print!("Выберите пункт: ");
        io::stdout().flush().unwrap();

        let choice = read_number();

        match choice {
            START_GAME => {
                start_game(settings);
            }

            LOAD_GAME => {
                load_game();
            }

            SETTINGS => {
                settings_menu(settings);
            }

            ABOUT => {
                about();
            }

            EXIT => {
                println!("\nВыход из программы...");
                break;
            }

            _ => {
                println!("Ошибка: такого пункта меню нет.");
            }
        }
    }
}

fn main() {

    let mut settings = Settings {
        specialty: String::from("Не выбрана"),
        student_name: String::from("Не указано"),
        subjects_count: 0,
    };

    main_menu(&mut settings);
}