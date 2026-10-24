#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

void cout_field(std::vector<std::vector<char>>& matrix, int& n, int& m);

// возвращает колво мин
int generate_field(std::vector<std::vector<char>> f, int& n, int& m, int& x, int& y);
void write_field_to_file(std::vector<std::vector<char>>& f, std::ofstream& output, int& n, int& m);
std::vector<std::vector<char>> read_field_from_file(std::ifstream& input);

// Возвращает true - если бомба при press, иначе - false
bool change_user_field_ui(std::vector<std::vector<char>>& f, int& n, int& m, 
	std::ifstream& inp, const std::string& cmd, int& x, int& y);

void field_chain_reaction(int x, int y,
	const std::vector<std::vector<char>>& mine_field, std::vector<std::vector<char>>& user_field);

bool check_victory(const std::vector<std::vector<char>>& f, int& n, int& m, int& mines);