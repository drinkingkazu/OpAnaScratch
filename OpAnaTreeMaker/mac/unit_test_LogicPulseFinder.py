from ROOT import larlite as fmwk
from ROOT import opana
from ROOT import TH1D,TCanvas
import sys

logic_pf = opana.LogicPulseFinder()
logic_pf.Configure()

wf1=fmwk.fifo()
wf1.set_channel_number(41)

wf2=fmwk.fifo()
wf2.set_channel_number(42)

wf3=fmwk.fifo()
wf3.set_channel_number(41)

for i in xrange(2000):
    if i >= 50 and i <= 100:
        wf1.push_back(200 + 2048)
        wf3.push_back(2048)
        continue

    if i >= 125 and i <= 135:
        wf1.push_back(2048)
        wf3.push_back(300 + 2048)
        continue
    
    if i >= 250 and i <= 375:
        wf1.push_back(200 + 2048)
        wf3.push_back(2048)
        continue

    if i >= 855 and i <= 994:
        wf1.push_back(2048)
        wf3.push_back(300 + 2048)
        continue
        
    wf1.push_back(2048)
    wf3.push_back(2048)
        
evfifo=fmwk.event_fifo()
evfifo.push_back(wf1)
evfifo.push_back(wf2)
evfifo.push_back(wf3)

aho = logic_pf.GetPulses(evfifo)


c  = TCanvas("c","",600,500)

h1 = TH1D("h1","",wf1.size(),0,wf1.size()-1)
h2 = TH1D("h2","",wf3.size(),0,wf3.size()-1)

for x in xrange(wf1.size()):
    h1.SetBinContent(x+1,wf1[x])

for x in xrange(wf3.size()):
    h2.SetBinContent(x+1,wf3[x])


h2.Draw()
h1.SetLineColor(2)
h1.Draw("SAMES")
c.Update()
