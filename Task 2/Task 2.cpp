#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <regex>

//Функция по проверке на расширение (.txt)
bool isTextFileByExtension(const std::string& filePath) {
    std::regex textFileExtensionPattern(".*\\.txt$", std::regex::icase);
    return std::regex_match(filePath, textFileExtensionPattern);
}

//Функция по открытию файла
std::ifstream openTextFile(const std::string& filePath) {
    setlocale(LC_ALL, "Russian");

    if (!isTextFileByExtension(filePath)) {
        throw std::invalid_argument("Указанный файл не имеет текстового расширения (.txt).");
    }
    
    std::ifstream inputFileStream(filePath, std::ios::binary);
    if (!inputFileStream.is_open()) {
        throw std::runtime_error("Не удалось открыть файл. Проверьте путь или доступ.");
    }

    return inputFileStream;
}

//Функция по чтению и выводу файла (блоками)
void readAndDisplayFileContents(std::ifstream& inputFileStream) {
    const size_t readBufferSizeBytes = 1024; // Размер буфера для чтения (1 КБ)
    char readBuffer[readBufferSizeBytes];

    // Постепенно считываю содержимое файла и вывожу его в консоль
    while (inputFileStream.read(readBuffer, readBufferSizeBytes) || inputFileStream.gcount() > 0) {
        std::cout.write(readBuffer, inputFileStream.gcount());
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        std::string filePathToOpen;

        std::cout << "Введите путь к текстовому файлу (с расширением .txt): ";
        std::getline(std::cin, filePathToOpen);

        std::ifstream openedFileStream = openTextFile(filePathToOpen);

        readAndDisplayFileContents(openedFileStream);

        openedFileStream.close();
    }
    catch (const std::invalid_argument& invalidArgumentException) {
        std::cerr << "Ошибка: " << invalidArgumentException.what() << std::endl;
    }
    catch (const std::runtime_error& runtimeException) {
        std::cerr << "Ошибка: " << runtimeException.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Произошла неизвестная ошибка." << std::endl;
    }

    return 0;
}
