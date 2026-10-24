#include <iostream>

// целая часть числа
int num_size(const char* s) {
	int s_size = 0;

	while (s[s_size] != '.' && s[s_size] != '\0') {
		++s_size;
	}

	return s_size;
}

// сравнение по модулю
int modelcheck(const char* a, const char* b) {
	int a_size = num_size(a);
	int b_size = num_size(b);

	// если целые части разные по сайзу, то очев
	if (a_size < b_size) {
		return -1;
	}
	if (a_size > b_size) {
		return 1;
	}

	// если одинаковые, сравниваем по символьно
	for (int i = 0; i < a_size; ++i) {
		if (a[i] > b[i]) {
			return 1;
		}
		if (a[i] < b[i]) {
			return -1;
		}
	}

	// если целые части одинаковы, то на дробные переходим
	a += a_size; b += b_size;
	if (*a == '.') {
		++a;
	}
	if (*b == '.') {
		++b;
	}

	while (*a != '\0' || *b != '\0') {
		char d_a = (*a == '\0') ? '0' : *a;
		char d_b = (*b == '\0') ? '0' : *b;

		if (d_a < d_b) {
			return -1;
		}
		if (d_a > d_b) {
			return 1;
		}

		if (*a != '\0') {
			++a;
		}
		if (*b != '\0') {
			++b;
		}
	}

	return 0;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		return 0;
	}

	// argv[1] - указатель на первое
	const char* a = argv[1];
	// argv[2] - указатель на второе
	const char* b = argv[2];

/*
1. сравним знаки
2. 
*/
	bool is_a_neg = (*a == '-');
	bool is_b_neg = (*b == '-');

	// скипаем знаки для сравнения чисел
	if (*a == '-' || *a == '+') {
		++a;
	}
	if (*b == '-' || *b == '+') {
		++b;
	}

	int res = 0;
	if (is_a_neg != is_b_neg) {
		res = is_a_neg ? -1 : 1; // очевно, что положительное больше отрицательного
	} else {
		res = modelcheck(a, b);

		// меняем знак модуля, т.к. отриц числа
		if (is_a_neg) {
			res *= -1;
		}
	}

	if (res < 0) {
		std::cout << "less" << std::endl;
	} else if (res > 0){
		std::cout << "greater" << std::endl;
	} else {
		std::cout << "equal" << std::endl;
	}

	return 0;
}