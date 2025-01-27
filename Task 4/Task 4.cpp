#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

// Проверка, является ли файл PNG
bool isPNG(const std::string& fileName) {
    setlocale(LC_ALL, "Russian");

    const std::vector<unsigned char> pngSignature = { 137, 80, 78, 71, 13, 10, 26, 10 };

    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + fileName);
    }
    
    std::vector<unsigned char> fileHeader(8);
    file.read(reinterpret_cast<char*>(fileHeader.data()), fileHeader.size());

    if (file.gcount() < 8) {
        throw std::runtime_error("Файл слишком мал для проверки сигнатуры: " + fileName);
    }
    
    return fileHeader == pngSignature;
}

int main() {
    setlocale(LC_ALL, "Russian");

    const std::string fileName = "image.png";
    
    try {
        
        if (isPNG(fileName)) {
            std::cout << "Файл \"" << fileName << "\" является PNG." << std::endl;
        }
        else {
            std::cout << "Файл \"" << fileName << "\" не является PNG." << std::endl;
        }
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}