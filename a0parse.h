#ifndef _A0PARSE_H_
#define	_A0PARSE_H_

#include "quickutil.h"

//copy pasting is bad for you
static void parse_a0(const char * const s,bbo &top_md){
	top_md.exchange_time = atoul_8(s+sizeof(char)*381);
}

static inline void parse_issue_code_a0(const char * const s,bbo &res){
	memcpy(res.symbol,s+sizeof(char)*18,sizeof(char)*12);
	res.symbol[12] = 0;
}

#endif