use std::collections::LinkedList;

mod output;
mod file_manager;

pub struct Settings {
    pub specialty: String,
    pub student_name: String,
    pub subjects_count: u32,
}

fn main() {




    let mut settings = Settings {
        specialty: "Не выбрана".to_string(),
        student_name: "Не указано".to_string(),
        subjects_count: 0,
    };

    output::main_menu(&mut settings);

}