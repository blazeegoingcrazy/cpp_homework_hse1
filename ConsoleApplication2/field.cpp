#include "field.h"

#include <cstdlib>
#include <ctime>
#include <queue>
// Вывод произвольного поля
void cout_field(std::vector<std::vector<char>>& matrix, int& n, int& m) {
	// вывод номеров столбцов
	for (int i = 0; i < m; ++i) {
		std::cout << " " << i + 1;
	}
	std::cout << std::endl;

	// вывод номеров строк и само поле
	for (int i = 0; i < n; ++i) {
		std::cout << i + 1;
		for (int j = 0; j < m; ++j) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void write_field_to_file(std::vector<std::vector<char>>& f, int& n, int& m) {
	std::ofstream output("GameField.txt", std::ios::out | std::ios::trunc);

	if (output.is_open()) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				output << f[i][j];
			}
			output << std::endl;
		}
		output.close();
	}
	else {
		std::cerr << "File is not found" << std::endl;
		std::abort();
	}
}

std::vector<std::vector<char>> read_field_from_file(std::ifstream& input) {
	std::vector<std::vector<char>> game_field;

	std::string line;
	while (std::getline(input, line)) {
		game_field.push_back(std::vector<char>(line.begin(), line.end()));
	}

	return game_field;
}

int generate_field(std::vector<std::vector<char>> f, int& n, int& m, int& x, int& y) {
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	// расстановка мин 
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			// квадрат 3*3 безопасной зоны
			if ((x - 2 <= i && i <= x) && (y - 2 <= j && j <= y)) {
				f[i][j] = '#';
			}
			// рандомное распределение мин
			else {
				int r = std::rand() % 2; // 0 - нет бомбы, 1 - есть бомба
				(r ? f[i][j] = '*' : f[i][j] = '#');
			}
		}
	}
	// заполнение цифровых полей
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (f[i][j] == '*') {
				continue;
			}
			else {
				int mines_around_cnt = 0;
				// клетка не задевает пределы поля, поэтому считаем чисто
				if ((0 <= i - 1 && i + 1 <= n - 1) && (0 <= j - 1 && j + 1 <= m - 1)) {
					for (int q = i - 1; q <= i + 1; ++q) {
						for (int k = j - 1; k <= j + 1; ++k) {
							if (f[q][k] == '*') {
								++mines_around_cnt;
							}
						}
					}
					f[i][j] = mines_around_cnt + '0';
				}
				// клетка является углом (0, 0)
				else if (i == 0 && j == 0) {
					for (int q = 0; q <= 1; ++q) {
						for (int k = 0; k <= 1; ++k) {
							if (f[q][k] == '*') {
								++mines_around_cnt;
							}
						}
					}
					f[i][j] = mines_around_cnt + '0';
				}
				// клетка является углом (0, m - 1)
				else if (i == 0 && j == m - 1) {
					for (int q = 0; q <= 1; ++q) {
						for (int k = m - 2; k <= m - 1; ++k) {
							if (f[q][k] == '*') {
								++mines_around_cnt;
							}
						}
					}
					f[i][j] = mines_around_cnt + '0';
				}
				// клетка является углом (n - 1, 0)
				else if (i == n - 1 && j == 0) {
					for (int q = n - 2; q <= n - 1; ++q) {
						for (int k = 0; k <= 1; ++k) {
							if (f[q][k] == '*') {
								++mines_around_cnt;
							}
						}
					}
					f[i][j] = mines_around_cnt + '0';
				}
				// клетка является углом (n - 1, m - 1)
				else if (i == n - 1 && j == m - 1) {
					for (int q = n - 2; q <= n - 1; ++q) {
						for (int k = m - 2; k <= m - 1; ++k) {
							if (f[q][k] == '*') {
								++mines_around_cnt;
							}
						}
					}
					f[i][j] = mines_around_cnt + '0';
				}
				// клетка задевает верхную или нижнюю стенку поля
				else if ((0 > i - 1 || i + 1 > n - 1) && (0 <= j - 1 && j + 1 <= m - 1)) {
					// клетка задевает верхную стенку поля
					if (0 > i - 1) {
						for (int q = 0; q <= 1; ++q) {
							for (int k = j - 1; k <= j + 1; ++k) {
								if (f[q][k] == '*') {
									++mines_around_cnt;
								}
							}
						}
						f[i][j] = mines_around_cnt + '0';
					}
					// клетка задевает нижнюю стенку поля
					else {
						for (int q = i - 1; q <= n - 1; ++q) {
							for (int k = j - 1; k <= j + 1; ++k) {
								if (f[q][k] == '*') {
									++mines_around_cnt;
								}
							}
						}
						f[i][j] = mines_around_cnt + '0';
					}
				}
				// клетка задевает левую или правую стенку поля
				else if ((0 <= i - 1 && i + 1 <= n - 1) && (0 > j - 1 || j + 1 > m - 1)) {
					// клетка задевает левую стенку поля
					if (0 > j - 1) {
						for (int q = i - 1; q <= i + 1; ++q) {
							for (int k = 0; k <= 1; ++k) {
								if (f[q][k] == '*') {
									++mines_around_cnt;
								}
							}
						}
						f[i][j] = mines_around_cnt + '0';
					}
					// клетка задевает правую стенку поля
					else {
						for (int q = i - 1; q <= i + 1; ++q) {
							for (int k = j - 1; k <= m - 1; ++k) {
								if (f[q][k] == '*') {
									++mines_around_cnt;
								}
							}
						}
						f[i][j] = mines_around_cnt + '0';
					}
				}
			}
		}
	}

	//f[x - 1][y - 1] = '!';
	//cout_field(f, n, m);
	write_field_to_file(f, n, m);
	int mines = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (f[i][j] == '*') {
				mines++;
			}
		}
	}
	return mines;
}

