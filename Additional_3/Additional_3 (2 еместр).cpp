// Additional_3 (2 еместр).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*Реализуйте двусвязный циклический список, предусмотрите в нем функции добавления элемента, 
вставки, удаления, обхода списка в обоих направлениях.*/

#include <iostream>

using namespace std;

struct List
{
    List* Next;
    List* Prev;
    int x;
};

void ADD(List* head, int x)
{
    List* p = new List;
    p->x = x;
    if (head->Next == nullptr)
    {
        head->Next = p;
        p->Next = p;
        p->Prev = p;
    }
    else if (head->Next == head->Next->Next)
    {
        p->Next = head->Next;
        p->Prev = head->Next;
        head->Next->Next = p;
        head->Next->Prev = p;
    }
    else
    {
        p->Next = head->Next;
        p->Prev = head->Next->Prev;
        head->Next->Prev->Next = p;
        head->Next->Prev = p;
    }

}
void Print(List* head)
{
    std::cout << std::endl << std::endl;
    List* p = new List;
    p = head->Next;
    do // Обход вперёд
    {
        std::cout << p->x << " ";
        p = p->Next;
    } while (p != head->Next);
    std::cout << std::endl;
    p = head->Next;
    do // Обход назад
    {
        std::cout << p->x << " ";
        p = p->Prev;
    } while (p != head->Next);
}
void Incert(List* head, int x, int k)
{
    List* p = new List;
    p->x = x;
    if (head->Next == nullptr)
    {
        if (k == 0)
        {
            head->Next = p;
            p->Next = p;
            p->Prev = p;
        }
    }
    else if (head->Next == head->Next->Next)
    {
        if (k == 0 || k == 1)
        {
            if (k == 0)
            {
                head->Next = p;
                p->Next = p;
                p->Prev = p;
            }
            else
            {
                p->Next = head->Next;
                p->Prev = head->Next;
                head->Next->Next = p;
                head->Next->Prev = p;
            }
        }

    }
    else
    {
        int u = 0;
        List* r = new List;
        r = head->Next;
        do
        {
            if (u == k)
            {
                p->Next = r;
                p->Prev = r->Prev;
                r->Prev->Next = p;
                r->Prev = p;
            }
            u++;
            r = r->Next;
        } while (r != head->Next);
    }
}
void Delete(List* head, int k)
{
    if (head->Next == nullptr)
    {

    }
    else if (head->Next == head->Next->Next)
    {
        if (k == 0)
        {
            delete[] head->Next;
            head->Next = nullptr;
        }
    }
    else
    {
        int u = 0;
        List* r = new List;
        r = head->Next;
        do
        {
            if (u == k)
            {
                r->Prev->Next = r->Next;
                r->Next->Prev = r->Prev;
                delete[] r;
                break;
            }
            u++;
            r = r->Next;
        } while (r != head->Next);
    }
}
int main()
{
    setlocale(LC_ALL, "Rus");
    List* head = new List;
    head->Prev = nullptr;
    head->Next = nullptr;

    ADD(head, 10);
    ADD(head, 110);
    ADD(head, 101);
    ADD(head, 1011);
    Incert(head, 22, 2);
    Print(head);
    Incert(head, 222, 2);
    Print(head);
    Delete(head, 2);
    Print(head);
}