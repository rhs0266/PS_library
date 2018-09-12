MANUAL

data_maker.cpp : data_info.txt 안의 정보를 사용하여 데이터를 만들어내는 코드이다. generator codes와 solution code와 validator code를 필요로 한다.

generator code : 주어진 인자들(arguments)을 기반으로 데이터를 stdout에 출력하는 코드이다.

solution code  : 문제를 올바르게 해결하는 코드이다.

validator code : 주어진 입력이 description을 올바르게 따랐는 지 확인하는 코드이다.

data_checker.cpp : 만들어진 data 를 checker.cpp를 이용하여 검수하는 코드이다.
