clean:
	rm -rf testdata; mkdir testdata;\
	rm DM; rm CHECKER; rm others

DM:
	g++ data_maker.cpp -o DM; ./DM

CHECKER:
	g++ ./generators/checker.cpp -o others; g++ ./data_checker.cpp -o CHECKER

all:
	make clean; make DM; make CHECKER
