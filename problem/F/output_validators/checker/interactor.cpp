#include "testlib.h"
#include <bitset>
#include <string>
using namespace std;
using ll = long long;
#define rep(i, a, b) for(int i = a; i < b; i++)
#define rrep(i, a, b) for(int i = a; i <= b; i++)
#define rvep(i, a, b) for(int i = a; i >= b; i--)


const int MAX_N = 1.2e5 + 5;
const int MAX_M = 60 + 5;
ll skill[MAX_N][MAX_M];
int n, m;
int main(int argc, char * argv[])
{
    registerTestlibCmd(argc, argv);
    

    n = inf.readInt(1, MAX_N);
    m = inf.readInt(1, MAX_M);
    rrep(i, 1, n){
        rrep(j, 1, m){
            skill[i][j] = inf.readInt(0, 1e8);
        }
    }

    ll pa = ouf.readLong(0LL, 1e10, "sum");
    ll ja = ans.readLong(0LL, 1e10, "sum");
    // check the solution is valid
    ll sum = 0;
    bitset<MAX_N> usedId, usedAbility;
    int id, abi;
    rrep(i, 1, m){
        id = ouf.readInt(0, MAX_N, "Id");
        abi = ouf.readInt(0, MAX_N, "Ability");
        if(usedId[id]){
            quitf(_wa, "id : '%d' has been already used", id);
        }
        if(usedAbility[abi]){
            quitf(_wa, "abilitiy : '%d' has been already used", abi);
        }
        usedId[id] = usedAbility[abi] = true;
        sum += skill[id][abi];
    }

    if(sum != pa){
        quitf(_wa, "ans:'%d' is not equal to sum:'%d'", pa, sum);
    }

    if(ja > pa)
        quitf(_wa, "expected '%d', found '%d'", ja, pa);

    else if(ja < pa)
        quitf(_wa, "expected '%d', found '%d'", ja, pa);

    
    if (!ouf.seekEof())
        quitf(_fail, "expected exactly one token in the answer file");
    
    quitf(_ok, "answer is '%d'", ja);
}
