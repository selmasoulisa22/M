import random

# Fungsi untuk mengacak kata
def scramble_word(word):
    scrambled = list(word)
    random.shuffle(scrambled)
    return ''.join(scrambled)

# Fungsi untuk ubah string ke huruf kecil semua
def to_lower(string):
    return string.lower()

# Fungsi untuk memilih daftar kata berdasarkan level
def get_words_by_level(level):
    if level == 1:
        return ["mata", "ikan", "buku", "pagi", "kota"]
    elif level == 2:
        return ["belajar", "komputer", "program", "kamera", "internet"]
    else:
        return ["pemrograman", "perpustakaan", "pengembangan", "algoritmis", "berkebangsaan"]

def main():
    score = 0
    max_questions = 5

    print("===== GAME SCRAMBLE VERSI LANJUTAN =====")
    level = int(input("Pilih level kesulitan:\n1. Mudah\n2. Sedang\n3. Sulit\nPilihan: "))

    words = get_words_by_level(level)

    for i in range(max_questions):
        original = random.choice(words)
        scrambled = scramble_word(original)

        print(f"\nKata ke-{i + 1}: {scrambled}")
        guess = input("Tebakanmu: ")

        if to_lower(guess) == to_lower(original):
            print("Benar!")
            score += 10
        else:
            print(f"Salah. Jawaban: {original}")

    print("\nPermainan selesai!")
    print(f"Skor akhir kamu: {score} dari {max_questions * 10}")
    print("Terima kasih sudah bermain!")

if __name__ == "__main__":
    main()
