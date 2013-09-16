#ifndef _A3PARSE_H_
#define	_A3PARSE_H_

#include "quickutil.h"

//copy pasting is bad for you

static void commodity_a3(const char * const s,top2 &top_md){
	top_md.bid1 =  0;
	top_md.bidsize1 = 0;
	top_md.ask1 = 0;
	top_md.asksize1 = 0;
	top_md.bid2 =  0;
	top_md.bidsize2 = 0;
	top_md.ask2 = 0;
	top_md.asksize2 = 0;
	top_md.tradeprice = atoul_8(s+sizeof(char)*21);
	top_md.tradesize = atoul_6(s+sizeof(char)*29);
	top_md.total_volume = atoul_7(s+sizeof(char)*97);
	top_md.exchange_time = atoul_8(s+sizeof(char)*37);
}

static void future_a3(const char * const s,top2 &top_md){
	top_md.bid1 =  0;
	top_md.bidsize1 = 0;
	top_md.ask1 = 0;
	top_md.asksize1 = 0;
	top_md.bid2 =  0;
	top_md.bidsize2 = 0;
	top_md.ask2 = 0;
	top_md.asksize2 = 0;
	top_md.tradeprice = atoul_5(s+sizeof(char)*20);
	top_md.tradesize = atoul_6(s+sizeof(char)*25);
	top_md.total_volume = atoul_7(s+sizeof(char)*75);
	top_md.exchange_time = atoul_8(s+sizeof(char)*33);
}

static void option_a3(const char * const s,top2 &top_md){
	top_md.bid1 =  0;
	top_md.bidsize1 = 0;
	top_md.ask1 = 0;
	top_md.asksize1 = 0;
	top_md.bid2 =  0;
	top_md.bidsize2 = 0;
	top_md.ask2 = 0;
	top_md.asksize2 = 0;
	top_md.tradeprice = atoul_5(s+sizeof(char)*20);
	top_md.tradesize = atoul_7(s+sizeof(char)*25);
	top_md.total_volume = atoul_8(s+sizeof(char)*62);
	top_md.exchange_time = atoul_8(s+sizeof(char)*34);
}


#endif