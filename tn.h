// tn.h
#ifndef TN_H
#define TN_H
// tn.h는 주로 토큰 타입과 관련된 상수,함수,외부 변수 선언 등을 정의하는 헤더파일
// lexer와 parser에서 공통으로 사용되는 정보를 모아두는 역할

// tn.h 파일의 내용이 scanner.l을포함하고 있기 때문에 
// scanner.l에서 tn.h를 포함시켜야 한다.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define MAX_LEN		12 // 식별자의 최대 길이

enum tokentypes { //어휘 분석기가 인식할 수 있는 토큰의 종류
	TEOF,
	TERROR, TCOMMENT, TNUMBER, TFNUMBER, TIDENT,
	TCONST, TELSE, TIF, TINT, TFLOAT, TRETURN, TVOID, TWHILE,
	TADD, TSUB, TMUL, TDIV, TMOD,
	TASSIGN, TADDASSIGN, TSUBASSIGN, TMULASSIGN, TDIVASSIGN, TMODASSIGN,
	TNOT, TAND, TOR,
	TEQUAL, TNOTEQU, TLESS, TLESSE, TGREAT, TGREATE,
	TINC, TDEC,
	TLPAREN, TRPAREN, TCOMMA, TLBRACE, TRBRACE, TLBRACKET, TRBRACKET, TSEMI
};
enum errorTypes { noerror, illid_digit, illid_long, illch, real_num, overst};
typedef enum errorTypes ERRORtypes;
//어휘분석기에서 발생할 수 있는 다양한 오류 유형
// 오류 없음 , 숫자 포함, 길이 길어, 잘문된 문자, 실수형, overflow

extern int lineNumber;// 현재 처리중인 소스코드의 행 번호
extern int startLineNumber;   // 특정 작업이 시작된 행 번호(특히 주석)
extern char error_message[]; // 에러 메세지를 담는 변수(저장하는 문자열)
// extern keyword : 변수나 함수가 다른 파일에서 정의되었음을 알려주는 키워드
// extern 키워드를 사용하면 다른 파일에 정의된 변수나 함수를 사용할 수 있다.
// extern 키워드를 사용하면 변수나 함수를 선언만 하고 정의는 하지 않는다.
// 변수 공유를 위해 use



//lex 
// lex와 bison 간의 interface를 제공하는 변수와 함수         
extern char* yytext; // 현재 토큰의 문자열(lex가 입력을 읽고 패턴에 맞는 텍스트 저장)
extern int yyleng; // 현재 토큰의 길이(
extern int yylex(); // 다음 토큰을 분석하고 다음 코큰의 타입 반환
// bison에서는 yytext를 사용하여 현재 토큰의 텍스트를 참조하고, 
// yylex를 호출하여 다음 토큰을 얻는다.

//   
extern void SymbolTable(char*, int); // 심볼테이블에 식별자와 정보를 추가
extern void ReportError(ERRORtypes err); // (에러 메세지를 출력) 오류 유형 보고



#endif // TN_H

// example
//토큰 처리 과정
//입력: 123 + abc

//첫 번째 토큰 : 123

//Lex는[0 - 9] + 패턴과 매칭합니다.
//yytext(현재 값)는 "123"을 가리키고, yyleng는 3입니다.
//yylex는 TNUMBER를 반환하고, yylval은 123입니다.
