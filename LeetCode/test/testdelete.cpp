//
// Created by root on 18-3-4.
//

class A {
public:
    int a[100];
//    ~A(){};

};

int main()
{
    while(1)
    {
        A* pa = new A[100];
        delete[] pa;
    }
    return 0;
}
