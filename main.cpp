#include <iostream>
#include <string>
#include <limits>

using namespace std;

void clearScreen() {
    system("cls");
}

int getValidIntegerInput(string prompt) {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid! Harap masukkan angka.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
    }
}

//==========INPUT NAMA==========//
void identitas(string &nama, int &nomorMeja) {
    cout << "Masukkan nama depan Anda: ";
    cin >> nama;
    
    nomorMeja = getValidIntegerInput("Masukkan nomor meja Anda: ");
    clearScreen();
}

//==========BERANDA==========//
void beranda() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "|   SELAMAT DATANG DI MENU RESTO RPL   |" << endl;
    cout << "========================================" << endl;
    cout << "| 1. Daftar menu                       |" << endl;
    cout << "| 2. Lihat keranjang                   |" << endl;
    cout << "| 3. Pembayaran                        |" << endl;
    cout << "| 4. Keluar                            |" << endl;
    cout << "========================================" << endl;
    cout << "\nMasukkan pilihanmu (1-4): ";
}

//==========LIST MENU MAKANAN/MINUMAN==========//
struct MenuItem {
    int id;
    string nama;
    int harga;
};

struct Pesanan {
    int id;
    int qty;
};

const int jumlahMenu = 15;
MenuItem daftarMenu[jumlahMenu] = {
    {1, "Nasi Goreng", 25000},
    {2, "Mie Goreng", 20000},
    {3, "Ayam Bakar", 30000},
    {4, "Sate Ayam", 27000},
    {5, "Soto Betawi", 28000},
    {6, "Bakso Urat", 22000},
    {7, "Gado-Gado", 20000},
    {8, "Pecel Lele", 24000},
    {9, "Nasi Padang", 29000},
    {10, "Rendang Sapi", 35000},
    {11, "Es Teh Manis", 5000},
    {12, "Teh Hangat", 5000},
    {13, "Es Jeruk", 7000},
    {14, "Jus Alpukat", 15000},
    {15, "Jus Mangga", 13000}
};

const int maksPesanan = 100;
Pesanan pesanan[maksPesanan];
int jumlahPesanan = 0;

void tampilkanDaftarMenu() {
    int pilihan, qty;
    char lanjut;
    
    do {
        clearScreen();
        cout << "---------------Daftar Menu-------------\n\n";
        cout << "ID\tNama Makanan\t\tHarga\n";
        cout << "---------------------------------------\n";
        
        for (int i = 0; i < jumlahMenu; i++) {
            cout << daftarMenu[i].id << "\t" 
                 << daftarMenu[i].nama << "\t\tRp " 
                 << daftarMenu[i].harga << endl;
        }
        
        pilihan = getValidIntegerInput("\nMasukkan ID menu yang dipilih (0 untuk kembali): ");

        if (pilihan == 0) break;

        if (pilihan >= 1 && pilihan <= jumlahMenu) {
            qty = getValidIntegerInput("Masukkan jumlah: ");
            if (qty > 0 && qty <= 100) {
                pesanan[jumlahPesanan++] = {pilihan, qty};
            } else {
                cout << "Jumlah tidak valid.\n";
            }
        } else {
            cout << "ID salah.\n";
        }
        
        cout << "\nTambahkan menu lain? (y/n): ";
        cin >> lanjut;
    } while (lanjut == 'y' || lanjut == 'Y');
}

//==========KERANJANG==========//
void keranjang() {
    int choice;

    do {
        clearScreen();
        cout << "-----FITUR MASIH DALAM TAHAP PENGEMBANGAN-----\n\n";
        cout << "--------------- Keranjang Anda ---------------\n\n";

        if (jumlahPesanan == 0) {
            cout << "Keranjang masih kosong.\n";
        } else {
            for (int i = 0; i < jumlahPesanan; i++) {
                cout << "Pesanan " << i + 1 << " - ID: " << pesanan[i].id
                     << ", Jumlah: " << pesanan[i].qty << endl;
            }
        }

        choice = getValidIntegerInput("\n0 untuk kembali ke menu utama: ");

    } while (choice != 0);
}

//==========PEMBAYARAN==========//
void pembayaran() {
    int choice;
    char lanjut;

    do {
        clearScreen();
        cout << "--------------- Pembayaran ---------------\n\n";

        if(jumlahPesanan == 0){
            cout << "Keranjang masih kosong \n";
        }
        else {
            cout << "Daftar Pesanan Anda:\n";
            cout << "\nID\tNama Makanan\t\tJumlah\tHarga\n";
            cout << "--------------------------------------------\n";
            
            for (int i = 0; i < jumlahPesanan; i++) {
                int id = pesanan[i].id - 1;
                cout << daftarMenu[id].nama << "\t\t" 
                     << pesanan[i].qty << "\tRp " 
                     << daftarMenu[id].harga * pesanan[i].qty << endl;
            }
            cout << "\nApakah ingin melakukan pembayaran? (y/n): ";
            cin >> lanjut;
            if(lanjut == 'y' || lanjut == 'Y') {
                cout << "\nPilih metode pembayaran: \n";
                cout << "1. Tunai\n";
                cout << "2. Kartu Kredit\n";
                cout << "3. E-Wallet atau Transfer Bank\n";
                
                int metode = getValidIntegerInput("Masukkan pilihan (1-3): \n");
                if (metode < 1 || metode > 3) {
                    cout << "Pilihan tidak valid.\n";
                    continue;
                }
                if (metode == 1){
                    cout << "Silahkan pergi ke kasir untuk melakukan pembayaran.\n";
                    
                }
                else if (metode == 2){
                    cout << "Silahkan pilih kartu kredit Anda untuk melakukan pembayaran.\n";
                    cout << "1. BCA\n";
                    cout << "2. Mandiri\n";
                    cout << "3. BRI\n";
                    cout << "4. BNI\n";
                    int kartu = getValidIntegerInput("Masukkan pilihan (1-4): \n");
                    if (kartu <= 4 && kartu >= 1){
                        cout << "Silahkan menunggu pegawai datang untuk melakukan pembayaran.\n"; 
                    }
                    else {
                        cout << "Pilihan tidak valid.\n";
                        continue;
                    }
                }
                else if (metode == 3){
                    cout << "Silahkan untuk meng-scan QR untuk melakukan pembayaran.\n";
                    
                }
                }
        }        
          
        choice = getValidIntegerInput("Tekan '0' untuk kembali ke menu utama: \n");
    } while (choice != 0);
}

int main() {
    int choice, nomorMeja;
    string nama;
    bool running = true;

    identitas(nama, nomorMeja);

    while (running) {
        beranda();
        choice = getValidIntegerInput("");

        switch (choice) {
            case 1:
                tampilkanDaftarMenu();
                break;
            case 2:
                keranjang();
                break;
            case 3:
                pembayaran();
                break;
            case 4:
                running = false;
                clearScreen();
                cout << "\nTerima kasih.\n";
                break;
            default:
                cout << "\nPilihan salah! Coba ulangi kembali.\n";
                system("pause");
                break;
        }
    }

    return 0;
}
