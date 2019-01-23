#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    int size = 5;
    
    //allocating arrays
    int v[size];

    for (int i = 0; i < size; i++){
        v[i] = i * 2;
    }

    int* x = new int[size];

    for (int i = 0; i < size; i++){
        x[i] = (i + 1) * 2;
    }

    vector<int> y;

    for (int i = 0; i < size; i++){
        y.push_back(v[i] + x[i]);
    }

    //printing
    for (int i = 0; i < size; i++){
        cout << y[i] << endl;
    }


    //deleting arrays
    delete x;
    x = nullptr;

    return 0;
}
