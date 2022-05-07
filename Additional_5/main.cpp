#include <iostream>

/*class Foo
{
public:
    Foo(int j) { i=new int[j]; }
    ~Foo() { delete i; }
private:
    int* i;
};

class Bar: Foo
{
public:
    Bar(int j) { i=new char[j]; }
    ~Bar() { delete i; }
private:
    char* i;
};


void main()
{
    Foo* f=new Foo(100);
    Foo* b=new Bar(200);
    *f=*b;
    delete f;
    delete b;
}
*/
template<typename T>
class Fis {
public:
    Fis(int n) {pt  = new T[n];
        std::cout << " Fis" << "\n";}

    ~Fis() {delete pt;
        std::cout << " ~Fis" << "\n";}

protected:
    T *pt = nullptr;

};

class Foo : public Fis<int> {
public:
    Foo(int j): Fis<int>(j) {
        std::cout << " Foo" << "\n";
    }

    virtual ~Foo() {std::cout << " ~Foo" << "\n"; }
};

class Bar : public Fis<char> {
public:
    Bar(int j): Fis<char>(j) { std::cout << " Bar" << "\n";}

    virtual ~Bar() { std::cout << " ~Bar" << "\n";}

};


int main() {
    Foo *f = new Foo(100);
    Foo *b = reinterpret_cast<Foo *>(new Bar(200));
    delete f;
    *f = *b;



    return 0;
}
