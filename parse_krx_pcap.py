import sys,os
from krx_pcap2h5 import open_pcap
import pandas as pd
import numpy as np
import time

def main(file_name,start_time,end_time):
    print 'Parsing %s ....' %file_name
    
    h5_filename = pd.Timestamp(start_time).isoformat('T')+'_'+pd.Timestamp(end_time).isoformat('T')+'.h5'
    store = pd.HDFStore(h5_filename,'w') 
    open_pcap(file_name,store,start_time,end_time,1)
    print store
    store.close()

def rtmain(file_name,start_time,end_time):
    print 'Parsing %s ....' %file_name
    
    h5_filename = pd.Timestamp(start_time).isoformat('T')+'_'+pd.Timestamp(end_time).isoformat('T')+'.h5'
    store = pd.HDFStore(h5_filename,'w') 
    
    last_time = start_time
    stop_time = end_time
    one_minute = (1000000000*60)
    t= start_time

    while last_time<stop_time:
    	last_time = open_pcap(file_name,store,t,t+one_minute,1)
    	t += one_minute
		time.sleep(60)
    print store
    store.close()

if __name__ == "__main__":
    if len(sys.argv) != 5:
        sys.exit('Usage: %s pcap-path start_time<YYYYMMDDThhmmss.uuuuuu> end_time<YYYYMMDDThhmmss.uuuuuu> real-time-flag(0/1)' % sys.argv[0])

    if not os.path.exists(sys.argv[1]):
        sys.exit('ERROR: Raw Pcap file %s was not found!' % sys.argv[1])
    start_time_as_long = pd.Timestamp(sys.argv[2]).value
    end_time_as_long = pd.Timestamp(sys.argv[3]).value
    if sys.argv[4] == '0': #not real time
    	sys.exit(main(sys.argv[1],start_time_as_long,end_time_as_long))
    if sys.argv[4] == '1': #real time!
    	sys.exit(rtmain(sys.argv[1],start_time_as_long,end_time_as_long))