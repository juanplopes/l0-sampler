#include<iostream>
#include<random>
#include<set>
#include<cstring>
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

int main() {
    int total = 100000, count = 0;
    for(int i=0; i<total; i++) {
        if (not test(30, 42, 12))
            count++;
    }
    cout << count << "/" << total << ": " << (count/(float)total) << endl;

}
