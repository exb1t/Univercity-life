use std::io::{self, Write};
mod output;


pub struct Settings {
    pub specialty: String,
    pub student_name: String,
    pub subjects_count: i32,
}


pub fn read_string() -> String {
    let mut input = String::new();
    io::stdout().flush().unwrap();
    io::stdin()
        .read_line(&mut input)
        .expect("Не удалось прочитать ввод");
    input.trim().to_string()
}

pub fn read_number() -> i32 {
    loop {
        match read_string().parse::<i32>() {
            Ok(number) if number >= 0 => return number,
            _ => {
                print!("Введите неотрицательное число: ");
                io::stdout().flush().unwrap();
            }
        }
    }
}

pub fn wait_for_enter() {
    println!("\nНажмите Enter, чтобы вернуться в главное меню.");
    read_string();
}




fn main() {
    let mut settings = Settings {
        specialty: "Не выбрана".to_string(),
        student_name: "Не указано".to_string(),
        subjects_count: 0,
    };

    MW_output::main_menu(&mut settings);

}