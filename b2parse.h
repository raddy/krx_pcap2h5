#ifndef _B2PARSE_H_
#define	_B2PARSE_H_

#include "quickutil.h"

//copy pasting is bad for you
static void future_b2(const char * const s,bbo &top_md){
	top_md.bid1 =  atoul_5(s+sizeof(char)*98);
	top_md.bidsize1 = atoul_6(s+sizeof(char)*103);
	top_md.ask1 = atoul_5(s+sizeof(char)*82);
	top_md.asksize1 = atoul_6(s+sizeof(char)*87);
	top_md.tradeprice = atoul_5(s+sizeof(char)*20);
	top_md.tradesize = 0;
	top_md.total_volume = atoul_7(s+sizeof(char)*62);
	top_md.exchange_time = 0;
}

static void option_b2(const char * const s,bbo &top_md){
	top_md.bid1 =  atoul_5(s+sizeof(char)*84);
	top_md.bidsize1 = atoul_7(s+sizeof(char)*89);
	top_md.ask1 = atoul_5(s+sizeof(char)*68);
	top_md.asksize1 = atoul_7(s+sizeof(char)*73);
	top_md.tradeprice = atoul_5(s+sizeof(char)*20);
	top_md.tradesize = 0;
	top_md.total_volume = atoul_8(s+sizeof(char)*49);
	top_md.exchange_time = 0;
}


#endif