#include "testlib.h"
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#define FOR(i,n,m) for (int i=(n);i<=(m);i++)
#define NM 100005
using namespace std;

void make(int n,int m){
	cout << n << " " << m << endl;
	FOR (i,1,n){
		FOR (j,1,m){
			cout << rnd.next(-10000,10000);
			if (j<m) cout << " ";
		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    make(atoi(argv[2]), atoi(argv[3])); // N M
    
    return 0;
}
