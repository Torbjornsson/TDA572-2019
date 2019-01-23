#include <iostream>
#include <vector>

using namespace std;

void sumA (const int *a, int *b){
    for (int i = 0; i < 5; i++){
        b[i] = a[i];
    }
}

void sumB (const vector<int> & a, vector<int> &b){
    b = a;
}

int main(int argc, char const *argv[])
{
    int * aa = new int[5];
    int * ab = new int[5];
    for (int i = 0; i < 5; i ++){
        aa[i] = 15 + i;
    }

    sumA(aa, ab);
    for (int i = 0; i < 5; i++){
        cout << "A " << ab[i] << endl;
    }


    vector<int> ba({7, 4, 9});
    vector<int> bb;

    sumB(ba, bb);

    for (int i = 0; i < bb.size(); i++){
        cout << "B " << bb[i] << endl;
    }


    delete aa;
    aa = nullptr;
    delete ab;
    ab = nullptr;
    
    return 0;
}
