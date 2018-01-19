#include<iostream>
#include<random>
#include<set>
#include<cstring>
#define SQRT2 1.414213562
#define SBASE 0.506931309
using namespace std;

std::random_device rd;
std::mt19937_64 e2(rd());

int cnt[100][1000], last[100][1000];
set<int> S;

bool test(int n, int m, int d) {
    uniform_int_distribution<int> dist32(std::llround(0), std::llround(m-1));

    for(int j=0; j<d; j++) {
        memset(cnt[j], 0, sizeof(int) * m);

        for(int i = 1; i<=n; i++) {
            int v = dist32(e2);
            cnt[j][v]++;
            last[j][v] = i;
            
            //cout << " " << i << "(" << v << ")";        
        }
        //cout << endl;
    }    
    
    S.clear();
    for(int j=0; j<d; j++) {
        for(int i=0; i<m; i++) {
            if (cnt[j][i] == 1)
                S.insert(last[j][i]);
        }    
    }
    return S.size() == n;
}

int round(int total, int n, int m, int d) {
    int count = 0;
    for(int i=0; i<total; i++)
        if (not test(n, m, d))
            count++;
    return count;
}

int main() {
//    int n = 100;
    for(int n = 10; n < 1000; n += 10) {
        double delta = 0.01;

        int m1 = 2*n;
        int d1 = ceil(log2(n/delta));
        int m2 = ceil(SQRT2*n);
        int d2 = ceil(log(delta/n)/log(SBASE));
    
        int total = 10000;
    
        cout << delta;
    
        int r1 = round(total, n, m1, d1);
        cout << " " << r1/(double)total;
        
        int r2 = round(total, n, m2, d2);
        cout << " " << r2/(double)total;
        cout << endl;
    }

}
