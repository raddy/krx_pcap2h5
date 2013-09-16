import sys,os
from krx_pcap2h5 import open_pcap
import pandas as pd

def main(file_name,start_time,end_time):
    print 'Parsing %s ....' %file_name
    open_pcap(file_name,start_time,end_time)

if __name__ == "__main__":
    if len(sys.argv) != 4:
        sys.exit('Usage: %s pcap-path start_time<YYYYMMDDThhmmss.uuuuuu> end_time<YYYYMMDDThhmmss.uuuuuu>' % sys.argv[0])

    if not os.path.exists(sys.argv[1]):
        sys.exit('ERROR: Raw Pcap file %s was not found!' % sys.argv[1])
    start_time_as_long = pd.Timestamp(sys.argv[2]).value
    end_time_as_long = pd.Timestamp(sys.argv[3]).value
    sys.exit(main(sys.argv[1],start_time_as_long,end_time_as_long))