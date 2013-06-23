import numpy as np
import pandas as pd
import sys
cimport cython
cimport numpy as np
from libc.stdlib cimport malloc, free
from libc.string cimport strlen

ctypedef np.double_t DTYPE_t

cdef extern from "stdint.h" nogil:
    ctypedef   signed long  int64_t #pytables doesn't like unsigned ints apparently
    ctypedef unsigned short uint16_t
    
cdef extern from * nogil:
    ctypedef char const_char "const char"
    ctypedef void const_void "const void"
    
cdef extern from "string.h" nogil:
    void *memcpy  (void *TO, const_void *FROM, size_t SIZE)

cdef extern from "time.h" nogil:
    ctypedef long time_t
    ctypedef long suseconds_t
    struct timeval:
        time_t tv_sec
        suseconds_t  tv_usec
    
cdef extern from "pcap.h" nogil:
    struct pcap_pkthdr:
        timeval ts
    ctypedef struct pcap_t:
        int __xxx
    pcap_t *pcap_open_offline(const char *, char *)
    unsigned char *pcap_next(pcap_t *p, pcap_pkthdr *hdr)
    void pcap_close(pcap_t *)

cdef extern from "netinet/in.h" nogil:
    ctypedef unsigned int in_addr_t    
    ctypedef struct in_addr:
        in_addr_t s_addr
    
cdef extern from "netinet/ip.h" nogil:
    struct ip:
        unsigned short ip_len
        unsigned char ip_p
        unsigned int ip_hl #not sure how to use this...
        in_addr ip_src,ip_dst
        
cdef extern from "arpa/inet.h" nogil:
    int ntohs (int)
    char* inet_ntoa(in_addr)

cdef extern from "netinet/udp.h" nogil:
    struct udphdr:
        unsigned short uh_sport
        unsigned short uh_dport

cdef extern from "quickbbo.h" nogil:
    struct bbo:
        int64_t bid1
        int64_t bidsize1
        int64_t ask1
        int64_t asksize1
        int64_t tradeprice
        int64_t tradesize
        int64_t total_volume
        int64_t exchange_time
        char symbol[13]
        char msg_type[3]
        
    int parse_msg(const_char *s,bbo &result)  

cdef packed struct bbo_packed:
        char symbol[13]
        int64_t bid1
        int64_t bidsize1
        int64_t ask1
        int64_t asksize1
        char msg_type[3]
        int64_t tradeprice
        int64_t tradesize
        int64_t total_volume
        int64_t packet_time
        int64_t exchange_time
        int64_t source_port
        char source_ip[16]
        int64_t dest_port
        char dest_ip[16] 
    
