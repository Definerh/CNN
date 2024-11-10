#include <iostream>
#include <vector>
#include <cmath>

int imax = 0, jmax = 0;
int i = 0, j = 0;
std::vector <std::vector <bool> > input;
std::vector <bool> cache_vector;

const bool kernel[5][5] = {
	{1, 0, 0, 0, 1},
	{0, 1, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 1, 0},
	{1, 0, 0, 0, 1}
};

void Input()
{
	bool ch = 0;
	input.clear();
	cache_vector.clear();
	std::cout << "Please input the size of the image:";
	std::cin >> imax >> jmax;
	for (i = 0; i < imax; i++) {
		cache_vector.clear();
		for (j = 0; j < jmax; j++) {
			std::cin >> ch;
			cache_vector.push_back(ch);
		}
		input.push_back(cache_vector);
	}
}

void Test_Input()
{
	std::cout << std::endl;
	for(int i = 0; i < imax; i++) {
		for(int j = 0; j < jmax; j++) {
			std::cout << input[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Remove(bool cache_number[5][5],int x, int y){
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cache_number[i][j] = input[x + i][y + j];
		}
	}
}

short Calc(bool cache_number[5][5]){
	short sum = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			sum += kernel[i][j] * cache_number[i][j];
		}
	}
	return sum;
}

short Convolute_and_Pool()
{
	short result[imax - 4][jmax - 4] = {0};
	bool cache_number[5][5] = {0};
	for (int i = 0; i < (imax - 4); i++) {
		for (int j = 0; j < (jmax - 4); j++) {
			Remove(cache_number, i, j);
			result[i][j] = Calc(cache_number);
		}
	}
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

double Activate(short num){
	return exp(num) / (1 + exp(num));
} 

int main(void)
{
	Input();
//	Test_Input();
	std::cout << Activate(Convolute_and_Pool()) << std::endl;
	return 0;
}
