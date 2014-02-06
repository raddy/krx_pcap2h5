import sys,os
import pandas as pd

def main(file_name,start_time,end_time,symbol):
    print 'Parsing %s ....' %file_name
    store = pd.HDFStore(file_name)
    md = store.select('pcap_data',[pd.Term('index','>=',start_time),pd.Term('index','<=',end_time)])
    store.close()
    md.index = pd.to_datetime(md.index)
    print_columns = ['symbol','bid1','bidsize1','ask1','asksize1','tradeprice','tradesize']
    #pd.set_option('display.height', 500)
    pd.set_option('display.max_rows', 500)
    print md[md.symbol==symbol].ix[:,print_columns].head(500)
if __name__ == "__main__":
    if len(sys.argv) != 5:
        sys.exit('Usage: %s h5_name start_time end_time symbol' % sys.argv[0])

    if not os.path.exists(sys.argv[1]):
        sys.exit('ERROR: H5 file %s was not found!' % sys.argv[1])
    start_time_as_long = pd.Timestamp(sys.argv[2]).value
    end_time_as_long = pd.Timestamp(sys.argv[3]).value
    symbol = sys.argv[4]
    sys.exit(main(sys.argv[1],start_time_as_long,end_time_as_long,symbol))