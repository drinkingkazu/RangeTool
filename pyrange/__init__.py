import sys
root_available = True
lib_available  = True 
try:
    import ROOT
    ROOT.gErrorIgnoreLevel = 4000
    lib_available = not ROOT.gSystem.Load("libRangeTool")
    ROOT.gErrorIgnoreLevel = ROOT.kInfo
except ImportError:
    root_available = False

if not root_available:
    print ' Failed to import ROOT (PyROOT not available)'
    sys.exit(1)
elif not lib_available:
    print ' Failed to import libRangeTool.so (Range package lib not available)'
    sys.exit(1)

from ROOT import util
# Import class
#from ROOT.util import Range, UniqueRangeSet
Range = util.Range
UniqueRangeSet = util.UniqueRangeSet
# Import functions
#from ROOT.util import bmark_range_insert, bmark_range_exclude
bmark_insert = util.range.bmark_insert
bmark_exclude = util.range.bmark_exclude
    

