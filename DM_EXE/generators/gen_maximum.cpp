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
			cout << 10000;
			if (j<m) cout << " ";
		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    make(100, 100); // N M
    
    return 0;
}
