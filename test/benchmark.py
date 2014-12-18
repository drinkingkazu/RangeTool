import sys
from test_msg import debug,info,warning,error
try:
    import pyrange
except ImportError:
    error('pyrange module not available')
    sys.exit(1)

#
# Benchmarking. doesn't matter if things fail.
#
from test_func import benchmark_insert
benchmark_insert()

from test_func import benchmark_exclude
benchmark_exclude()




