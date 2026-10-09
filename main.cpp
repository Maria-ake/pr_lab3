#include <iostream>
#include <string>
#include <vector>

using namespace std;

string defangIPaddr(const string& address) {
    string result;
    for (char c : address) {
        if (c == '.') {
            result += "[.]";
        } else {
            result += c;
        }
    }
    return result;
}


bool isPalindrome(const string& s) {
    string cleaned;
    for (char c : s) {
        if (c != ' ') {
            cleaned += c;
        }
    }

    int left = 0;
    int right = static_cast<int>(cleaned.size()) - 1;

    while (left < right) {
        if (cleaned[left] != cleaned[right]) {
            return false;
        }
        ++left;
        --right;
    }

    return true;
}


int wordScore(const string& word, const vector<int>& score) {
    int total = 0;
    for (char c : word) {
        total += score[c - 'a'];
    }
    return total;
}

void dfsMaxScore(const vector<string>& words,
                 vector<int>& available,
                 const vector<int>& score,
                 int index,
                 int currentScore,
                 int& bestScore) {
    if (currentScore > bestScore) {
        bestScore = currentScore;
    }

    if (index >= static_cast<int>(words.size())) {
        return;
    }

    for (int i = index; i < static_cast<int>(words.size()); ++i) {
        vector<int> need(26, 0);

        for (char c : words[i]) {
            need[c - 'a']++;
        }

        bool canForm = true;
        for (int k = 0; k < 26; ++k) {
            if (need[k] > available[k]) {
                canForm = false;
                break;
            }
        }

        if (!canForm) {
            continue;
        }

        for (int k = 0; k < 26; ++k) {
            available[k] -= need[k];
        }

        dfsMaxScore(words,
                    available,
                    score,
                    i + 1,
                    currentScore + wordScore(words[i], score),
                    bestScore);

        for (int k = 0; k < 26; ++k) {
            available[k] += need[k];
        }
    }
}

int maxScoreWords(const vector<string>& words,
                  const vector<char>& letters,
                  const vector<int>& score) {
    vector<int> available(26, 0);

    for (char c : letters) {
        available[c - 'a']++;
    }

    int bestScore = 0;
    dfsMaxScore(words, available, score, 0, 0, bestScore);

    return bestScore;
}


int main() {
    setlocale(LC_ALL, "Russian");

    // ---------------- Блок 1, задание 2 ----------------
    cout << "=== Блок 1, задание 2 ===" << endl;
    string ip;
    cout << "Введите IPv4-адрес: ";
    getline(cin, ip);

    cout << "Результат: " << defangIPaddr(ip) << endl << endl;

    cout << "=== Блок 2, задание 1 ===" << endl;
    string sentence;
    cout << "Введите строку для проверки на палиндром: ";
    getline(cin, sentence);

    cout << "Результат: " << (isPalindrome(sentence) ? "true" : "false") << endl << endl;

    cout << "=== Блок 3, задание 1 ===" << endl;

    vector<string> words = {"dog", "cat", "dad", "good"};
    vector<char> letters = {'a', 'a', 'c', 'd', 'd', 'd', 'g', 'o', 'o'};
    vector<int> score = {
        1, 0, 9, 5, 0, 0, 3, 0, 0, 0,
        0, 0, 0, 0, 2, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    };

    int result = maxScoreWords(words, letters, score);
    cout << "Максимальный счёт: " << result << endl;

    return 0;
}