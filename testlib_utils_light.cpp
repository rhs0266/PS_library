#include "testlib.h"
#include <iostream>
#include <time.h>
#include <assert.h>
#include <unordered_map>
#define sp ' '
#define nl '\n'

using namespace std;


/*
selecet_distinct := select distinct <num> numbers in [<low>, <high>].
*/
vector<int> select_distinct(int low, int high, int num) {
    assert(num <= high - low + 1);
    unordered_map<int, int> mem;
    vector<int> res;
    int s = low;
    for (int i = 1; i <= num; i++) {
        int trg = rnd.next(s, high);

        if (mem.find(s) == mem.end()) mem[s] = s;
        if (mem.find(trg) == mem.end()) mem[trg] = trg;
        swap(mem[s], mem[trg]);
        res.push_back(mem[s]);

        s++;
    }
    return res;
}

/*
distribute := distribute <pie> to the <num> people. each person has at least one pie.
*/
vector<int> distribute(int pie, int num) {
    vector<int> res = select_distinct(1, pie - 1, num - 1);
    res.push_back(pie);

    sort(res.begin(), res.end());

    for (int i = num - 1; i >= 1; i--) res[i] -= res[i - 1];
    return res;
}

/*
distribute_nullable := distribute <pie> to the <num> people. each person has equal or more than 0.
*/
vector<int> distribute_nullable(int pie, int num) {
    vector<int> res;
    for (int i = 0; i < num - 1; i++) {
        res.push_back(rnd.next(0, pie));
    }
    res.push_back(pie);

    sort(res.begin(), res.end());

    for (int i = num - 1; i >= 1; i--) res[i] -= res[i - 1];
    return res;
}

/*
gen_names := generate names which length between <min_len> and <max_len>.
*/
vector<string> gen_names(int n, int min_len, int max_len, bool redundant) {
    vector<string> res;
    for (int i=0;i<n;i++){
        int len = rnd.next(min_len, max_len);
        string name = "";
        for (int j=0;j<len;j++){
            name += char('a' + rnd.next(0, 25));
        }
        
        bool flag = true;
        if (!redundant) {
            for (int j=0;j<i;j++){
                if (res[j] == name) flag = false;
            }
        }
        if (!flag){
            i--;
            continue;
        }
        res.push_back(name);
    }
    return res;
}

vector<bool> check_distinct(int n, int m) {
    vector<bool> res(n);
    vector<int> sel = select_distinct(0, n-1, m);
    for (int x: sel) res[x] = true;
    return res;
}

void make(){
}

int main(int argc, char* argv[])
{
	registerGen(argc, argv, 1);
    	auto z = [argv](int idx) -> int {
	    return atoi(argv[idx]);
	};
	make();
	return 0;
}
