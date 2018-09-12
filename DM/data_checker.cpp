#include "testlib.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <string>

#define MAXLEN 1000005

char bufA[MAXLEN], bufB[MAXLEN];

using namespace std;

//FILE *in = fopen("data_info.txt", "r");

bool compare(string fileA, string fileB){
    FILE *inA = fopen(fileA, "r"), *inB = fopen(fileB, "r");
    assert(inA != NULL && inB != NULL);
    for (;;){
        if (feof(inA) && feof(inB)){
            return true;
        }
        if (feof(inA) && !feof(inB)){
            while (fgets(bufB, MAXLEN, inB)!=NULL){
                int idx=0;
                while (bufB[idx]){
                    if (bufB[idx]=='\n' || bufB[idx]==' '){
                        idx++;
                        continue;
                    }else{
                        return false;
                    }
                }
            }
        }
        if (!feof(inA) && feof(inB)){
            while (fgets(bufA, MAXLEN, inA)!=NULL){
                int idx=0;
                while (bufA[idx]){
                    if (bufA[idx]=='\n' || bufA[idx]==' '){
                        idx++;
                        continue;
                    }else{
                        return false;
                    }
                }
            }
        }
        string strA, strB;
        strA = bufA, strB = bufB;
        // TODO : trim strA and strB, compare them
    }
}

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
