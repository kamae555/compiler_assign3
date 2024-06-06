#include <stdio.h>
#include "sym_table_lab.h" 
// 심볼테이블 관련 헤더 파일을 추가함으로써 함수 선언까지는 완료하였으니 이제 정의만 하자
// 주어진 키를 해시 테이블의 인덱스로 변환
// 문자열 키와 해시 테이블의 크기를 인자로 받아 테이블의 index 반환
// 문자열 키가 뭐야?
// 문자열 키는 심볼 테이블에 저장된 심볼의 이름이다.
// 예시를 보여줘
// 예를 들어, 심볼 테이블에 저장된 심볼의 이름이 "abc"라면, 이 문자열 "abc"가 키가 된다.

int divisionMethod(char* key, int tableSize) {
    unsigned int hash_key = 0;
    int c;

    while (c = *key++) {
        hash_key += c;
    }
    return hash_key % tableSize;
}

int midsquareMethod(char* key, int tableSize) {
    int squared;
    int midPart;
    unsigned int hash_key = 0;
    int c;

    while (c = *key++) {
        hash_key += c;
    }

    squared = hash_key * hash_key;
    midPart = squared / 100 % 1000; // �������� �߰� �κ� ����
    return midPart % tableSize;
}

int foldingMethod(char* key, int tableSize) {
    int fold = 0;
    unsigned int hash_key = 0;
    int c;

    while (c = *key++) {
        hash_key += c;
    }
    
    while (hash_key > 0) {
        fold += hash_key % 10000; // 4�ڸ��� ������ ����
        hash_key /= 10000;
    }
    return fold % tableSize;
}
//divisionMethod: 문자열의 각 문자의 ASCII 값을 더한 후, 
// 해시 테이블의 크기로 나눈 나머지를 반환합니다.
//dsquareMethod: 문자열의 각 문자의 ASCII 값을 더한 후, 
// 그 값을 제곱하여 중간 부분을 추출하고, 해시 테이블의 크기로 나눈 나머지를 반환합니다.
//ldingMethod : 문자열의 각 문자의 ASCII 값을 더한 후,
// 그 값을 4자리씩 나누어 각 부분을 더하고, 
// 해시 테이블의 크기로 나눈 나머지를 반환합니다.