#let's just ignore non-udp for now
@cython.cdivision(True)
@cython.boundscheck(False)
def open_pcap(some_pcap):
    cdef:
        char __ebuf[256]
        char *p = some_pcap
        pcap_t *handle = pcap_open_offline(p,__ebuf)
        pcap_pkthdr header
        const unsigned char *packet
        unsigned char* pkt_ptr
        ip *ip_hdr
        udphdr *udpHdr
        char *data
        char *s
        int data_len, ip_hdr_len, ether_type, ether_offset, pkt_counter=0,packet_length,flag
        DEF MAX_SIZE  = 500000
        long KST_TZ_OFFSET = 9 * 60 * 60 * 1000 * 1000 * 1000
        
        np.ndarray packet_info = np.ndarray((MAX_SIZE,),
            dtype=[('symbol','a13'),('bid1','i8'),('bidsize1','i8'),('ask1','i8'),('asksize1','i8'),('msg_type','a3'),
                   ('tradeprice','i8'),('tradesize','i8'),('total_volume','i8'),('packet_time','i8'),('exchange_time','i8'),
                   ('source_port','i8'),('source_ip','a16'), ('dest_port','i8'),('dest_ip','a16')])
        bbo_packed [:] packet_view = packet_info
        bbo packet_interals
        expiration_dict = dict()
    #set up hdfstore
    h5_filename = some_pcap.split('/')[-1]+'.h5'
    store = pd.HDFStore(h5_filename,'w') #delete old pcap if it already existed
    
    
    while 1:
        packet = pcap_next(handle,&header)
        if packet is NULL:
            break
        pkt_ptr = <unsigned char *> packet
        ether_type = (<int>(pkt_ptr[12]) << 8) | <int>(pkt_ptr[13])
        if ether_type == 0x0800: #ether type == 2048
            ether_offset = 14 #14 bytes
        pkt_ptr+=ether_offset
        ip_hdr = <ip *>pkt_ptr
        packet_length = ntohs(ip_hdr.ip_len)
        if ip_hdr.ip_p == 17: #UDP == 17 bro
            ip_hdr_len = ip_hdr.ip_hl*4 #is this always 20 bytes since we're v4?
            udpHdr = (<udphdr *> (<char *>ip_hdr + ip_hdr_len))
            data = ((<char *> udpHdr) + sizeof(udphdr))
            data_len = (packet_length - sizeof(udphdr) - ip_hdr_len)
            data[data_len] = 0
            flag = parse_msg(data,packet_interals)
            if flag==1: #found an a3/b6/g7/b2
                # *** General Packet Info *** 
                packet_view[pkt_counter].packet_time = header.ts.tv_sec * 1000000000 +header.ts.tv_usec*1000 + KST_TZ_OFFSET
                packet_view[pkt_counter].source_port = udpHdr.uh_sport
                packet_view[pkt_counter].dest_port = udpHdr.uh_dport
                #copy ip info in (clunky)
                s = inet_ntoa(ip_hdr.ip_src)
                memcpy(packet_view[pkt_counter].source_ip,s,strlen(s))
                packet_view[pkt_counter].source_ip[strlen(s)] = 0
                s = inet_ntoa(ip_hdr.ip_dst)
                memcpy(packet_view[pkt_counter].dest_ip,s,strlen(s))
                packet_view[pkt_counter].dest_ip[strlen(s)] = 0
                #end of ip info
                # *** End of General Packet Info
                memcpy(packet_view[pkt_counter].symbol,packet_interals.symbol,sizeof(char)*12) #does this need to be null termed? hmnn..
                memcpy(packet_view[pkt_counter].msg_type,packet_interals.msg_type,sizeof(char)*2) #does this need to be null termed? hmnn..
                packet_view[pkt_counter].bid1 = packet_interals.bid1
                packet_view[pkt_counter].bidsize1 = packet_interals.bidsize1
                packet_view[pkt_counter].ask1 = packet_interals.ask1
                packet_view[pkt_counter].asksize1 = packet_interals.asksize1
                packet_view[pkt_counter].tradeprice = packet_interals.tradeprice
                packet_view[pkt_counter].tradesize = packet_interals.tradesize
                packet_view[pkt_counter].total_volume = packet_interals.total_volume
                packet_view[pkt_counter].exchange_time = packet_interals.exchange_time
                pkt_counter+=1
            elif flag==2: #found an a0
                python_code = packet_interals.symbol
                exp_code = python_code[6:8]
                expiration_dict[exp_code] = str(packet_interals.exchange_time)
        if pkt_counter == MAX_SIZE:
            df = pd.DataFrame(packet_info)
            df.index = df.packet_time.values
            del df['packet_time']
            store.append('pcap_data',df,data_columns=['symbol'])
            pkt_counter = 0
    df = pd.DataFrame(packet_info[:pkt_counter])
    df.index = df.packet_time.values
    del df['packet_time']
    store.append('pcap_data',df,data_columns=['symbol'])
    store.append('expiry_info',pd.DataFrame(expiration_dict.values(),index=expiration_dict.keys()))
    pcap_close(handle)
    store.close()