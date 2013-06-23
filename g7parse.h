#ifndef _G7PARSE_H_
#define	_G7PARSE_H_

#include "quickutil.h"

//copy pasting is bad for you
static void future_g7(const char * const s,bbo &top_md){
	top_md.bid1 =  atoul_5(s+sizeof(char)*103);
	top_md.bidsize1 = atoul_6(s+sizeof(char)*108);
	top_md.ask1 = atoul_5(s+sizeof(char)*169);
	top_md.asksize1 = atoul_6(s+sizeof(char)*174);
	top_md.tradeprice = atoul_5(s+sizeof(char)*20);
	top_md.tradesize = atoul_6(s+sizeof(char)*25);
	top_md.total_volume = atoul_7(s+sizeof(char)*75);
	top_md.exchange_time = atoul_8(s+sizeof(char)*33);
}

static void option_g7(const char * const s,bbo &top_md){
	top_md.bid1 =  atoul_5(s+sizeof(char)*90);
	top_md.bidsize1 = atoul_7(s+sizeof(char)*95);
	top_md.ask1 = atoul_5(s+sizeof(char)*157);
	top_md.asksize1 = atoul_7(s+sizeof(char)*162);
	top_md.tradeprice = atoul_5(s+sizeof(char)*20);
	top_md.tradesize = atoul_7(s+sizeof(char)*25);
	top_md.total_volume = atoul_8(s+sizeof(char)*62);
	top_md.exchange_time = atoul_8(s+sizeof(char)*34);
}


#endif