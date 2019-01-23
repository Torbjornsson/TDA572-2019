#include <iostream>

int sum(int a, int b){
    return a + b;
}

int main(int argc, char const *argv[])
{
    std::cout << sum(2, 3) << std::endl;
    return 0;
}