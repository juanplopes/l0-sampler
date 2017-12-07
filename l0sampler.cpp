#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <cmath>
#include <set>
#include "MurmurHash3.cpp"
using namespace std;

struct Item {
    int index;
    long long value;
    Item(int index, long long value) : index(index), value(value) {}
    
    inline bool operator< (const Item &that) const {
        if (index != that.index) return index < that.index;
        return value < that.value;
    }
};

struct OneSparse {
    long long w0, w1, w2;
    
    OneSparse() : w0(0), w1(0), w2(0) {}
    
    void update(int i, long delta) {
        w0 += delta;
        w1 += delta*i;
        w2 += delta*i*i;
    }
    
    Item recover() {
        return Item(w1/w0, w0);
    } 
    
    int size() {
        if (w0 == 0) return 0;
        if (w1*w1 != w0*w2) return 2;
        return 1;
    }
};

struct SSparse {
    int d, w, s;
    long long w2;
    
    boost::numeric::ublas::matrix<OneSparse> M;
    
    SSparse(int s, double delta) : 
        s(s), w2(0), d(ceil(log2(s/delta))), w(2*s), M(d, w) {
    }
    
    void update(int i, long long delta) {
        uint64_t hash[2];
        uint32_t seed = 0;
        
        for(int j=0; j<d; j++) {
            MurmurHash3_x64_128(&i, sizeof(int), seed, hash);
            
            M(j, hash[0]%w).update(i, delta);
            seed = hash[1];
        }
        
        w2 += i*delta;
    }
    
    bool recover(set<Item> &V) {
        for(int i=0; i<d and V.size() < s; i++)
            for(int j=0; j<w and V.size() < s; j++)
                if (M(i, j).size() == 1)
                    V.insert(M(i, j).recover());
            
        long long sig = 0;
        for(set<Item>::iterator it = V.begin(); it != V.end(); it++) {
           sig += it->index * it->value;
        }
        return w2 == sig;
    }
    
    int bytes() {
        return d*w*sizeof(Item) + sizeof(w2);
    }
};

class L0Sampler {
    

}


int main() {
    SSparse S(10, 0.001);
    cout << S.d << " " << S.w << endl;
    
    for(int i=2; i<=22; i+=2) {
        S.update(i, 10);
        S.update(i-1, 10);
        S.update(i-1, -10);
    }
    
    set<Item> Q;
    cout << S.recover(Q) << endl;
    for(set<Item>::iterator it = Q.begin(); it != Q.end(); it++) {
      cout << " " << it->index << " "  <<  it->value << endl;
    }
    cout << S.bytes() << endl;

}
