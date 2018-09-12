#include "testlib.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <string>

using namespace std;

//FILE *in = fopen("data_info.txt", "r");


/* Batch style data checker */
int main(int argc, char* argv[])
{
    freopen("data_info.txt","r",stdin);
    assert(stdin != NULL);
    assert(argc == 2);
    int data_n = atoi(argv[1]);

    cout << "@ Execute Checker" << endl;
    
    system(("g++ checker.cpp -o testdata/checker").c_str());

    for (int i=1;i<=data_n;i++){

        cout << "# " << i << " ........... ";

        char number_buffer[1005];
        sprintf(number_buffer,"%d",i);
        string number = number_buffer;
        
        system(("./testdata/checker << ./testdata/"+number+".in >> ./testdata/checker.out").c_str());
        
        if (compare("./testdata/"+number+".out", "./testdata/check.out")){
            cout << "Accept" << endl;
        }else{
            cout << "Wrong Answer" << endl;
        }

        system(("rm ./testdata/checker.out").c_str());
    }

    return 0;
}
