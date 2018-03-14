#include<iostream>
#include<random>
#include<set>
#include<cstring>
#define SQRT2 1.414213562
#define SBASE 0.506931309
using namespace std;

std::random_device rd;
std::mt19937_64 e2(rd());

int result[1000][100];
int result2[1000];
int cnt[100];

bool test(int m) {
    uniform_int_distribution<int> dist32(std::llround(-2147483648), std::llround(2147483647));

    int step = m/100;
    memset(cnt, 0, sizeof(cnt));
    for(int j=0; j<m; j++) {
        if (j % step == 0) {
            for(int i=0; i<=32; i++) {
                if (cnt[i] == 1) {
                    result[j/step][i]++;
                    result2[j/step]++;
                    break;
                }
            }
        }
        int v = dist32(e2);
        if (v == 0) continue;
        int zeros = __builtin_clz(v);
        cnt[zeros]++;
    }
    
    for(int i=0; i<=32; i++) {
        if (cnt[i] == 1) return true;
    }
    return false;
}

int round(int total, int m) {
    int count = 0;
    for(int i=1; i<=total; i++) {
        if (i%1000 == 0) 
            cerr << i << endl;
        if (not test(m))
            count++;
    }
    return count;
}

double binom(int n, int k) {
    double p = pow(2, -k);
    return n * p * pow(1-p, n-1);
}

double total(int n) {
    double prob = 1;
    for(int i=1; i<=100; i++) {
        prob *= (1 - binom(n, i));
    }
    return prob;
}

int main() {
    cerr << round(100000, 100)/100000.0 << endl;
    
    for(int i=1; i<100; i++) {
        cout << i << "\t" << 1-result2[i]/100000.0 << endl;
    }
    

    
}
