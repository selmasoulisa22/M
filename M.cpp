#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <chrono>
#include <thread>
#include <fstream>
#include <random>
#include <map>
#include <set>

using namespace std;

string scrambleWord(string word) {
    static random_device rd;
    static mt19937 g(rd());

    string scrambled = word;
    do {
        shuffle(scrambled.begin(), scrambled.end(), g);
    } while (scrambled == word);

    return scrambled;
}

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

vector<string> getWordsByLevel(int level) {
    if (level == 1) {
        return { "mata", "ikan", "buku", "pagi", "kota", "kamu", "kita", "kami", "lain", "malu", "dari", "tali", "kopi", "haus" };
    } else if (level == 2) {
        return { "belajar", "komputer", "program", "kamera", "internet", "lemari", "kasur", "sepatu", "selimut", "rumah", "manusia", "makan", "tidur" };
    } else {
        return { "pemrograman", "perpustakaan", "pengembangan", "olahraga", "berkebangsaan", "masyarakat", "organisasi", "kementrian", "pendakian" };
    }
}

void saveToLeaderboard(const string& name, int score) {
    ofstream file("leaderboard.txt", ios::app);
    if (file.is_open()) {
        file << name << " " << score << endl;
        file.close();
    }
}

void showLeaderboard() {
    ifstream file("leaderboard.txt");
    cout << "\n===== LEADERBOARD =====" << endl;

    map<string, int> leaderboard;
    string name;
    int score;
    while (file >> name >> score) {
        if (leaderboard.find(name) == leaderboard.end() || leaderboard[name] < score)
            leaderboard[name] = score;
    }
    file.close();

    vector<pair<string, int>> sortedScores(leaderboard.begin(), leaderboard.end());
    sort(sortedScores.begin(), sortedScores.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    int rank = 1;
    for (auto& p : sortedScores) {
        cout << rank << ". " << p.first << " - " << p.second << " poin" << endl;
        if (++rank > 10) break; // hanya tampilkan 10 besar
    }
}

int main() {
    srand(time(0));
    int score = 0;
    int level;
    const int maxQuestions = 5;
    const int timeLimit = 10; // detik

    cout << "===== GAME SCRAMBLE DENGAN TIMER & LEADERBOARD =====" << endl;
    cout << "Masukkan nama kamu: ";
    string playerName;
    cin >> playerName;

    cout << "Pilih level:\n1. Mudah\n2. Sedang\n3. Sulit\nPilihan: ";
    cin >> level;

    vector<string> words = getWordsByLevel(level);
    set<string> usedWords;
    cin.ignore(); // bersihkan newline

    for (int i = 0; i < maxQuestions; ++i) {
        string original;
        do {
            original = words[rand() % words.size()];
        } while (usedWords.count(original)); // hindari kata yang sama
        usedWords.insert(original);

        string scrambled = scrambleWord(original);
        cout << "\nKata ke-" << (i + 1) << ": " << scrambled << endl;
        cout << "Tebakanmu (maksimal " << timeLimit << " detik): ";

        string guess;
        bool timeUp = false;
        auto start = chrono::steady_clock::now();

        thread timerThread([&]() {
            for (int sec = timeLimit; sec > 0; --sec) {
                cout << "\rWaktu tersisa: " << sec << " detik  " << flush;
                this_thread::sleep_for(chrono::seconds(1));
            }
            timeUp = true;
            cout << "\rWaktu habis!                      \n";
        });

        getline(cin, guess);
        auto end = chrono::steady_clock::now();
        timerThread.join(); // tunggu thread selesai

        auto elapsed = chrono::duration_cast<chrono::seconds>(end - start).count();

        if (elapsed > timeLimit || timeUp) {
            cout << "Terlambat! Jawaban yang benar: " << original << endl;
        } else {
            if (toLower(guess) == toLower(original)) {
                cout << "Benar!" << endl;
                score += 10;
            } else {
                cout << "Salah. Jawaban: " << original << endl;
            }
        }
    }

    cout << "\nGame selesai!" << endl;
    cout << "Skor akhir: " << score << "/" << (maxQuestions * 10) << endl;

    saveToLeaderboard(playerName, score);
    showLeaderboard();

    return 0;
}
