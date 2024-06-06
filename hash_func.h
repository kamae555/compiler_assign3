#pragma once
//지시문은 헤더 파일이 여러 번 포함되는 것을 방지하는 기능
//헤더 파일 보호 매크로 (#ifndef, #define, #endif)의 대안입니다.

int divisionMethod(char* key, int tableSize);
//나눗셈 방법(division method)은 키를 해시 테이블의 크기로 
//나눈 나머지를 사용하여 해시 값을 생성
int midsquareMethod(char* key, int tableSize);
//이 방법은 키를 정수로 변환하고, 그 정수를 제곱한 후, 
// 중간 부분의 몇 자리를 해시 값으로 사용합니다. 예를 들어, key의 정수 값이 123이면,
//  이를 제곱하여 15129가 되고, 중간 부분인 512를 해시 값으로 사용할 수 있습니다.
int foldingMethod(char* key, int tableSize);
//이 방법은 키를 여러 부분으로 나누고, 각 부분을 더하여 해시 값을 만듭니다. 
// 예를 들어, key가 "example_key"이면, 
// 이를 몇 부분으로 나누고, 각 부분의 값을 더하여 해시 값을 생성합니다.