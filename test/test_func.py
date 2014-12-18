import pyrange, time
from test_msg import debug,info,warning,error

def test_overlap():
    info('UnitTest: testing Range::Merge and UniqueRangeSet::Exclusive')
    res = pyrange.test_overlap()
    if res:
        error('UnitTest: Failed! util::range::test_overlap return %s' % res)
        return False
    info('UnitTest: SUCCESS')
    return True

def benchmark_insert(n=1000000):
    if not type(n) == type(int()) or n < 0: 
        error('%s expect positive integer input arg...')
        return False

    info('Benchmark: UniqueRangeSet::Insert for %d times ' % n)
    t_start = time.time()
    res = pyrange.bmark_insert(n)
    t_end = time.time()
    if res < 0:
        error('Benchmark: Failed! Aborting...')
        return False
    info('Benchmark: SUCCESS ... time %s (average %s/insert)' % (res, res/n))
    return True

def benchmark_exclude(n=1000000):
    if not type(n) == type(int()) or n < 0: 
        error('%s expect positive integer input arg...')
        return False
    
    info('Benchmark: Range::Exclude with %d entries of UniqueRangeSet' % n)
    t_start = time.time()
    res = pyrange.bmark_exclude(n)
    t_end = time.time()
    if res < 0:
        error('Benchmark: Failed! Aborting...')
        return False
    info('Benchmark: SUCCESS ... time %s ' % res)
    return True
