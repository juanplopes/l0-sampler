#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <cmath>
#include "MurmurHash3.h"
using namespace std;
using namespace boost::numeric::ublas;


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
    matrix<OneSparse<T> > M;
    
    SSparse(int s, double delta) {
        int w = 2*s;
        int d = ceil(log2(s/delta));   
        
        M.resize(w, d, false);
    }
    
    void update(int i, T delta) {
        
    }
};



int main() {

}
