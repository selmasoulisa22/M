#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// Fungsi untuk memilih kata secara acak
string pilihKata() {
    string daftarKata[] = {"apel", "pohon", "kucing", "rumah", "mobil", "buku", "komputer"};
    int index = rand() % 7;  // Pilih indeks acak antara 0 dan 6
    return daftarKata[index];
}

// Fungsi untuk menampilkan status tebakan
void tampilkanStatus(string kata, string tebakan) {
    for (int i = 0; i < kata.length(); i++) {
        if (tebakan[i] == ' ') {
            cout << "_ ";  // Menampilkan garis bawah untuk huruf yang belum ditebak
        } else {
            cout << tebakan[i] << " ";  // Menampilkan huruf yang sudah ditebak
        }
    }
    cout << endl;
}

int main() {
    srand(time(0));  // Inisialisasi randomizer
    string kata = pilihKata();  // Pilih kata secara acak
    string tebakan(kata.length(), ' ');  // Membuat string tebakan yang berisi spasi
    int kesempatan = 6;  // Jumlah kesempatan menebak

    cout << "Selamat datang di game Tebak Kata!" << endl;
    cout << "Coba tebak kata yang saya pikirkan!" << endl;
    cout << "Kata tersebut terdiri dari " << kata.length() << " huruf." << endl;

    // Loop permainan
    while (kesempatan > 0) {
        tampilkanStatus(kata, tebakan);
        cout << "Kesempatan tersisa: " << kesempatan << endl;

        char huruf;
        cout << "Masukkan huruf tebakan: ";
        cin >> huruf;

        bool adaPerubahan = false;
        // Cek apakah huruf yang dimasukkan ada di dalam kata
        for (int i = 0; i < kata.length(); i++) {
            if (kata[i] == huruf && tebakan[i] == ' ') {
                tebakan[i] = huruf;
                adaPerubahan = true;
            }
        }

        // Jika huruf yang dimasukkan tidak ada, kurangi kesempatan
        if (!adaPerubahan) {
            kesempatan--;
            cout << "Huruf tidak ada dalam kata!" << endl;
        }

        // Cek apakah kata sudah tertebak
        if (tebakan == kata) {
            cout << "Selamat, Anda berhasil menebak kata!" << endl;
            tampilkanStatus(kata, tebakan);
            break;
        }
    }

    // Jika kesempatan habis
    if (kesempatan == 0) {
        cout << "Sayang sekali, Anda kehabisan kesempatan. Kata yang benar adalah: " << kata << endl;
    }

    return 0;
}
