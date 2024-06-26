#include "tn.h"
// tn.h를 포함하여 오류 타입과 외부 변수를 선언한 상태
// lex에서 발생한 오류를 처리하기 위한 함수를 정의한다.
// 이제 함수를 정의해보자

#define MAX_ERROR_MSG	100
char error_message[MAX_ERROR_MSG]; 
//에러 메세지를 담는 변수 (메인에서 error_message를 출력한다.)

void ReportError(ERRORtypes err) 
// tn_h에서 정의한 ERRORtypes 열거형 타입의 인자를 받는 함수
// 이 함수는 ERRORtypes 열거형 타입의 인자를 받아서, 
// 적절한 오류 메시지를 error_message에 저장
{
	switch (err) {
	case overst:
		strcpy_s(error_message, MAX_ERROR_MSG, "overflow");
		// errno_t strcpy_s(char *dest, rsize_t destsz, const char *src);
		// dest : 복사할 문자열을 저장할 버퍼
		// destsz : 버퍼의 크기
		// src : 복사할 문자열
		// 성공시 0을 반환하고, 실패시 오류 코드 반환

		break;
	case illid_long:
		strcpy_s(error_message, MAX_ERROR_MSG, "too long identifier");
		break;
	case illch:
		sprintf_s(error_message, MAX_ERROR_MSG, "%s illegal character", yytext);
		//허용되지 않은 문자가 들어올 경우 에러 발생
		break;
	case illid_digit:
		sprintf_s(error_message, MAX_ERROR_MSG, "%s start with digit", yytext);
		break;
	case real_num:
		strcpy_s(error_message, MAX_ERROR_MSG, "real number is not allowed");
		//실수가 들어올 경우 에러 발생. Floating Point 경우는 제외하였음.
	}
}
// error_message라는 배열에 overflow, too long identifier, 
// illegal character, start with digit, real number is not allowed를 저장한다.


// 함수 선언은 tn.h에 정의되어 있으므로, 함수 정의만 하면 된다.
// 함수를 정의하였으므로, 이제 main.c에서 함수를 호출하여 사용할 수 있다.