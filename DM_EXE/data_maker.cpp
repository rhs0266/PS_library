#include "testlib.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <string>

using namespace std;

//FILE *in = fopen("data_info.txt", "r");

int gen_n, data_n;
vector<string> gens;
char com[1005]; // command line

void compiles() {
    for (int i = 0; i < gen_n; i++) {
        system(("g++ ./generators/" + gens[i] + ".cpp -o ./generators/generators/" + gens[i]).c_str());
    }
}

/* Batch style data maker */
int main(int argc, char* argv[])
{
    freopen("data_info.txt","r",stdin);
    assert(stdin != NULL);

    //////////////////////////
    // generators           //
    //////////////////////////

    cout << "Compiling Generators......";

    assert(scanf("%d", &gen_n) == 1 && gen_n >= 1);
    
    for (int i = 0; i < gen_n; i++) {
        string gen_name; // without ".cpp"
        cin >> gen_name;
        gens.push_back(gen_name);
    }

    compiles();

    cout << " Done" << endl;


    //////////////////////////
    // make input data      //
    //////////////////////////

    cout << "Making Input Data.........";

    assert(scanf("%d\n", &data_n) == 1 && data_n >= 1);
    for (int i = 1; i <= data_n; i++) {
        fgets(com, 1000, stdin);

        char number_buffer[5];
        sprintf(number_buffer, "%d", i);

        string number = number_buffer;
        string command = com;
        command.erase(command.find_last_not_of(" \n\r\t")+1);
        
        string output_name = number+".in";
        system(("./generators/"+command+" >> testdata/"+output_name).c_str());
    }

    cout << " Done" << endl;

    //////////////////////////
    // validate input data  //
    //////////////////////////

    cout << "Validating Input Data.....";

    system("g++ validator.cpp -o testdata/validator");

    for (int i = 1;i <= data_n; i++) {
        char number_buffer[5];
        sprintf(number_buffer, "%d", i);

        string number = number_buffer;

        system(("./testdata/validator << " + number + ".in").c_str());
    }

    cout << " Done" << endl;

    //////////////////////////
    // make output data     //
    //////////////////////////

    cout << "Making Output Data........";

    system("g++ solution.cpp -o testdata/solution");

    for (int i=1;i<=data_n;i++){

        char number_buffer[5];
        sprintf(number_buffer, "%d", i);

        string number = number_buffer;

        system(("./testdata/solution << " + number + ".in >> " + number + ".out").c_str());
    }
    cout << " Done" <<endl;


    return 0;
}
