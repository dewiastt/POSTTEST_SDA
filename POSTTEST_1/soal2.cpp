#include <iostream>
using namespace std;

int main() {
    const int n = 3;
    int matriks[n][n] = {
        {9, 3, 3},
        {4, 1, 7},
        {3, 8, 2}
    };

    int jumlahDiagonalUtama = 0;
    int jumlahDiagonalSekunder = 0;

    for (int i = 0; i < n; i++) {
        jumlahDiagonalUtama += matriks[i][i];           
        jumlahDiagonalSekunder += matriks[i][n - 1 - i];
    }

    int total = jumlahDiagonalUtama + jumlahDiagonalSekunder;
    if (n % 2 == 1) {
        total -= matriks[n/2][n/2];
    }

    cout << "Matriks 3x3:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matriks[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nJumlah Diagonal Utama   : " << jumlahDiagonalUtama << endl;
    cout << "Jumlah Diagonal Sekunder: " << jumlahDiagonalSekunder << endl;
    cout << "Total Kedua Diagonal    : " << total << endl;

    return 0;
}
