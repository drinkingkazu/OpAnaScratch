from ROOT import larlite as fmwk
from ROOT import opana
from ROOT import TH1D,TCanvas
import sys
algo = opana.PulseFinder()
wf=fmwk.fifo()

for x in xrange(20):

    wf.push_back(x%10)

cnt = 0
for i in algo.Reconstruct(wf) :
    print "i: " + str(cnt)
    i.dump()
    cnt += 1

c=TCanvas("c","",600,500)
h=TH1D("h","",wf.size(),-0.5,wf.size()-0.5)

for x in xrange(wf.size()):
    h.SetBinContent(x+1,wf[x])

h.Draw()
c.Update()
sys.stdin.readline()
