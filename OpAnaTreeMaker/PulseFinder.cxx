#ifndef PULSEFINDER_CXX
#define PULSEFINDER_CXX

#include "PulseFinder.h"

namespace opana {
  
  size_t PulseFinder::find_peak(const::larlite::fifo& data, const size_t istart, const size_t iend) const
  {
    auto the_max = double{0.0};
    size_t cl = 4096;
    
    for(size_t i = istart; i < iend; ++i) {
      if(data[i] > the_max) { the_max = data[i]; cl = i; }
    }
    
    return cl;
  }
  
  const std::vector< opana::Pulse_t> PulseFinder::Reconstruct(const ::larlite::fifo& wf) const
  {
    std::vector< opana::Pulse_t> result;
    
    auto ped_rms = _algo.Calculate(wf,1);
    
    Double_t rise_edge  = 3.0;
    Double_t fall_edge  = 3.0;
    
    bool found_pulse = false; 
    size_t t = 0;
    
    while (  t < wf.size() ) {
      if(wf[t] > (ped_rms.first  + rise_edge * ped_rms.second) && !found_pulse)
	found_pulse = true;
      
      if(found_pulse) {
	opana::Pulse_t a;
	a.tstart = t;
	a.area = 0.0;
	size_t t_end = t;

	while(1) {
	  if(t_end == wf.size() - 1)
	    break;
	  
	  if(wf[t_end] <= (ped_rms.first + fall_edge * ped_rms.second))
	    break;
	  else 
	    ++t_end;
	}
	
	a.tend = t_end;
	a.tmax = find_peak(wf, t, t_end);	
	a.amp  = wf[a.tmax];
	
	while(t < t_end) { //secretly increases t...
	  a.area += wf[t];
	  ++t;
	}
	
	a.ch = wf.channel_number();
	a.ped_mean = ped_rms.first; 
	result.push_back(a);
      }
      
      ++t;
      found_pulse = false;
    }
    
    return result;
  }
  
}
#endif
