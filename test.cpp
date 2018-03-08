#include "l0sampler.cpp"

int T[10000];
int main() {

/* //    SSparse S(30, 1);
    SSparse S(30, 6, 42);
    cout << " " << S.d << " " << S.w << endl;
    
    for(int k=1; k<=30; k++)
        S.update(dist32(e2) % 100007, 1);
    
    set<Item> V;
    cout << " " << S.recover(V) << endl;

    for(auto it = V.begin(); it != V.end(); it++) {
        cout << " " << it->index << "=" << it->value << endl;
    }
    cout << endl;*/

    cout << sizeof(OneSparse) << endl;

    for(int i=1; i<7; i++) {
        int n = 30, m = 8;
        int total = 10000, count = 0;

        L0Sampler S(1<<m, i);
        cout << " " << S.m << " " << S.d << " " << S.bytes() << endl;

        for(int j=0; j<total; j++) {
            L0Sampler S(1<<m, i);
            
            for(int k=1; k<=n; k++)
                S.update(k, 1);
            
            Item item;
            if (not S.recover(item)) {         
                count++;
            } else {
                T[item.index]++;
            }
        }
        cout << i << " " << count/(double)total << ":";
        for(int j=1; j<=n; j++) {
            cout << " " << T[j];
        }
        cout << endl;

    }
}
