#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Item {
    string namaItem;
    int jumlah;
    string tipe;
    Item* next;
    Item* prev;
};

Item* head = nullptr;
Item* tail = nullptr;
int panjangList = 0;

void tambahItem(string nama, string tipe, int jumlahAwal) {
    Item* baru = new Item{nama, jumlahAwal, tipe, nullptr, nullptr};
    if (head == nullptr && tail == nullptr) {
        head = baru;
        tail = baru;
    } else {
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
    }
    panjangList++;
    cout << ">> Item \"" << nama << "\" berhasil ditambahkan di akhir!\n";
}

void sisipItem(string nama, string tipe, int jumlahAwal, string nim) {
    int posisi = (nim[nim.size()-1] - '0') + 1;

    if (posisi < 1 || posisi > panjangList + 1) {
        cout << ">> Posisi tidak valid!\n";
        return;
    }

    Item* baru = new Item{nama, jumlahAwal, tipe, nullptr, nullptr};

    if (posisi == 1) { 
        if (head == nullptr) {
            head = tail = baru;
        } else {
            baru->next = head;
            head->prev = baru;
            head = baru;
        }
    } else if (posisi == panjangList + 1) { 
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
    } 
    else { 
        Item* temp = head;
        for (int i = 1; i < posisi - 1; i++) {
            temp = temp->next;
        }
        baru->next = temp->next;
        baru->prev = temp;
        temp->next->prev = baru;
        temp->next = baru;
    }

    panjangList++;
    cout << ">> Item \"" << nama << "\" berhasil disisipkan di posisi " << posisi << endl;
}

void hapusItemTerakhir() {
    if (head == nullptr && tail == nullptr) {
        cout << ">> Inventory kosong!\n";
        return;
    } else if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Item* hapus = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete hapus;
    }
    panjangList--;
    cout << ">> Item terakhir berhasil dihapus!\n";
}

void gunakanItem(string nama) {
    if (head == nullptr) {
        cout << ">> Inventory kosong!\n";
        return;
    }

    Item* temp = head;
    while (temp != nullptr && temp->namaItem != nama) {
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
        if (temp == head && temp == tail) { 
            head = tail = nullptr;
        } else if (temp == head) { 
            head = head->next;
            head->prev = nullptr;
        } else if (temp == tail) { 
            tail = tail->prev;
            tail->next = nullptr;
        } else { 
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        delete temp;
        panjangList--;
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
    head = tail = new Item{namaUser, duaDigit, "ID", nullptr, nullptr};
    panjangList = 1;

    int pilih;
    do {
        cout << "\033[1;36m\n======================================================\n";
        cout << "\033[1;33mGAME INVENTORY MANAGEMENT (DOUBLE LINKED LIST)\n";
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

    cout << "Program selesai, Terimakasih\n";
    return 0;
}
