import sys
from test_msg import debug,info,warning,error
try:
    import pyrange
except ImportError:
    error('pyrange module not available')
    sys.exit(1)

#
# Run unit tests first. Failure = exit
#
from test_func import test_overlap
if not test_overlap(): sys.exit(1)





