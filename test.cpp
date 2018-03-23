#include "l0sampler.cpp"
using namespace std;

int cnt1[200], cnt2[200];
int dist1[200], dist2[200];
int step = 32;
int barstep = step*16;
int tests = 1000;
int size = ceil(log2(step*128))+5;

bool test1(int n, Item &item) {
    L0Sampler sampler(size, 1);
    
    for(int j=1; j<=n; j++) {
        sampler.update(j, 1);
        if (j % step == 0) {
            if (sampler.recover(item))
                cnt1[j/step]++;
        }
    }
    return sampler.recover(item);    
}

bool test2(int n, Item &item) {
    L0SamplerAlt sampler(size, 1);
     
    for(int j=1; j<=n; j++) {
        sampler.update(j, 1);
        if (j % step == 0) {
            if (sampler.recover(item))
                cnt2[j/step]++;
        }
    }
    return sampler.recover(item);
}

int round(int total, int n) {
    Item item;
    for(int i=1; i<=total; i++) {
        if (i%10 == 0) 
            cerr << i << endl;
        if (test1(n, item))
            dist1[(item.index-1)/barstep]++;
        if (test2(n, item))
            dist2[(item.index-1)/barstep]++;
    }
}

int main() {
    round(tests, 128*step);
    
    for(int i=1; i<=128; i++) {
        cout << i*step << "\t" << (i*step)/pow(2, floor(log2(i*step))) << "\t" << 1-cnt1[i]/(double)tests << "\t" << 1-cnt2[i]/(double)tests << endl;
    }
    
    for(int i=0; i<8; i++) {
        cout << i*barstep << "\t" << dist1[i]/(double)tests << "\t" << dist2[i]/(double)tests << endl;
    }
}
