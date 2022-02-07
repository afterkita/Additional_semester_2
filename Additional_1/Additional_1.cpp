// Additional_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*
Задача №1
«Рекурсия»
Задачи во всех вариантах следует выполнять с применением рекурсии. Циклы использовать нельзя.
Вариант 8.
Дана последовательность {Ai} (Ai < 1000) длины N<1000. Найти среднее арифметическое ее чисел.
*/

#include <iostream>
#include <fstream>
float rec(std::ifstream& in, float count, float score) {
	float f;
	int i = 0;
	if (in >> i) {
		std::cout << i << " ";
		count++;
		score += i;
		f = rec(in, count, score);
		return f;
	}
	else {
		 f = score / count;
		return f;
	}
}
int main()
{
	setlocale(LC_ALL, "Rus");
	std::ifstream in ("input.txt");
	std::cout<< std::endl << rec(in,0,0);	
}