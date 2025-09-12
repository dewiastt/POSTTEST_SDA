#include <iostream>
using namespace std;

int tukarNilai(int **x, int **y) {
    int temp = **x;
    **x = **y;
    **y = temp;
    return 0; 
}

int tampilanalamat(int *ptr, string nama) {
    cout << nama << " -> Nilai: " << *ptr << ", Alamat: " << ptr << endl;
    return 0;
}

int main() {
    int a, b;

    cout << "PROGRAM PERTUKARAN NILAI MENGGUNAKAN DOUBLE POINTER" << endl;
    cout << "====================================================" << endl;

    cout << "Masukkan nilai A: ";
    cin >> a;
    cout << "Masukkan nilai B: ";
    cin >> b;

    int *ptrA = &a;
    int *ptrB = &b;

    cout << "\n=== SEBELUM ===" << endl;
    tampilanalamat(ptrA, "A");
    tampilanalamat(ptrB, "B");

    tukarNilai(&ptrA, &ptrB);

    cout << "\n=== SETELAH ===" << endl;
    tampilanalamat(ptrA, "A");
    tampilanalamat(ptrB, "B");

    return 0;
}
