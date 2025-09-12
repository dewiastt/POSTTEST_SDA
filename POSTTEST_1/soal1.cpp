#include <iostream>
using namespace std;

int* dibalik(int* arr, int n) {
    int* awal = arr;
    int* akhir = arr + n - 1;

    while (awal < akhir) {
        int temp = *awal;
        *awal = *akhir;
        *akhir = temp;

        awal++;
        akhir--;
    }
    return arr; 
}

int main() {
    const int n = 7;
    int arr[n];

    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 3;
    }

    cout << "Array sebelum dibalik: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    int* hasil = dibalik(arr, n);
    cout << "Array sesudah dibalik: ";
    for (int i = 0; i < n; i++) {
        cout << hasil[i] << " ";
    }
    cout << endl;

    return 0;
}
