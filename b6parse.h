#ifndef _B6PARSE_H_
#define	_B6PARSE_H_

#include "quickutil.h"

//copy pasting is bad for you
static void future_b6(const char * const s,top2 &top_md){
	top_md.bid1 =  atoul_5(s+sizeof(char)*28);
	top_md.bidsize1 = atoul_6(s+sizeof(char)*33);
	top_md.ask1 = atoul_5(s+sizeof(char)*94);
	top_md.asksize1 = atoul_6(s+sizeof(char)*99);
	top_md.bid2 =  atoul_5(s+sizeof(char)*40);
	top_md.bidsize2 = atoul_6(s+sizeof(char)*45);
	top_md.ask2 = atoul_5(s+sizeof(char)*106);
	top_md.asksize2 = atoul_6(s+sizeof(char)*111);
	top_md.tradeprice = 0;
	top_md.tradesize = 0;
	top_md.total_volume = 0;
	top_md.exchange_time = atoul_8(s+sizeof(char)*203);
}

static void option_b6(const char * const s,top2 &top_md){
	top_md.bid1 =  atoul_5(s+sizeof(char)*29);
	top_md.bidsize1 = atoul_7(s+sizeof(char)*34);
	top_md.ask1 = atoul_5(s+sizeof(char)*96);
	top_md.asksize1 = atoul_7(s+sizeof(char)*101);
	top_md.bid2 =  atoul_5(s+sizeof(char)*41);
	top_md.bidsize2 = atoul_7(s+sizeof(char)*46);
	top_md.ask2 = atoul_5(s+sizeof(char)*108);
	top_md.asksize2 = atoul_7(s+sizeof(char)*113);
	top_md.tradeprice = 0;
	top_md.tradesize = 0;
	top_md.total_volume = 0;
	top_md.exchange_time = atoul_8(s+sizeof(char)*206);
}


#endif