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

  void PulseFinder::Configure(float rise_edge, float fall_edge, float threshold)
  {
    _rise_edge = rise_edge;
    _fall_edge = fall_edge;
    _threshold = threshold;
  }

  
  const std::vector< opana::Pulse_t> PulseFinder::Reconstruct(const ::larlite::fifo& wf) const
  {
    std::vector< opana::Pulse_t> result;
    
    auto ped_info = _algo.Calculate(wf,1);
    
    bool found_pulse = false; 
    size_t t = 0;
    
    while (  t < wf.size() ) {
      if(wf[t] > (ped_info.first  + _rise_edge * ped_info.second)  && 
	 wf[t] > _threshold + ped_info.first &&
	 !found_pulse)
	found_pulse = true;
      
      if(found_pulse) {
	opana::Pulse_t a;
	a.tstart = t;
	a.area = 0.0;
	size_t t_end = t;

	while(1) {
	  if(t_end == wf.size() - 1)
	    break;
	  
	  if( wf[t_end] <= (ped_info.first + _fall_edge * ped_info.second) &&
	      (wf[t_end] <= _threshold + ped_info.first))
	    break;
	  else 
	    ++t_end;
	}
	
	a.tend = t_end;
	a.tmax = find_peak(wf, t, t_end);	
	a.amp  = wf[a.tmax] - ped_info.first;
	
	while(t < t_end) { //secretly increases t...
	  if(wf[t] >= ped_info.first) a.area += wf[t] - ped_info.first;
	  ++t;
	}
	
	a.ch = wf.channel_number();
	a.ped_mean = ped_info.first; 
	result.push_back(a);
      }
      
      ++t;
      found_pulse = false;
    }
    
    return result;
  }
  
}
#endif
