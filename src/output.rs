use super::{Settings, read_number, read_string, wait_for_enter};

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
                print!("Введите специальность: ");
                settings.specialty = read_string();
            }
            2 => {
                print!("Введите имя студента: ");
                settings.student_name = read_string();
            }
            3 => {
                print!("Введите количество предметов: ");
                settings.subjects_count = read_number();
            }
            4 => break,
            _ => println!("Такого пункта нет."),
        }
    }
}

fn about() {
    println!("\nО программе");
    println!("Название: Моя весёлая жизнь в универе");
    println!("Версия: 1.0");
    println!("Выполнил: Песков Дмитрий");
    wait_for_enter();
}
