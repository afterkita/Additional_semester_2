// Additional_2 (2 семестр).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*Реализовать сортировку и оцените ее сложность.

Вариант 7
Сортировка слиянием.

Вариант 8
Сортировка Шелла.
*/

#include <iostream>
#include <vector>
// Перемешивание вектора (Позаимствовал из 3 лабы)
void Blender(std::vector<int>& victor)
{
    int l = victor.size();
    int r = 0;
    for (int i = 0;i < l;i++)
    {
        r = rand() % l;
        if (r != i)
        {
            std::swap(victor[i], victor[r]);
        }
    }
}
// Функция для вывода вектора после сортировки (Позаимствовал из 3 лабы)
void Printer(std::vector<int>& victor)
{
    int l = victor.size();
    if (l <= 2000)
    {
        for (int i = 0;i < l;i++)
        {
            std::cout << victor[i] << " ";
        }
    }
    std::cout << std::endl << std::endl;
}
// Сортировка слиянием (Позаимствовал из 2 лабы)
/* Лучшее время работы О = n*log(n)
*  Худшее время работы O = n*log(n)
*/
void MSort_B(std::vector<int>& values, std::vector<int>& buffer, int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        MSort_B(values, buffer, l, m);
        MSort_B(values, buffer, m + 1, r);

        int k = l;
        for (int i = l, j = m + 1; i <= m || j <= r; )
        {
            if (j > r || (i <= m && values[i] < values[j]))
            {
                buffer[k] = values[i];
                ++i;
            }
            else {
                buffer[k] = values[j];
                ++j;
            }
            ++k;
        }
        for (int i = l; i <= r; ++i)
        {
            values[i] = buffer[i];
        }
    }
}
void MSort(std::vector<int>& values)
{
    if (!values.empty())
    {
        std::vector<int> buffer(values.size());
        MSort_B(values, buffer, 0, values.size() - 1);
    }
}

// Сортировка Шелла
/* Лучшее время работы О = n*log(n)
*  Худшее время работы O = n*n
*  Среднее время O = (n*n)/2
*/
void SSort(std::vector<int>& values)
{
    int h = values.size();
    int d = h;
    d = d / 2;
    while (d > 0)
    {
        for (int i = 0; i < h - d; i++)
        {
            int j = i;
            while (j >= 0 && values[j] > values[j + d])
            {
                std::swap(values[j],values[j + d]);
                j--;
            }
        }
        d = d / 2;
    }
}
int main()
{
    setlocale(LC_ALL, "Rus");
    std::vector<int> victor; // N значений массива
    srand(time(0));
    int N = 100;
    for (int i = 0;i < N;i++)
    {
        victor.push_back(i);
    }
    std::cout << "Перемешиваем" << std::endl;
    Blender(victor);
    Printer(victor);
    std::cout << "Сортировка Шелла" << std::endl;
    SSort(victor);
    Printer(victor);
    std::cout << "Перемешиваем" << std::endl;
    Blender(victor);
    Printer(victor);
    std::cout << "Сортировка слиянием" << std::endl;
    MSort(victor);
    Printer(victor);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
