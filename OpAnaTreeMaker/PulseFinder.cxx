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
    
    auto ped_rms = _algo.Calculate(wf);

    // short ch; //channel
    // short tstart;
    // short tend;
    // short tmax;
    // float ped_mean;
    // float amp;
    // float area;
    
    //check if there is even a pulse there...
    Double_t peak_discrim = 2.0;
    
    // while(1) {
    //   if(wf[find_peak(wf)] > ped_rms.first + peak_discrim * ped_rms.second) {
    // 	opana::Pulse_t a();
    // 	a.tmax = find_peak;
    // 	a.amp  = wf[find_peak];
    //   }
    // }
    
     // if(!result.size())
     //  return result;
     
    
    Double_t rise_edge  = 3.0;
    Double_t fall_edge = 3.0;
    
    
    //for(size_t t = 0: t < wf.size(); ++t) {
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
	  if(wf[t_end] <= (ped_rms.first + fall_edge * ped_rms.second))
	    break;
	  else 
	    ++t_end;
	}
	if(t_end == wf.size() - 1) t_end++;
	a.tend = t_end;
	a.tmax = find_peak(wf, t, t_end);	
	a.amp  = wf[a.tmax];
	for(t ; t < t_end; ++t) //secretly increases t...
	  a.area += wf[t];
	
	a.ch = wf.channel_number();
	result.push_back(a);
      }
      
      ++t;
      found_pulse = false;
    }
    
    return result;
  }

}
#endif