// псевдо-bfs
void field_chain_reaction(int x, int y,
	const std::vector<std::vector<char>>& mine_field, std::vector<std::vector<char>>& f, int& n, int& m) {
	if (f[x][y] != '#') {
		return;
	}

	std::queue<std::pair<int, int>> q;

	// Открываем старт-ячейку, перенося символ из скрытого поля
	f[x][y] = mine_field[x][y];
	q.push(std::make_pair(x, y));

	while (!q.empty()) {
		std::pair<int, int> cur_point = q.front();
		q.pop();

		// Если в открытой ячейке цифра больше '0' (от '1' до '8'), 
		// мы её показали, но дальше не даем
		if (mine_field[cur_point.first][cur_point.second] != '0') {
			continue;
		}

		// Если '0' - проверка соседей для открытия
		for (int dl = -1; dl <= 1; ++dl) {
			for (int dr = -1; dr <= 1; ++dr) {
				if (dl == 0 && dr == 0) {
					continue;
				}

				int sosed_left = cur_point.first + dl;
				int sosed_right = cur_point.second + dr;

				// Проверка границ поля
				if (sosed_left >= 0 && sosed_left < n &&
					sosed_right >= 0 && sosed_right < m) {

					// Условие: сосед должен быть строго '#' и это не мина
					if (f[sosed_left][sosed_right] == '#' && mine_field[sosed_left][sosed_right] != '*') {

						// Открываем ячейку для пользователя
						f[sosed_left][sosed_right] = mine_field[sosed_left][sosed_right];
						q.push(std::make_pair(sosed_left, sosed_right));
					}
				}
			}
		}
	}
}

bool change_user_field_ui(std::vector<std::vector<char>>& f, int& n, int& m,
	std::ifstream& inp, const std::string& cmd, int& x, int& y) {
	// пометка бомб в user_field
	if (cmd == "flag") {
		f[x - 1][y - 1] = '!';
		return false;
	}
	
	std::vector<std::vector<char>> mine_field = read_field_from_file(inp);
	// при попадании на бомбу
	if (mine_field[x - 1][y - 1] == '*') {
		return true;
	}

	field_chain_reaction(x - 1, y - 1, mine_field, f, n, m);
	cout_field(f, n, m);
	return false;
}

bool check_victory(const std::vector<std::vector<char>>& f, int& n, int& m, int& mines) {
	int hidden_or_flagged_cnt = 0;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			// Если ячейка еще не открыта (там '#' или '!')
			if (f[i][j] == '#' || f[i][j] == '!') {
				hidden_or_flagged_cnt++;
			}
		}
	}

	// Победа, если колво неоткрытых мест  равно колву мин
	return hidden_or_flagged_cnt == mines;
}
