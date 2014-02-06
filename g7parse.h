#ifndef _G7PARSE_H_
#define	_G7PARSE_H_

#include "quickutil.h"

//copy pasting is bad for you

static void commodity_g7(const char * const s,top2 &top_md){
	top_md.bid1 =  atoul_8(s+sizeof(char)*142);
	top_md.bidsize1 = atoul_6(s+sizeof(char)*150);
	top_md.ask1 = atoul_8(s+sizeof(char)*223);
	top_md.asksize1 = atoul_6(s+sizeof(char)*231);
	top_md.bid2 =  atoul_8(s+sizeof(char)*157);
	top_md.bidsize2 = atoul_6(s+sizeof(char)*165);
	top_md.ask2 = atoul_8(s+sizeof(char)*238);
	top_md.asksize2 = atoul_6(s+sizeof(char)*246);
	top_md.total_bids = atoul_6(s+sizeof(char)*135);
	top_md.total_asks = atoul_6(s+sizeof(char)*216);
	top_md.tradeprice = atoul_8(s+sizeof(char)*21);
	top_md.tradesize = atoul_6(s+sizeof(char)*29);
	top_md.total_volume = atoul_7(s+sizeof(char)*97);
	top_md.exchange_time = atoul_8(s+sizeof(char)*37);
}

static void future_g7(const char * const s,top2 &top_md){
	top_md.bid1 =  atoul_5(s+sizeof(char)*103);
	top_md.bidsize1 = atoul_6(s+sizeof(char)*108);
	top_md.ask1 = atoul_5(s+sizeof(char)*169);
	top_md.asksize1 = atoul_6(s+sizeof(char)*174);
	top_md.bid2 =  atoul_5(s+sizeof(char)*115);
	top_md.bidsize2 = atoul_6(s+sizeof(char)*120);
	top_md.ask2 = atoul_5(s+sizeof(char)*181);
	top_md.asksize2 = atoul_6(s+sizeof(char)*186);
	top_md.total_bids = atoul_6(s+sizeof(char)*96);
	top_md.total_asks = atoul_6(s+sizeof(char)*162);
	top_md.tradeprice = atoul_5(s+sizeof(char)*20);
	top_md.tradesize = atoul_6(s+sizeof(char)*25);
	top_md.total_volume = atoul_7(s+sizeof(char)*75);
	top_md.exchange_time = atoul_8(s+sizeof(char)*33);
}

static void option_g7(const char * const s,top2 &top_md){
	top_md.bid1 =  atoul_5(s+sizeof(char)*90);
	top_md.bidsize1 = atoul_7(s+sizeof(char)*95);
	top_md.ask1 = atoul_5(s+sizeof(char)*157);
	top_md.asksize1 = atoul_7(s+sizeof(char)*162);
	top_md.bid2 =  atoul_5(s+sizeof(char)*102);
	top_md.bidsize2 = atoul_7(s+sizeof(char)*107);
	top_md.ask2 = atoul_5(s+sizeof(char)*169);
	top_md.asksize2 = atoul_7(s+sizeof(char)*174);
	top_md.total_bids = atoul_7(s+sizeof(char)*83);
	top_md.total_asks = atoul_7(s+sizeof(char)*150);
	top_md.tradeprice = atoul_5(s+sizeof(char)*20);
	top_md.tradesize = atoul_7(s+sizeof(char)*25);
	top_md.total_volume = atoul_8(s+sizeof(char)*62);
	top_md.exchange_time = atoul_8(s+sizeof(char)*34);
}


#endif