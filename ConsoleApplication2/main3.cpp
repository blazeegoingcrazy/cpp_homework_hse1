#include <iostream>
#include <iomanip>

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

    double* arr = new double[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    double sumka = 0;
    for (int i = 0; i < n; ++i) {
        double x;
        std::cin >> x;
        sumka += arr[i] * x;
    }

    std::cout << std::fixed << std::setprecision(15) << sumka  << std::endl;
    delete[] arr;

    return 0;
}