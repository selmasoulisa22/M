#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>

using namespace std;

// Fungsi untuk memilih kata secara acak
string pilihKata() {
    string daftarKata[] = {"apel", "pohon", "kucing", "rumah", "mobil", "buku", "komputer"};
    int index = rand() % 7;
    return daftarKata[index];
}

// Fungsi untuk mengacak huruf-huruf dalam sebuah kata
string acakKata(string kata) {
    string kataAcak = kata;
    std::shuffle(kataAcak.begin(), kataAcak.end());
    return kataAcak;
}

int main() {
    srand(time(0));  // Inisialisasi randomizer

    string kataAsli = pilihKata();            // Pilih kata asli
    string kataScrambled = acakKata(kataAsli); // Acak huruf dalam kata

    int kesempatan = 3;

    cout << "=== Game Scramble - Tebak Kata ===" << endl;
    cout << "Kata acak: " << kataScrambled << endl;
    cout << "Tebak kata asli dari huruf yang diacak!" << endl;

    while (kesempatan > 0) {
        string tebakan;
        cout << "Tebakan Anda: ";
        cin >> tebakan;

        // Konversi ke huruf kecil (jika diperlukan)
        transform(tebakan.begin(), tebakan.end(), tebakan.begin(), ::tolower);

        if (tebakan == kataAsli) {
            cout << "Benar! Anda berhasil menebak kata." << endl;
            break;
        } else {
            kesempatan--;
            cout << "Salah! Kesempatan tersisa: " << kesempatan << endl;
        }
    }

    if (kesempatan == 0) {
        cout << "Sayang sekali! Jawaban yang benar adalah: " << kataAsli << endl;
    }

    return 0;
}
