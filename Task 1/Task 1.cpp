#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// Функция для приведения строки к нижнему регистру
string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return tolower(c);
        });
    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");

    ifstream file("words.txt");
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл words.txt" << endl;
        return 1;
    }

    string wordToFind;
    cout << "Введите слово для поиска: ";
    cin >> wordToFind;

    // Привожу искомое слово к нижнему регистру
    wordToFind = toLower(wordToFind);

    string word;
    int count = 0;

    // Проверка слов из файла (возможно лучше было бы вынести в доп функцию)
    while (file >> word) {
        // Привожу слово из файла к нижнему регистру
        word = toLower(word);

        // Убираю пунктуацию в конце слов
        word.erase(remove_if(word.begin(), word.end(), [](unsigned char c) {
            return ispunct(c);
            }), word.end());

        // Сравнение с заданным словом
        if (word == wordToFind) {
            count++;
        }
    }

    file.close();

    // Вывожу результат пользу
    if (count > 0) {
        cout << "Слово \"" << wordToFind << "\" встречается " << count << " раз(а)." << endl;
    }
    else {
        cout << "Слово \"" << wordToFind << "\" не найдено." << endl;
    }

    return 0;
}
