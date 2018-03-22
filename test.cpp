#include "l0sampler.cpp"
using namespace std;

int cnt1[200], cnt2[200];
int step = 32;
int tests = 1000;
int size = ceil(log2(step*128))+5;

void test1(int n) {
    L0Sampler sampler(size, 1);
    Item item;
    
    for(int j=1; j<=n; j++) {
        sampler.update(j*37, 1);
        if (j % step == 0) {
            if (sampler.recover(item))
                cnt1[j/step]++;
        }
    }
}

void test2(int n) {
    L0SamplerAlt sampler(size, 1);
    Item item;
    
    for(int j=1; j<=n; j++) {
        sampler.update(j*37, 1);
        if (j % step == 0) {
            if (sampler.recover(item))
                cnt2[j/step]++;
        }
    }
}

int round(int total, int n) {
    for(int i=1; i<=total; i++) {
        if (i%10 == 0) 
            cerr << i << endl;
        test1(n);
        test2(n);
    }
}

int main() {
    round(tests, 128*step);
    
    for(int i=1; i<=128; i++) {
        cout << i*step << "\t" << 1-cnt1[i]/(double)tests << "\t" << 1-cnt2[i]/(double)tests << endl;
    }
}
