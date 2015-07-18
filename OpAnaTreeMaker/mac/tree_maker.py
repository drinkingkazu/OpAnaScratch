import sys

if len(sys.argv) < 2:
    msg  = '\n'
    msg += "Usage 1: %s $INPUT_ROOT_FILE(s)\n" % sys.argv[0]
    msg += '\n'
    sys.stderr.write(msg)
    sys.exit(1)

from larlite import larlite as fmwk
from ROOT import opana
my_proc = fmwk.ana_processor()

for x in xrange(len(sys.argv)-1):
    my_proc.add_input_file(sys.argv[x+1])

my_proc.set_io_mode(fmwk.storage_manager.kREAD)

my_proc.set_ana_output_file("out.root");

ana = fmwk.RawWFAna()
ana.StoreWaveform(True)

preco_algo = opana.PulseFinder()
preco_algo.Configure(5.,5.,3.)

ped_algo = preco_algo.Algo()
ped_algo.Configure(10,0.5)

ana.SetAlgo(preco_algo)

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
