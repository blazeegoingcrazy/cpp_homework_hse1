#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <clocale>
#include <windows.h>

#include "field.h"

int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	setlocale(LC_ALL, ".UTF-8");

	int n, m;
	std::cin >> n >> m;

	std::vector<std::vector<char>> user_field(n, std::vector<char>(m, '#')); // поле игрока
	cout_field(user_field, n, m);

	bool is_game_over = false;
	bool is_victory = false;
	int cnt = 0; // номер хода
	int mines = 0;

	// запуск игры
	while (!is_game_over && !is_victory) {
		++cnt; // новый ход
		std::cout << "Введите команду и индекс поля." << std::endl;
		if (cnt <= 2) {
			std::cout << "Пример команд: " << std::endl << "flag 1 1 -> ставит пользовательский флажок в (1,1) для отметки бомб.";
			std::cout << std::endl << "press 1 1 -> производит нажатие на поле (1,1)." << std::endl;
		}
		
		int x, y;
		std::string command = "press";
		// самый первый ход
		if (cnt == 1) {
			std::cout << std::endl << "Введите любую клетку: " << std::endl;
			std::cin >> x >> y;

			// генерируем новое поле
			mines = generate_field(user_field, n, m, x, y);
			std::ifstream input("GameField.txt");

			// обновляем интерфейс относительно действия игрока
			change_user_field_ui(user_field, n, m, input, command, x, y);

			input.close();

			is_victory = check_victory(user_field, n, m, mines);
		}
		else {
			std::cin >> command;
			std::cin >> x >> y;

			std::ifstream input("GameField.txt");

			if (input.is_open()) {
				if (command == "press") {
					is_game_over = change_user_field_ui(user_field, n, m, input, command, x, y);

					if (!is_game_over) {
						is_victory = check_victory(user_field, n, m, mines);
					}
				}
				else if (command == "flag") {
					change_user_field_ui(user_field, n, m, input, command, x, y);
					cout_field(user_field, n, m);
					is_victory = check_victory(user_field, n, m, mines);
				}
				else {
					std::cerr << "Введена неправильная команда" << std::endl;
				}
			}

			input.close();
		}
	}
	if (is_game_over) {
		std::cout << "Бум! Вы проиграли. Игра окончена!" << std::endl;
	}
	else if (is_victory) {
		std::cout << "Поздравляем! Вы успешно разминировали поле за " << cnt << " ходов!" << std::endl;
	}
}