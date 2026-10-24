#include <iostream>

// Разворот на отрезке [begin, end)
void reverse(int* begin, int* end) {
    while (begin < end) {
        --end;

        if (begin >= end) {
            break;
        }

        int temp = *begin;
        *begin = *end;
        *end = temp;

        ++begin;
    }
}

// сдвиг
void rotate(int* arr, int n, int k) {
    int shift = k % n;

    if (shift < 0) {
        shift += n;
    }

    // Три разворота
    reverse(arr, arr + n);
    reverse(arr, arr + shift);
    reverse(arr + shift, arr + n);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 0;
    }

    int n = 0;
    const char* p = argv[1];

    while (*p != '\0') {
        n = n * 10 + (*p - '0');
        ++p;
    }

    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    int k;
    std::cin >> k;

    rotate(arr, n, k);

    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << std::endl;
    }

    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;
    delete[] arr;

    return 0;
}