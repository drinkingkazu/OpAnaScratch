import sys
from ROOT import gSystem
gSystem.Load("libOpAnaScratch_OpAnaTreeMaker")
from ROOT import sample

try:

    print "PyROOT recognized your class %s" % str(sample)

except NameError:

    print "Failed importing OpAnaTreeMaker..."

sys.exit(0)

