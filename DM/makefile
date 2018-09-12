clean:
	rm -rf testdata; mkdir testdata;\
	rm DM; rm CHECKER

DM:
	g++ data_maker.cpp -o DM; ./DM

CHECKER:
	g++ ./generators/checker.cpp -o CHECKER
