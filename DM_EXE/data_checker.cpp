#include "testlib.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <string>

#define MAXLEN 1000005


using namespace std;

/* Batch style data checker */
int main(int argc, char* argv[])
{
    freopen("data_info.txt","r",stdin);
    assert(stdin != NULL);
    assert(argc == 3);
    int data_n = atoi(argv[1]);
	string compare = argv[2];

    cout << "@ Execute Checker" << endl;

    for (int i=1;i<=data_n;i++){

        cout << "# " << i << " ........... " << endl;

        char number_buffer[1005];
        sprintf(number_buffer,"%d",i);
        string number = number_buffer;

		string compare = "./standard_checkers/" + compare;
		string input = "./testdata/" + number + ".in";
		string output = "./testdata/" + number + ".out";
		string result = "./generators/checker.out";
        
		// make result
        system(("./generators/checker << ./testdata/"+number+".in >> ./generators/checker.out").c_str());
        
		// compare
		system((compare + " " + input + " " + output + " " + result).c_str());
        
		// remove result
        system(("rm ./generators/checker.out").c_str());
    }

    return 0;
}
