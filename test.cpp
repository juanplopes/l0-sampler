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

    for(double i=0.01; i<=1; i+=0.01) {
        double delta = i;
        int n = 30;
        int total = 10000, count = 0;

        SSparse S(n, delta);
        cout << " " << S.d << " " << S.w << endl;

        for(int j=0; j<total; j++) {
            SSparse S(n, delta);
//            cout << " " << S.d << " " << S.w << endl;
            
            for(int k=1; k<=n; k++)
                S.update(dist32(e2) % 100007, 1);
            
            set<Item> V;
            if (not S.recover(V)) {         
                count++;
            }
        }
        cout << i << " " << count << endl;

    }
}
