#include <iostream>
#include <vector>

using namespace std;

int * sumA (const int *a, const int *b){
    int *c = new int[3];
    for (int i = 0; i < 3; i++){
        c[i] = a[i] + b[i];
    }
    return c;
}

int * sumB (const int *a, const int *b){
    int *c = new int[4];
    for (int i = 0; i < 4; i++){
        c[i] = a[i] + b[i];
    }

    return c;
}

vector<int> sumC(const vector<int> & a, const vector<int> &b){
    vector<int> c;
    for (int i = 0; i < a.size(); i++){
        c.push_back(a[i] + b[i]);
    }
    return c;
}

int main(int argc, char const *argv[])
{
    //inits
    int aa[3], ab[3];
    //int ac[3];

    int * ac;
    for (int i = 0; i < 3; i++){
        aa[i] = i + 4;
        ab[i] = i + 2;
    }

    ac = sumA(aa,ab);

    for (int i = 0; i < 3; i++){
        cout << "A " << ac[i] << endl;
    }

    int* ba = new int[4];
    int* bb = new int[4];
    int* bc = new int[4];

    for (int i = 0; i < 4; i++){
        ba[i] = 40 - i;
        bb[i] = 20 - i;
    }

    bc = sumB(ba, bb);
    
    for (int i = 0; i < 4; i++){
        cout << "B " << bc[i] <<endl;
    }

    vector<int> ca({1, 4, 9});
    vector<int> cb({2, 6, 4});

    vector<int> cc;

    cc = sumC(ca, cb);

    for (int i = 0; i < cc.size(); i++){
        cout << "C " << cc[i] << endl;
    }

    delete ba;
    ba = nullptr;
    delete bb;
    bb = nullptr;
    delete bc;
    bc = nullptr;

    return 0;
}
