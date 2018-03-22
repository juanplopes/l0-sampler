#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <random>
#include <cmath>
#include <set>
#include "MurmurHash3.cpp"
#define P 18446744073709551557ull
#define SQRT2 1.414213562
#define SBASE 0.506931309
using namespace std;
using namespace boost::multiprecision;

std::random_device rd;
std::mt19937_64 e2(rd());
std::uniform_int_distribution<unsigned long long> dist(std::llround(0), std::llround(P-1));
std::uniform_int_distribution<unsigned int> dist32(std::llround(0), std::llround(-1u));

uint128_t ppow(uint128_t a, uint128_t b) {
    return powm(a, b, uint128_t(P));
}

struct Item {
    int index;
    long long value;
    Item() : index(0), value(0) {}
    Item(int index, long long value) : index(index), value(value) {}
    
    inline bool operator< (const Item &that) const {
        if (index != that.index) return index < that.index;
        return value < that.value;
    }
};

struct OneSparse {
    int64_t w0, w1;
    int128_t w2; 
    uint64_t z;
    
    OneSparse() : w0(0), w1(0), w2(0), z(dist(e2)) {}

    void update(int i, long delta) {
        w0 += delta;
        w1 += delta*i;
        w2 += delta * ppow(z, i);
    }
    
    Item recover() {
        return Item(w1/w0, w0);
    } 
    
    int size() {
        if (w0 == 0) return 0;
        if (w2 != w0 * ppow(z, w1/w0)) return 2;
        return 1;
    }
};

struct L0Sampler {
    boost::numeric::ublas::matrix<OneSparse> M;
    int m, d;
    unsigned int seed;
    
    L0Sampler(int m, int d) : 
        m(m), d(d), seed(dist32(e2)), M(d, m) { 
    }
    
    void update(int i, long long delta) {
        unsigned int seed = this->seed;
        for(int j=0; j<d; j++) {
            uint64_t hash = h(i, seed);
            seed = (unsigned int)hash;
            if (hash == 0) continue;
            
            int pos = floor(log2(hash));
            M(j, pos).update(i, delta);
        }
    }
    
    uint64_t h(int i, unsigned int seed) {
        uint64_t hash[2];
        MurmurHash3_x64_128(&i, sizeof(int), seed, hash);
        return hash[0] % (1<<m);
    }
    
    bool recover(Item &recovered) {
        for(int i=0; i<d; i++) {
            for(int j=0; j<m; j++) {
                if(M(i, j).size() == 1) {
                    recovered = M(i, j).recover();
                    return true;
                }
            }
        }
        return false;
    }
    
    int bytes() {
        return m*d*sizeof(OneSparse)+sizeof(L0Sampler);
    }
};

struct L0SamplerAlt {
    boost::numeric::ublas::matrix<OneSparse> M;
    int m, d;
    unsigned int seed;
    
    L0SamplerAlt(int m, int d) : 
        m(m), d(d), seed(dist32(e2)), M(d, m) { 
    }
    
    void update(int i, long long delta) {
        unsigned int seed = this->seed;
        for(int j=0; j<d; j++) {
            for(int k=0; k<m; k++) {
                uint64_t hash = h(i, seed);
                seed = (unsigned int)hash;
                if (hash == 0) continue;
                
                int pos = floor(log2(hash));
                if (pos != k) continue;
                M(j, pos).update(i, delta);
            }
        }
    }
    
    uint64_t h(int i, unsigned int seed) {
        uint64_t hash[2];
        MurmurHash3_x64_128(&i, sizeof(int), seed, hash);
        return hash[0] % (1<<m);
    }
    
    bool recover(Item &recovered) {
        for(int i=0; i<d; i++) {
            for(int j=0; j<m; j++) {
                if(M(i, j).size() == 1) {
                    recovered = M(i, j).recover();
                    return true;
                }
            }
        }
        return false;
    }
    
    int bytes() {
        return m*d*sizeof(OneSparse)+sizeof(L0Sampler);
    }
};

