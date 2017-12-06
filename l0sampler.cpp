#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <cmath>
#include "MurmurHash3.h"
using namespace std;


template <class T>
struct OneSparse {
    T w0, w1, w2;
    
    void update(int i, T delta) {
        w0 += delta;
        w1 += delta*i;
        w2 += delta*i*i;
    }
    
    T value() {
        return w0;
    }
    
    int index() {
        return w1/w0;
    }
    
    int size() {
        if (w0 == 0) return 0;
        if (w1*w1 != w0*w2) return 2;
        return 1;
    }
};

template <class T>
struct SSparse {
    int d, w, s;
    boost::numeric::ublas::matrix<OneSparse<T> > M;
    
    SSparse(int s, double delta) : 
        s(s), d(ceil(log2(s/delta))), w(2*s), M(d, w) {
    }
    
    void update(int i, T delta) {
        uint64_t hash[2];
        uint32_t seed = 0;
        
        for(int j=0; j<d; j++) {
            MurmurHash3_x64_128(&i, sizeof(int), seed, hash);
            
            M(j, hash[0]%w).update(i, delta);
            seed = hash[1];
        }
    }
    
    bool recover(vector<OneSparse<T> > &V) {
        return true;
    }
};



int main() {

}
