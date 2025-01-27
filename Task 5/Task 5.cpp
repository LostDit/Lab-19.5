#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// Функция для получения вопроса и правильного ответа по номеру сектора
void get_question_and_answer(int sector, string& question, string& answer) {

    string question_filename = "question.txt";
    string answer_filename = "answer.txt";

    ifstream question_file(question_filename);
    ifstream answer_file(answer_filename);

    if (!question_file || !answer_file) {
        cerr << "Ошибка при открытии файлов!" << endl;
        exit(1);
    }

    for (int i = 0; i <= sector; ++i) {
        getline(question_file, question);
        getline(answer_file, answer);
    }

    question_file.close();
    answer_file.close();
}

// Основная функция игры
void play_game() {
    vector<bool> sectors(13, false); // Массив, показывающий, был ли сектор уже сыгран
    int player_score = 0;
    int viewers_score = 0;
    int current_sector = 0;

    while (player_score < 6 && viewers_score < 6) {
        cout << "\nТекущий сектор: " << current_sector + 1 << endl;

        // Ввод офсета
        int offset;
        cout << "Введите офсет: ";
        while (!(cin >> offset)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный ввод. Пожалуйста, введите число: ";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int new_sector = (current_sector + offset + 13) % 13;

        while (sectors[new_sector]) {
            new_sector = (new_sector + 1) % 13;
        }

        sectors[new_sector] = true;

        string question, correct_answer;
        get_question_and_answer(new_sector, question, correct_answer);

        cout << "Вопрос: " << question << endl;
        string player_answer;
        cout << "Ваш ответ: ";
        getline(cin, player_answer);

        if (player_answer == correct_answer) {
            player_score++;
            cout << "Правильный ответ! Ваш балл: " << player_score << endl;
        }
        else {
            viewers_score++;
            cout << "Неправильный ответ. Балл зрителей: " << viewers_score << endl;
        }

        current_sector = new_sector;
    }

    if (player_score == 6) {
        cout << "\nПоздравляем, вы победили!" << endl;
    }
    else if (viewers_score == 6) {
        cout << "\nПобедили зрители!" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Добро пожаловать в игру 'Что? Где? Когда?'" << endl;
    play_game();
    return 0;
}
