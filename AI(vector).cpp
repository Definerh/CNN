#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>

int imax = 0, jmax = 0;
std::vector <std::vector <bool> > _input;
std::vector <bool> v;

const bool juanjihe[5][5] = {
	{1, 0, 0, 0, 1},
	{0, 1, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 1, 0},
	{1, 0, 0, 0, 1}
};

short juanji();
double jihuo(short num);
void _remove(bool use[5][5], int nowx, int nowy);
short calc(bool use[5][5]);
short chihua(bool **result);

signed int main(int argc, const char *argv[]) {
	int i = 0, j = 0;
	bool ch = false;
	_input.clear();
	v.clear();
	std::cout << "Please input the size of the image:";
	std::cin >> imax >> jmax;
//	std::cout << imax << jmax;
	for (i = 0; i < imax; i++) {
		v.clear();
		for (j = 0; j < jmax; j++) {
			std::cin >> ch;
			v.push_back(ch);
		}
		_input.push_back(v);
	}
	/*
		std::cout << std::endl;
		for(int i=0; i<imax; i++) {
			for(int j=0; j<jmax; j++) {
				std::cout<<_input[i][j]<<" ";
			}
			std::cout << std::endl;
		}
	*/
//	std::cout << juanji();
	std::cout << "它有" << jihuo(juanji()) * 100.0 << "%的概率包含着X";
	return (signed int)0;
}

double jihuo(short num) {
//	return 10 / (1 + pow(2.7182818284590452353602874713527, (-1) * (num)));
	return (tanh(num - 2)) / 2 + 0.5;
}

void _remove(bool use[5][5], int nowx, int nowy) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			use[i][j] = _input[nowx + i][nowy + j];
		}
	}
}

short calc(bool use[5][5]) {
	short max = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			max += juanjihe[i][j] * use[i][j];
		}
	}
	return max;
}

short chihua(bool **result) {
	short max = 0;

	for (int i = 0; i < imax - 4; i++) {
		for (int j = 0; j < jmax - 4; j++) {
			if (*((int *)result + i * jmax + j ) > max) {
				max = *((int *)result + i * jmax + j );
			}
		}
	}
	return max;
}

short juanji() {

//	std::vector <std::vector <bool> > result;
	short result[imax - 4][jmax - 4] = {0};
	bool use[5][5] = {0};
	for (int i = 0; i < (imax - 4); i++) {
		for (int j = 0; j < (jmax - 4); j++) {
			_remove(use, i, j);
			result[i][j] = calc(use);
//			std::cout << result[i][j] << " ";
		}
	}
	/*	for (int i = 0; i < imax; i++) {
			for (int j = 0; j < jmax; j++) {
				std::cout << result[i][j] << " ";
			}
			std::cout << std::endl;
		}*/
	return chihua((bool **)result);
}
