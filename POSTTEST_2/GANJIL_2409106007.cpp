#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Item {
    string namaItem;
    int jumlah;
    string tipe;
    Item* next;
};

Item* head = nullptr;

void tambahItem(string nama, string tipe, int jumlahAwal) {
    Item* baru = new Item{nama, jumlahAwal, tipe, nullptr};
    if (head == nullptr) {
        head = baru;
    } else {
        Item* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = baru;
    }
    cout << ">> Item \"" << nama << "\" berhasil ditambahkan!\n";
}

void sisipItem(string nama, string tipe, int jumlahAwal, string nim) {
    int posisi = (nim[nim.size()-1] - '0') + 1;  

    Item* baru = new Item{nama, jumlahAwal, tipe, nullptr};

    if (posisi <= 1 || head == nullptr) {
        baru->next = head;
        head = baru;
        cout << ">> Item \"" << nama << "\" disisipkan di posisi 1\n";
        return;
    }

    Item* temp = head;
    int hitung = 1;
    while (temp->next != nullptr && hitung < posisi - 1) {
        temp = temp->next;
        hitung++;
    }

    baru->next = temp->next;
    temp->next = baru;

    cout << ">> Item \"" << nama << "\" berhasil disisipkan di posisi " << posisi << endl;
}

void hapusItemTerakhir() {
    if (head == nullptr) {
        cout << ">> Inventory kosong!\n";
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        cout << ">> Item terakhir berhasil dihapus!\n";
        return;
    }
    Item* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
    cout << ">> Item terakhir berhasil dihapus!\n";
}

void gunakanItem(string nama) {
    if (head == nullptr) {
        cout << ">> Inventory kosong!\n";
        return;
    }
    Item* temp = head;
    Item* prev = nullptr;
    while (temp != nullptr && temp->namaItem != nama) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << ">> Item tidak ditemukan!\n";
        return;
    }
    temp->jumlah--;
    cout << ">> Menggunakan 1 " << temp->namaItem << ". Sisa: " << temp->jumlah << endl;
    if (temp->jumlah <= 0) {
        cout << ">> Item habis, node dihapus!\n";
        if (prev == nullptr) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }
        delete temp;
    }
}


int tampilkanInventory() {
    if (head == nullptr) {
        cout << ">> Inventory kosong!\n";
        return 0;
    }

    cout << "\n=============================================================\n";
    cout << "                       DAFTAR INVENTORY                        \n";
    cout << "=============================================================\n";
    cout << left << setw(5) << "| No"
         << setw(25) << "| Nama Item"
         << setw(20) << "| Tipe"
         << setw(10) << "| Jumlah" << "|\n";
    cout << "-------------------------------------------------------------\n";

    Item* temp = head;
    int i = 1;
    while (temp != nullptr) {
        cout << left << setw(5) << ("| " + to_string(i))
             << setw(25) << ("| " + temp->namaItem)
             << setw(20) << ("| " + temp->tipe)
             << setw(10) << ("| " + to_string(temp->jumlah)) << "|\n";
        temp = temp->next;
        i++;
    }
    cout << "=============================================================\n";
    return 1;
}

int main() {
    string namaUser, nim;
    cout << "Masukkan Nama: ";
    getline(cin, namaUser);
    cout << "Masukkan NIM: ";
    cin >> nim;

    int duaDigit = stoi(nim.substr(nim.size()-2));  
    head = new Item{namaUser, duaDigit, "ID", nullptr};

    int pilih;
    do {
        cout << "\033[1;36m\n======================================================\n";
        cout << "\033[1;33mGAME INVENTORY MANAGEMENT \n";
        cout << "\033[1;37m[" << namaUser << " - " << nim << "]\n";
        cout << "\033[1;36m======================================================\033[0m\n";

        cout << "\033[1;32m| 1. Tambah Item Baru                              |\033[0m\n";
        cout << "\033[1;34m| 2. Sisipkan Item                                 |\033[0m\n";
        cout << "\033[1;31m| 3. Hapus Item Terakhir                           |\033[0m\n";
        cout << "\033[1;35m| 4. Gunakan Item                                  |\033[0m\n";
        cout << "\033[1;36m| 5. Tampilkan Inventory                           |\033[0m\n";
        cout << "\033[1;33m| 0. Keluar                                        |\033[0m\n";
        cout << "\033[1;36m======================================================\033[0m\n";
        cout << "Pilih menu: ";
        cin >> pilih; cin.ignore();

        if (pilih == 1) {
            string nama, tipe;
            cout << "Nama Item: "; getline(cin, nama);
            cout << "Tipe Item: "; getline(cin, tipe);
            tambahItem(nama, tipe, duaDigit);  
        } 
        else if (pilih == 2) {
            string nama, tipe;
            cout << "Nama Item: "; getline(cin, nama);
            cout << "Tipe Item: "; getline(cin, tipe);
            sisipItem(nama, tipe, duaDigit, nim);  
        } 
        else if (pilih == 3) {
            hapusItemTerakhir();
        } 
        else if (pilih == 4) {
            string nama;
            cout << "Masukkan nama item yang ingin digunakan: ";
            getline(cin, nama);
            gunakanItem(nama);
        } 
        else if (pilih == 5) {
            tampilkanInventory();
        }

    } while (pilih != 0);

    cout << "Program selesai Terimakasih\n";
    return 0;
}
