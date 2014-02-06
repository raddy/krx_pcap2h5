#pragma once


typedef unsigned short uint16;
typedef long long  int64_t;

static inline int64_t atoul_8(const char * const s){
    return (s[0]-'0')*10000000+(s[1]-'0')*1000000+(s[2]-'0')*100000
    		+(s[3]-'0')*10000+(s[4]-'0')*1000+(s[5]-'0')*100+(s[6]-'0')*10
    		+(s[7]-'0');
}

static inline int64_t atoul_7(const char * const s){
    return (s[0]-'0')*1000000+(s[1]-'0')*100000+(s[2]-'0')*10000
    		+(s[3]-'0')*1000+(s[4]-'0')*100+(s[5]-'0')*10+(s[6]-'0');
}

static inline int64_t atoul_6(const char * const s){
    return (s[0]-'0')*100000+(s[1]-'0')*10000+(s[2]-'0')*1000+(s[3]-'0')*100+(s[4]-'0')*10+(s[5]-'0');
}

static inline int64_t atoul_5(const char * const s){
    return (s[0]-'0')*10000+(s[1]-'0')*1000+(s[2]-'0')*100+(s[3]-'0')*10+(s[4]-'0');
}

struct bbo{
	int64_t bid1;
	int64_t bidsize1;
	int64_t ask1;
	int64_t asksize1;
	int64_t tradeprice;
	int64_t tradesize;
	int64_t total_volume;
	int64_t exchange_time;
	char symbol[13];
	char msg_type[3];
};

struct top2{
	int64_t bid1;
	int64_t bidsize1;
	int64_t ask1;
	int64_t asksize1;
	int64_t bid2;
	int64_t bidsize2;
	int64_t ask2;
	int64_t asksize2;
	int64_t total_bids;
	int64_t total_asks;
	int64_t tradeprice;
	int64_t tradesize;
	int64_t total_volume;
	int64_t exchange_time;
	char symbol[13];
	char msg_type[3];
};