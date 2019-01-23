#include <iostream>

void sum(int a, int b , int &c){
    c = a + b;
}

int main(int argc, char const *argv[])
{
    int c = 0;

    sum(2, 3, c);

    std::cout << c << std::endl;
    
    return 0;
}
