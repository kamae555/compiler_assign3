
#ifndef SYM_TABLE_LAB_H
#define SYM_TABLE_LAB_H

//심볼 테이블과 해시 테이블을 관리하기 위한 구조체와 함수들을 정의하는 헤더 파일
//심볼 테이블과 해시 테이블의 초기화, 출력, 
// 그리고 해시 테이블에서 심볼을 검색하는 함수들을 선언

#pragma once

#define SYM_TABLE_SIZE	100 // 심볼테이블의 크기
#define HASH_TABLE_SIZE 11 // 해시테이블의 크기
#define MAX_STR_POOL	200 // 문자열 풀의 크기

void init_sym_table(); // 심볼테이블 초기화 선언
void print_sym_table(); // 심볼테이블 출력함수 선언
void print_hash_table(); // 해시테이블 출력함수 선언

typedef struct HTentry* HTpointer;//해시테이블의 포인터
typedef struct HTentry {// 해시테이블의 항목을 나타내는 구조체
    int index; // 심볼테이블의 인덱스
    HTpointer next;// 다음 항목을 가리키는 포인터
}HTentry;

HTpointer lookup_hash_table(char* sym, int hscode);
// 해시테이블에서 심볼을 찾는 함수
// 찾으면 해당 항목의 포인터를 반환하고, 찾지 못하면 NULL을 반환한다.

#endif // !SYM_TABLE_LAB_H