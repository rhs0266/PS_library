#include "testlib.h"
#include <assert.h>

using namespace std;

void check(){
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    for (int i=1;i<=n;i++){
    	for (int j=1;j<=m;j++){
    		inf.readInt(-10000,10000,format("a[%d][%d]",i,j));
    		if (j<m) inf.readSpace();
    	}
    	inf.readEoln();
    }
}

int main(int argc, char* argv[])
{
    registerValidation(argc, argv);
    
    check();
    inf.readEof();
    return 0;
}
