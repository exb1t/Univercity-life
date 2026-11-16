use std::io::{self, Write};
use crate::{Settings, file_manager};

//=====general=====
fn read_string() -> String {
    io::stdout().flush().unwrap();

    let mut input = String::new();
    io::stdin().read_line(&mut input)
       .expect("Ошибка чтения ввода");
    input.trim().to_string()
}

fn read_number() -> u32 {
    loop {
        match read_string().parse::<u32>() {
            Ok(number) if number >= 0 => return number,
            _ => {
                print!("Введите неотрицательное число: ");
                io::stdout().flush().unwrap();
            }
        }
    }
}

fn wait_for_enter() {
    println!("\nНажмите Enter, чтобы вернуться в главное меню.");
    read_string();
}



pub fn main_menu (settings: &mut Settings) {
    loop {
        println!("\n=== Моя весёлая жизнь в универе ===");
        println!("1. Начать игру");
        println!("2. Загрузить игру");
        println!("3. Настройки");
        println!("4. О программе");
        println!("5. Выход");
        print!("Выберите пункт: ");

        match read_number() {
            1 => start_game(),
            2 => load_game(),
            3 => settings_menu(settings),
            4 => about(),
            5 => {
                println!("До свидания!");
                break;
            }
            _ => println!("Такого пункта нет."),
        }
    }
}



fn start_game() {
    println!("\nИгра \"Моя весёлая жизнь в универе\" начинается!");
    wait_for_enter();
}

fn load_game() {
    println!("\nЗагрузка игры пока недоступна.");
    println!("Эта функция появится в ближайших обновлениях.");
    wait_for_enter();
}

fn about() {
    println!("\nО программе");
    println!("Название: Моя весёлая жизнь в универе");
    println!("Версия: 0.2");
    println!("Выполнил: Песков Дмитрий");
    wait_for_enter();
}

//=====settings=====

fn settings_menu(settings: &mut Settings) {
    loop {
        println!("\nНастройки");
        println!("1. Специальность: {}", settings.specialty);
        println!("2. Имя студента: {}", settings.student_name);
        println!("3. Количество предметов: {}", settings.subjects_count);
        println!("4. Назад");
        print!("Выберите пункт: ");

        match read_number() {
            1 => {
                println!("\nВыберите специальность: ");
                settings.specialty = choose_specialty();
            }
            2 => {
                print!("\nВведите имя студента: ");
                settings.student_name = read_string(); 
            }
            3 => {
                print!("\nВведите количество предметов: ");
                settings.subjects_count = read_number();
            }
            4 => break,
            _ => println!("\nТакого пункта нет."),
        }
    }
}
 
fn choose_specialty() -> String {
    let specialties = file_manager::read_specialties();

    loop{
        for (i, specialty) in  specialties.iter().enumerate() {
            println!("{}. {}", i + 1, specialty);
        }

        let number = read_number();
 
        if number >0 && number <= specialties.len() as u32 {
            return specialties.iter().nth((number - 1) as usize).unwrap().clone();
        }
        else {
        println!("\nНеверный выбор. Специальность не изменена.");
        }
    }
}
