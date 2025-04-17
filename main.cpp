#include <iostream>
#include <string>
#include <limits>
#include <malloc.h>
 
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
     cout << "| 4. Top-up E-wallet                   |" << endl;
     cout << "| 5. Keluar                            |" << endl;
     cout << "========================================" << endl;
     cout << "\nMasukkan pilihanmu (1-5): ";
 }
 
 //==========LIST MENU MAKANAN/MINUMAN==========//
 struct MenuItem {
     int id;
     string nama;
     int harga;
 };
 
 struct Pesanan {
     int id;
     string nama;
     int qty;
     int harga;
 };

 struct node {
    Pesanan data;
    node *next;
    node *prev;
};

 node *head = NULL;
 node *tail = NULL;

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
 
void insertLast(int menuID, string nama, int quantity, int harga) {
    node *new_node = new node{{menuID, nama, quantity, harga}, NULL, NULL};

    node *current = head;
    while (current) {
        if (current->data.id == menuID) {
            current->data.qty += quantity;
            return;
        }
        current = current->next;
    }

    if (!head) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
}

 const int maksPesanan = 100;
 Pesanan pesanan[maksPesanan];
 int jumlahPesanan = 0;
 
 void tampilkanDaftarMenu() {
    int pilihan, qty;
    int lanjut;

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
                insertLast(pilihan, daftarMenu[pilihan - 1].nama, qty, daftarMenu[pilihan - 1].harga);
            } else {
                cout << "Jumlah tidak valid.\n";
            }
        } else {
            cout << "ID salah.\n";
        }
        do {
            lanjut = getValidIntegerInput("\nTambahkan menu lain? (1 untuk tambah / 0 untuk kembali): ");
            if (lanjut != 1 && lanjut != 0) {
                cout << "Pilihan tidak valid.\n";
            }
        } while (lanjut != 1 && lanjut != 0);

    } while (lanjut == 1);
}


void tampilkanKeranjang() {
    node* current = head;
    int i = 1;
    if (!current) {
        cout << "Keranjang masih kosong.\n";
        return;
    }
    while (current) {
        cout << "Pesanan " << i++ << " - ID: " << current->data.id
             << ", Nama: " << current->data.nama
             << ", Jumlah: " << current->data.qty
             << ", Harga: " << current->data.harga << endl;
        current = current->next;
    }
}

void inputMenutambahan() {
    int choice;
    do
    {
        int pilihan = getValidIntegerInput("Masukkan ID Menu yang ingin dipesan (0 untuk kembali): ");
        if (pilihan == 0) break;
        
        if (pilihan >= 1 && pilihan <= jumlahMenu) {
            int qty = getValidIntegerInput("Masukkan jumlah pesanan: ");
            if (qty > 0 && qty <= 100) {
                insertLast(pilihan, daftarMenu[pilihan - 1].nama, qty, daftarMenu[pilihan - 1].harga);
            } else {
                cout << "Jumlah tidak valid.\n";
            }
        } else {
            cout << "ID salah.\n";
        }
    } while (choice != 0);
}

void removebyId(int id) {
    node *current = head;
    while (current) {
        if (current->data.id == id) {

            if (current->prev)
                current->prev->next = current->next;
            else
                head = current->next;

            if (current->next)
                current->next->prev = current->prev;
            else
                tail = current->prev;

            delete current;
            cout << "Pesanan dengan ID " << id << " telah dihapus\n";
            return;
        }
        current = current->next;
    }
    cout << "Pesanan atas ID " << id << " tidak ditemukan\n";
}              

 //==========KERANJANG==========//
 void keranjang() {
    clearScreen();
     int choice;
 
     do {
        cout << "--------------------------Keranjang----------------------------\n";
        if (!head) {
            cout << "Keranjang masih kosong.\n";
        } else {
            tampilkanKeranjang();
        }
        cout << "---------------------------------------------------------------" << endl;
        double totalHarga = 0.0;
        node* current = head; 

        while (current) {
            int id = current->data.id - 1;
            double hargaItem = daftarMenu[id].harga * current->data.qty;
            totalHarga += hargaItem;

            current = current->next;
        }
        cout << "Total harga : Rp " << totalHarga << endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << "Pilihan : " << endl;
        cout << "0 Kembali ke menu utama\n1 Tambah pesanan\n2 Hapus pesanan \n";

        choice = getValidIntegerInput("\nMasukkan pilihan : ");

        if (choice == 1) {
            tampilkanDaftarMenu();
            clearScreen();
        }

        if (choice == 2) {
            int id;
            cout << "Masukan id yang akan dihapus: "; cin >> id;
            removebyId(id);
        }
     } while (choice != 0);
 }

//==========PEMBAYARAN==========//
double saldo = 0.0;
double totalHarga = 0.0;
double total() {
    totalHarga = 0.0;
    node* current = head; 

    while (current) {
        int id = current->data.id - 1;
        double hargaItem = daftarMenu[id].harga * current->data.qty;
        totalHarga += hargaItem;

        cout << daftarMenu[id].id << "\t" 
                << daftarMenu[id].nama << "\t\t" 
                << current->data.qty << "\tRp " 
                << hargaItem << endl;

        current = current->next;
    }
    return totalHarga;
}

