#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sym_table_lab.h" //소스파일은 추가 안하고 헤더파일만 추가하면 된다
#include "hash_func.h" // 소스파일은 알아서 compiler가 처리
#include "tn.h"


//sym_table_lab.h, hash_func.h, tn.h 헤더 파일에서 정의된 함수와 구조체를 사용
//심볼 테이블의 초기화, 해시 테이블에서의 심볼 검색, 
// 해시 테이블에 심볼 추가, 그리고 심볼 테이블과 해시 테이블의 출력 기능

char separators[] = " ,;\t\n\r\n"; // 토큰의 구분자 목록들
char str_pool[MAX_STR_POOL]; // 심볼테이블에 저장된 문자열을 저장하는 배열
// sym_table 구조
// StringPoolIndex | Length | Line
int sym_table[SYM_TABLE_SIZE][3]; // 심볼테이블을 나타내는 2차원 배열
// 각 행은 하나의 심볼을 나타내고, 3개의 열은 각각 문자열 풀 index,
// 심볼의 길이, 소스코드에서의 등장행 번호를 저장
// [{StringPoolIndex, Length, Line}, {StringPoolIndex, Length, Line}, ...]

#define isLetter(x) ( ((x) >= 'a' && (x) <='z') || ((x) >= 'A' && (x) <= 'Z') || ((x) == '_')) 
#define isDigit(x) ( (x) >= '0' && (x) <= '9' )

// isLetter : 문자 x가 영문자, 밑줄(-) 인지 확인하는 매크로

HTpointer HT[HASH_TABLE_SIZE]; // 해시테이블을 나타내는 배열

void init_sym_table() {
    int i;
    for (i = 0; i < SYM_TABLE_SIZE; i++) {
        sym_table[i][0] = -1;
        sym_table[i][1] = -1;
    }
}// 심볼 테이블을 초기화하면서 각 항목의 문자열 풀 인덱스와 길이를 -1로 설정
// 따라서 빈항목임을 표시

void print_sym_table() {
    int i;
    printf("\nSymbol Table\n");
    printf("Index\tStrPool\tLength\tLine\tSymbol\n");
    for (i = 0; i < SYM_TABLE_SIZE; i++) {
        if (sym_table[i][0] != -1) {
            printf("[%d]\t%d\t%d\t%d\t%s\n", i, sym_table[i][0], sym_table[i][1], sym_table[i][2], str_pool+sym_table[i][0]);
        }
    }
}
//역할: 심볼 테이블의 내용을 출력합니다.
//동작: 모든 심볼 테이블 항목을 순회하며, 
// 유효한 항목(즉, 초기화된 항목)을 출력합니다.



HTpointer lookup_hash_table(char* sym, int hscode) {
    HTpointer entry = HT[hscode];

    while (entry != NULL) {
        if (strcmp(str_pool+(sym_table[entry->index][0]), sym) == 0) {
            return entry; 
        }
        entry = entry->next;
    }
    return NULL;
}
//역할: 해시 테이블에서 특정 심볼을 검색합니다.
//동작: 주어진 해시 코드(hscode)에 해당하는 체이닝 리스트를 순회하여, 
// 심볼이 존재하는지 확인합니다.존재하면 해당 항목의 포인터를 반환하고, 
// 존재하지 않으면 NULL을 반환합니다.

void add_hash_table(int id_index, int hscode) {
    // �� �׸� ���� �� �ʱ�ȭ
    HTpointer newEntry = (HTpointer)malloc(sizeof(HTentry));
    if (newEntry == NULL) {
        printf("�޸� �Ҵ� ����\n");
        exit(1);
    }
    newEntry->index = id_index;
    newEntry->next = NULL;

    if (HT[hscode] == NULL) {
        // ù ��° �׸����� �߰�
        HT[hscode] = newEntry;
    }
    else {
        // �̹� �׸��� ������, ����Ʈ�� �� �տ� �߰�
        newEntry->next = HT[hscode];
        HT[hscode] = newEntry;
    }
}

void print_hash_table() {
    printf("\nHash Table:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HTpointer entry = HT[i];
        if (entry != NULL) {
            printf("[%d]: ", i);
            while (entry != NULL) {
                printf("%d -> ", entry->index);
                entry = entry->next;
            }
            printf("NULL\n");
        }
    }
}

int sym_table_index = 0;
int str_pool_index = 0;
void SymbolTable(char* ident, int len) {
    int hash_value = 0;

    if (str_pool_index + len > MAX_STR_POOL) {
        //�ؽ� ���
        //�ߺ��� �ĺ��� ������ ��� ��� ����
        //�ߺ��� �ĺ��ڰ� �������� ���� ���� �����÷ο� ���� �߻���Ű�� ����
        hash_value = divisionMethod(ident, HASH_TABLE_SIZE);

        HTpointer htp = lookup_hash_table(ident, hash_value);
        if (htp == NULL) {
            ReportError(overst);
            printf("String pool overflow\n");
            print_sym_table();
            print_hash_table();
            exit(0);
        }
        return;
    }

    hash_value = divisionMethod(ident, HASH_TABLE_SIZE);
    
    HTpointer htp = lookup_hash_table(ident, hash_value);
    if (htp == NULL) {
        if (sym_table_index == SYM_TABLE_SIZE) {
            ReportError(overst);
            printf("Symbol Table overflow\n");
            print_sym_table();
            print_hash_table();
            exit(0);
        }

        strcpy_s(str_pool + str_pool_index, MAX_STR_POOL, ident);

        add_hash_table(sym_table_index, hash_value);

        sym_table[sym_table_index][0] = str_pool_index;
        sym_table[sym_table_index][1] = len;
        sym_table[sym_table_index++][2] = lineNumber;

        str_pool[str_pool_index + len] = '\0';
        str_pool_index += len+1;
    }
}
