#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <random>
#include <cmath>
#include <set>
#include "MurmurHash3.cpp"
#define P 18446744073709551557ull
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
    long long w0, w1;
    int128_t w2; long long z;
    
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

struct SSparse {
    int d, w, s;
    uint128_t w2; long long z;
    
    boost::numeric::ublas::matrix<OneSparse> M;
    
    SSparse(int s, double delta) : 
        s(s), w2(0), d(ceil(log2(s/delta))), w(2*s), M(d, w), z(dist(e2))  {
    }
    
    void update(int i, long long delta) {
        uint64_t hash[2];
        uint32_t seed = 0;

        for(int j=0; j<d; j++) {
            MurmurHash3_x64_128(&i, sizeof(int), seed, hash);
            
            M(j, hash[0]%w).update(i, delta);
            seed = hash[1];
        }
        
        w2 += delta * ppow(z, i);
    }
    
    bool recover(set<Item> &V) {
        if (w2 == 0) return false;

        uint128_t sig = 0;
        for(int i=0; i<d and V.size() < s; i++) {
            for(int j=0; j<w and V.size() < s; j++) {
                if (M(i, j).size() == 1) {
                    Item r = M(i, j).recover();
                    if (V.insert(r).second) {
                        sig += r.value * ppow(z, r.index);
                    }
                }
            }
        }

        return w2 == sig;
    }
    
    int bytes() {
        return d*w*sizeof(Item)+sizeof(SSparse);
    }
};

struct L0Sampler {
    vector<SSparse> M;
    int m, s, n;
    unsigned int seed;
    uint64_t n3;
    SSparse one;
    
    L0Sampler(int n, double delta) : 
        n(n), n3((uint64_t)n*n*n), s(12*ceil(log2(1/delta))), m(ceil(3*log2(n))+1), 
        seed(dist32(e2)), one(s, delta) { 

        for(int j=0; j<m; j++) {
            M.push_back(SSparse(s, delta));
        }
        
    }
    
    void update(int i, long long delta) {
        uint64_t hash = h(i);
        for(int j=0; j<m; j++)
            if (n3/(1ll<<j) >= hash)
                M[j].update(i, delta);
    }
    
    uint64_t h(int i) {
        uint64_t hash[2];
        MurmurHash3_x64_128(&i, sizeof(int), seed, hash);
 
        return hash[0] % n3;
    }
    
    bool recover(Item &recovered) {
        set<Item> S;
        for(int j=0; j<m; j++) {
            S.clear();
            if (M[j].recover(S)) {
                set<Item>::iterator it = S.begin();
                Item item = *it;
                uint64_t minn = h(item.index);
                for(++it; it != S.end(); it++) {
                    uint64_t cand = h(it->index);
                    if (cand < minn) {
                        minn = cand;
                        item = *it;
                    }
                }
                recovered = item;
                return true;
            }
        }
        return false;
    }
    
    int bytes() {
        return m*M[0].bytes()+sizeof(L0Sampler);
    }
};

