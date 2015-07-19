from ROOT import larlite as fmwk
from ROOT import opana
from ROOT import TH1D,TCanvas
import sys
import ROOT

logic_pf = opana.LogicPulseFinder()
logic_pf.Configure()

wf1=fmwk.fifo()
wf1.set_channel_number(41)

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
evfifo.push_back(wf3)

logic_pulses = logic_pf.GetPulses(evfifo)


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



ub = opana.UnbiasedPulse()
chans = ROOT.vector('UInt_t')()
chans.push_back(0)
chans.push_back(24)

wf_0=fmwk.fifo()
wf_0.set_channel_number(0)

wf_24=fmwk.fifo()
wf_24.set_channel_number(24)

wf_25=fmwk.fifo()
wf_25.set_channel_number(25)

for i in xrange(2000):
    if i >= 126 and i <= 134:
        wf_0.push_back((i - 100)*(i - 50) + 2048)
    else:
        wf_0.push_back(2048)

    wf_24.push_back(2048)
    wf_25.push_back(2048)

evfifo2=fmwk.event_fifo()
evfifo2.push_back(wf_0)
evfifo2.push_back(wf_24)
evfifo2.push_back(wf_25)


# void Configure(std::vector<UInt_t> channels,
#     	   UInt_t delay        = 0, 
#     	   UInt_t baseline_num = 5,
#     	   UInt_t window_size  = 25,
#     	   UInt_t left_offset  = 0,
#     	   UInt_t right_offset = 0,
#     	   Int_t  tstart       = 10,
#     	   Int_t  tend         = 20,
#     	   bool   edge_flag    = false);

ub.Configure(chans,6)
ub.Algo().Configure()

lol = ub.Reconstruct(logic_pulses,evfifo2)

#    void Configure(unsigned int window = 10,
#    float cutoff = 0.5 );

c2 = TCanvas()
h3 = TH1D("h3","",wf_0.size(),0,wf_0.size()-1)

for x in xrange(wf_0.size()):
    h3.SetBinContent(x+1,wf_0[x])

h3.Draw()
c2.Update()
