#include <iostream>
#include <string>
#include <limits>

using namespace std;

void clearScreen() {
    system("clear");
}

void identitas(string &nama, int &nomorMeja) {
    cout << "Masukkan nama Anda: ";
    getline(cin, nama);
    
    cout << "Masukkan nomor meja Anda: ";
    cin >> nomorMeja;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    clearScreen();
}

void beranda() {
    clearScreen();
    cout << "====================================" << endl;
    cout << "|   SELAMAT DATANG DI MENU RESTO RPL   |" << endl;
    cout << "====================================" << endl;
    cout << "| 1. Daftar menu                       |" << endl;
    cout << "| 2. Lihat keranjang                   |" << endl;
    cout << "| 3. Pembayaran                        |" << endl;
    cout << "| 4. Keluar                            |" << endl;
    cout << "====================================" << endl;
    cout << "\nMasukkan pilihanmu (1-4): ";
}

int main() {
    int choice, nomorMeja;
    string nama;
    bool running = true;

    identitas(nama, nomorMeja);

    while (running) {
        beranda();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer

        switch (choice) {
            case 1:
                cout << "\nMenu feature will be implemented here.\n";
                system("pause");
                break;
            case 2:
                cout << "\nCart feature will be implemented here.\n";
                system("pause");
                break;
            case 3:
                cout << "\nPayment feature will be implemented here.\n";
                system("pause");
                break;
            case 4:
                running = false;
                cout << "\nThank you for using our app!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
                system("pause");
                break;
        }
    }

    return 0;
}
