from ROOT import std,opana,TH1D,TCanvas
import sys
algo = opana.PedEstimator()

wf=std.vector("unsigned short")()
start = False
for x in xrange(10):

    wf.push_back(x%3)
c=TCanvas("c","",600,500)
h=TH1D("wf","",wf.size(),-0.5,wf.size()-0.5)
for x in xrange(wf.size()):
    h.SetBinContent(x+1,wf[x])
res = algo.Calculate(wf,start,5,.5)
print res.first,res.second

h.Draw()
c.Update()
sys.stdin.readline()
