import sys
from test_msg import debug,info,warning,error
try:
    import pyrange
except ImportError:
    error('pyrange module not available')
    sys.exit(1)

from test_func import *

benchmark()

