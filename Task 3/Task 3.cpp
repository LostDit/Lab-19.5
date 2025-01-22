#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <cctype>
#include <tuple>

// Функция для очистки строки от пробелов в начале и конце
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    if (first == std::string::npos) return "";  // Пустая строка
    return str.substr(first, last - first + 1);
}

// Функция для обработки строки
bool parseLine(const std::string& line, std::string& fullName, int& amount) {
    std::istringstream iss(line);
    std::string firstName, lastName, date;

    if (!(iss >> firstName >> lastName >> amount >> date)) {
        return false;  // Если не тот формат строки
    }

    fullName = firstName + " " + lastName;
    return true;
}

// Функция для чтения и обработки файла
std::tuple<int, int, std::string> processFile(const std::string& fileName) {
    setlocale(LC_ALL, "Russian");

    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + fileName);
    }

    std::string line, fullName, maxName;
    int totalAmount = 0, maxAmount = std::numeric_limits<int>::min();
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;
        line = trim(line);  // Очистка строки от пробела

        // Пропуск пустых строк
        if (line.empty()) {
            continue;
        }

        int amount;
        if (!parseLine(line, fullName, amount)) {
            std::cerr << "Ошибка чтения строки " << lineNumber << ": \"" << line << "\"" << std::endl;
            continue;
        }

        totalAmount += amount;  // Суммирую выплаты
        if (amount > maxAmount) {
            maxAmount = amount;  // Обновляю максимальную выплату
            maxName = fullName;
        }
    }

    file.close();
    return { totalAmount, maxAmount, maxName };
}


int main() {
    setlocale(LC_ALL, "Russian");

    const std::string fileName = "Statement.txt";

    try {
        // Обрабатываю файл
        auto [totalAmount, maxAmount, maxName] = processFile(fileName);//Работает со стандарта ISO 17++

        // Вывожу результат
        std::cout << "Общая сумма выплат: " << totalAmount << std::endl;
        std::cout << "Максимальная выплата: " << maxAmount << " (" << maxName << ")" << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}