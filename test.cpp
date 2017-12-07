#include "l0sampler.cpp"

int T[10000];
int main() {
    for(int i=1; i<=100001; i+=1000) {
        L0Sampler S(i, 0.01);
        cout << i << " " << S.bytes() << endl;
    }
/*    L0Sampler S(1024, 0.1);
    for(int i=2; i<=1000; i+=2) {
        S.update(i, -10);
        S.update(i-1, 10);
        S.update(i-1, -10);
    }

    Item item; 
    if (S.recover(item)) {
        T[item.index]++;
        cout << item.index << " " << item.value << endl;
    } else {
        cout << "FAILED!" << endl;
    }
    cout << S.bytes() << endl;*/

}
