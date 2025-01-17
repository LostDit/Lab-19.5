#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>

using namespace std;

// Функция для приведения к нижнему регистру и удаление пунктуации
string preprocess(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return tolower(c);
        });
    result.erase(remove_if(result.begin(), result.end(), [](unsigned char c) {
        return ispunct(c) && c != '.'; // Сохр точки
        }), result.end());
    return result;
}

// Подсчет количества вхождений слова в строке
int countOccurrences(const string& line, const string& wordToFind) {
    string cleanedLine = preprocess(line);
    regex wordRegex("\\b" + wordToFind + "\\b");
    return distance(sregex_iterator(cleanedLine.begin(), cleanedLine.end(), wordRegex), sregex_iterator());
}

int main() {
    setlocale(LC_ALL, "Russian");

    ifstream file("words.txt");
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл words.txt." << endl;
        return 1;
    }

    string wordToFind;
    cout << "Введите слово для поиска: ";
    cin >> wordToFind;
    wordToFind = preprocess(wordToFind);

    int totalCount = 0;
    for (string line; getline(file, line); ) {
        totalCount += countOccurrences(line, wordToFind);
    }

    cout << "Слово \"" << wordToFind << "\" встречается " << totalCount << " раз(а)." << endl;
    return 0;
}