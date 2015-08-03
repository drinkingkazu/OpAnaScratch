import sys

if len(sys.argv) < 2:
    msg  = '\n'
    msg += "Usage 1: %s $INPUT_ROOT_FILE(s)\n" % sys.argv[0]
    msg += '\n'
    sys.stderr.write(msg)
    sys.exit(1)

from larlite import larlite as fmwk
from ROOT import opana
import ROOT

my_proc = fmwk.ana_processor()

for x in xrange(len(sys.argv)-1):
    my_proc.add_input_file(sys.argv[x+1])

my_proc.set_io_mode(fmwk.storage_manager.kREAD)

my_proc.set_ana_output_file("out.root");

ana = fmwk.RawFlasherAna()
ana.StoreWaveform(True)

logicpulse_algo    = opana.LogicPulseFinder()
logicpulse_algo.Configure(2048,50,38)
logicpulse_algo.Algo().Configure(10,0.5)

unbiasedpulse_algo = opana.UnbiasedPulse()
chans = ROOT.vector('UInt_t')()
fems  = ROOT.vector('UInt_t')()
# for i in xrange(0,36):
#     chans.push_back(i)


#only channel that is on in 003.root
chans.push_back(7)
fems.push_back (5)

unbiasedpulse_algo.Configure(chans,fems,30,25,5,5)
unbiasedpulse_algo.Algo().Configure(10,0.5)

print "penis1"
#ana.SetAlgo(preco_algo)
ana.SetUnbiasedPulse   (unbiasedpulse_algo)
ana.SetLogicPulseFinder(logicpulse_algo   )
print "penis2"
my_proc.add_process(ana)

print
print  "Finished configuring ana_processor. Start event loop!"
print

# Let's run it.
my_proc.run();

# done!
print
print "Finished running ana_processor event loop!"
print

sys.exit(0)


# void Configure(std::vector<UInt_t> channels,
#     	   UInt_t delay        = 0,
#     	   //UInt_t baseline_num = 5,
#     	   UInt_t window_size  = 25,
#     	   UInt_t left_offset  = 0,
#     	   UInt_t right_offset = 0,
#     	   Int_t  tstart       = 10,
#     	   Int_t  tend         = 20,
#     	   bool   edge_flag    = false);
