# MANUAL

1. /

* data_maker.cpp : data_info.txt 안의 정보를 사용하여 데이터를 만들어내는 코드이다. generator codes와 solution code와 validator code를 필요로 한다.

* data_checker.cpp : 만들어진 data 를 checker.cpp를 이용하여 검수하는 코드이다.

* data_info.txt : paramete를 제공하는 파일

2. /generators/

* generator codes : 주어진 인자들(arguments)을 기반으로 데이터를 stdout에 출력하는 코드이다.

* *solution.cpp*  : 문제를 올바르게 해결하는 코드이다.

* *checker.cpp* : 검수용 코드이다.

* *validator.cpp* : 주어진 입력이 description을 올바르게 따랐는 지 확인하는 코드이다.

3. /standard_checkers/

* lcmp : Line compare, Ignore whitespaces

* rcmp6 : Single or more double, max any error 1e-6

* ncmp : Single or more int64, Ignore whitespaces

-----------------------------------------------------------------------------------------------------------

# How to use

1. /generators/ 에 데이터 생성용 코드들(*[generator name].cpp*)과 *solution.cpp* 와 *validator.cpp* 를 작성한다.

2. *data_info.txt*에 첫 줄에는 generator 갯수 **gen_n**, 다음 **gen_n**개 줄에는 cpp 이름들(".cpp"는 제외), 다음 줄에는 test data 개수 **data_n**, 다음 **data_n**개 줄에는 test data 1개당 1줄의 command

3. /에서 $make clean => **주의** /testdata/ 내부 내용 삭제

4. /에서 $make DM => /testdata/ 내부에 데이터 생성

5. /에서 $make CHECKER => / 에 *CHECKER* exe 파일 생성

6. /에서 $./CHECKER {cmp} => {cmp}를 통해서 ./generators/checker.cpp의 결과와 /testdata/ 안의 결과를 비교
