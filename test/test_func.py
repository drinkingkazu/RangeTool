import pyrange, time
from test_msg import debug,info,warning,error

def benchmark():
    n = 1000000

    info('Benchmark: UniqueRangeSet::Insert for %d times ' % n)
    t_start = time.time()
    res = pyrange.bmark_range_insert(n)
    t_end = time.time()
    info('Benchmark: time total: %s (average %s/insert)' % (t_end-t_start,float(t_end-t_start)/n))
    if not res:
        error('Benchmark: Failed! Aborting...')
        return False
    info('Benchmark: SUCCESS')

    range_list = pyrange.UniqueRangeSet("double")()
    for x in xrange(n): 
        element = pyrange.Range("double")(4*x, 4*x+3)
        range_list.Insert(element)
    info('Benchmark: Range::Exclude with %d entries of UniqueRangeSet' % range_list.size())
    t_start = time.time()
    res = pyrange.bmark_range_exclude(range_list)
    t_end = time.time()
    info('Benchmark: time total: %s (average %s/insert)' % (t_end-t_start,float(t_end-t_start)/n))
    if not res:
        error('Benchmark: Failed! Aborting...')
        return False
    info('Benchmark: SUCCESS')
