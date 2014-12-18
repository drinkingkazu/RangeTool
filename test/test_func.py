import pyrange, time
from test_msg import debug,info,warning,error

def benchmark():
    n = 1000000

    info('Benchmark: UniqueRangeSet::Insert for %d times ' % n)
    t_start = time.time()
    res = pyrange.bmark_insert(n)
    t_end = time.time()
    if res < 0:
        error('Benchmark: Failed! Aborting...')
        return False
    info('Benchmark: SUCCESS ... time %s (average %s/insert)' % (res, res/n))

    info('Benchmark: Range::Exclude with %d entries of UniqueRangeSet' % n)
    t_start = time.time()
    res = pyrange.bmark_exclude(n)
    t_end = time.time()
    if res < 0:
        error('Benchmark: Failed! Aborting...')
        return False
    info('Benchmark: SUCCESS ... time %s ' % res)