void tfbank() {
    int choice;
    int norek = 678912345;
    string bank;

    do {
        clearScreen();
        cout << "Silahkan pilih bank Anda untuk melakukan pembayaran.\n";
        cout << "1. BCA\n";
        cout << "2. Mandiri\n";
        cout << "3. BRI\n";
        cout << "4. BNI\n";
        cout << "5. Keluar\n";
        choice = getValidIntegerInput("Masukkan pilihan (1-5): ");

        switch (choice) {
            case 1:
                bank = "BCA";
                break;
            case 2:
                bank = "Mandiri";
                break;
            case 3:
                bank = "BRI";
                break;
            case 4:
                bank = "BNI";
                break;
            case 5:
                return;
            default:
                cout << "Pilihan tidak tersedia.\n";
                continue;
        }
        clearScreen();
        cout << "---------------------- PEMBAYARAN VIA " << bank << " ----------------------\n";
        total();
        cout << "\n";
        cout << "Total Harga: Rp " << totalHarga << endl;
        cout << "--------------------------------------------------------------------------\n";
        cout << "Silahkan transfer ke nomor rekening: " << norek << endl;
        break;
    } while (choice != 0);
}

void pembayaranEwallet(double totalHarga) {
    int konfirmasi;
    clearScreen();
    cout << "-------------- PEMBAYARAN VIA E-WALLET --------------\n";
    cout << "Saldo E-wallet Anda: Rp " << saldo << endl;
    cout << "Total Harga: Rp " << totalHarga << endl;

    if (saldo < totalHarga) {
        cout << "Saldo tidak mencukupi untuk pembayaran!\n";
    } else {
        int konfirmasi = getValidIntegerInput("Apakah Anda yakin ingin melakukan pembayaran? (1 untuk Ya / 0 untuk Tidak): ");
    
        if (konfirmasi == 1) {
            saldo -= totalHarga;
            cout << "Pembayaran berhasil!\n";
            cout << "Saldo E-wallet sisa: Rp " << saldo << endl;
        } else if (konfirmasi == 0) {
            cout << "Pembayaran dibatalkan!\n";
        } else {
            cout << "Pilihan tidak valid!\n";
        }
    }
}

void pembayaran() {
    int choice;
    char lanjut;

    do {
        clearScreen();
        cout << "--------------- Pembayaran ---------------\n\n";

        if (!head) {
            cout << "Keranjang masih kosong \n";
        } else {
            cout << "Daftar Pesanan Anda:\n";
            cout << "\nID\tNama Makanan\t\tJumlah\tHarga\n";
            cout << "--------------------------------------------\n";
            total();
            cout << "--------------------------------------------\n";
            cout << "Total Harga: Rp " << totalHarga << endl; 

            while (true) {
                cout << "\nApakah ingin melakukan pembayaran? (y/n): ";
                cin >> lanjut;

                
                if (cin.fail() || (lanjut != 'y' && lanjut != 'Y' && lanjut != 'n' && lanjut != 'N')) {
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "Input tidak valid! Harap masukkan 'y' atau 'n'.\n";
                } else {
                    break; 
                }
            }

            if (lanjut == 'y' || lanjut == 'Y') {
                cout << "\nPilih metode pembayaran: \n";
                cout << "1. Tunai\n";
                cout << "2. Transfer Bank\n";
                cout << "3. E-Wallet\n";

                int metode = getValidIntegerInput("Masukkan pilihan (1-3): \n");
                if (metode < 1 || metode > 3) {
                    cout << "Pilihan tidak valid.\n";
                    continue;
                }
                if (metode == 1) {
                    cout << "Silahkan pergi ke kasir untuk melakukan pembayaran.\n";
                } else if (metode == 2) {
                    tfbank();
                } else if (metode == 3) {
                    pembayaranEwallet(totalHarga);
                }
            }
        }

        choice = getValidIntegerInput("Tekan '0' untuk kembali ke menu utama: \n");
    } while (choice != 0);
}

void topup() {
    int choice;
    do {
        clearScreen();
        cout << "-----------------TOP-UP E-WALLET-----------------\n";
        cout << "Saldo E-wallet Anda: Rp " << saldo << endl;
        cout << "Pilih menu: \n";
        cout << "1. Top Up\n";
        cout << "2. Kembali ke menu utama\n";
        choice = getValidIntegerInput("Masukkan pilihan (1-2): \n");

        switch (choice)
        {
        case 1:
            double topupAmount;
            topupAmount = getValidIntegerInput("Top up saldo Anda: Rp ");
            saldo += topupAmount;
            cout << "Top up berhasil!\n";
            cout << "Saldo Anda sekarang: " << saldo << endl;
            system("pause");
            break;
        case 2:
            break;
        default:
            cout << "Pilihan tidak valid.\n";
            system("pause");
            break;
        }
    } while (choice != 2);
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
                topup();
                break;
             case 5:
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