use std::fs::File;
use std::io::{BufRead, BufReader};
use std::collections::BTreeSet;

pub fn read_specialties() -> BTreeSet<String>{
    let file = File::open("specialties.txt").expect("Ошибка открытия файла");
    let reader = BufReader::new(file);
    let mut specialties = BTreeSet::new();

    for line in reader.lines() {
        let line = line.expect("Ошибка чтения строки");
        specialties.insert(line);
    }
    specialties
}
