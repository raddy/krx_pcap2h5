#ifndef _QUICKBBO_H_
#define	_QUICKBBO_H_

#include <string.h>
#include "b6parse.h"
#include "g7parse.h"
#include "a3parse.h"
#include "b2parse.h"

using namespace std;


__BEGIN_DECLS

//Msg Type Codes as ushort
#define B6 13890
#define G7 14151
#define A3 13121
#define B2 12866

//Product Type Codes as ushort
#define FUTURE 12592
#define OPTION 13104



static inline uint16 msg_type(const char *s){
	return ((uint16 *)s)[0];
}

static inline uint16 product_type(const char *s){
	return ((uint16 *)s)[1];
}

static inline void parse_msg_type(const char * const s,bbo &res){
	memcpy(res.msg_type,s,sizeof(char)*2);
	res.msg_type[2] = 0;
}

static inline void parse_issue_code(const char * const s,bbo &res){
	memcpy(res.symbol,s+sizeof(char)*5,sizeof(char)*12);
	res.symbol[12] = 0;
}

static inline int market_type_cash(const char *s){
	return (s[4] != '4');
}


/* Laziest possible code to parse a msg
	* Just parses B6s for now and 

*/
static int parse_msg(const char *s,bbo &result){
	//ignore non derivatives md for now
	if (s[4] != '4')
		return 0;

	parse_msg_type(s,result);

	switch(msg_type(s)){
		case B6:
			parse_issue_code(s,result);
			switch(product_type(s)){
				case FUTURE:
					future_b6(s,result);
					return 1;
				case OPTION:
					option_b6(s,result);
					return 1;
				default:
					return 0;
			}
		case G7:
			parse_issue_code(s,result);
			switch(product_type(s)){
				case FUTURE:
					future_g7(s,result);
					return 1;
				case OPTION:
					option_g7(s,result);
					return 1;
				default:
					return 0;
			}
		case A3:
			parse_issue_code(s,result);
			switch(product_type(s)){
				case FUTURE:
					future_a3(s,result);
					return 1;
				case OPTION:
					option_a3(s,result);
					return 1;
				default:
					return 0;
			}
		case B2:
			parse_issue_code(s,result);
			switch(product_type(s)){
				case FUTURE:
					future_b2(s,result);
					return 1;
				case OPTION:
					option_b2(s,result);
					return 1;
				default:
					return 0;
			}
		default:
			return 0;
	}
}


__END_DECLS

#endif