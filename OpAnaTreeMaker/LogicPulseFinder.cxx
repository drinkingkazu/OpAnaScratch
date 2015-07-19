#ifndef LOGICPULSEFINDER_CXX
#define LOGICPULSEFINDER_CXX

#include "LogicPulseFinder.h"

namespace opana {

  void LogicPulseFinder::Configure(float baseline, 
				   float height,
				   UInt_t channel_num)
  {
    _baseline    = baseline;
    _height      = height;
    _channel_num = channel_num;
  }


  std::vector<Pulse_t> LogicPulseFinder::GetPulses(const ::larlite::event_fifo& evfifo) {
    
    std::vector<Pulse_t> flasher_list;
    
    bool found_ttl = false;
    auto t = short{0};
    
    for(const auto& wf : evfifo) {
      if(wf.channel_number() != _channel_num) continue;
      t = 0;
      while( t < wf.size() ) {
	if( wf[t] > _baseline + _height && !found_ttl)
	  found_ttl = true;
	
	if(found_ttl) {
	  opana::Pulse_t ttl;
	  ttl.tstart = t;
	  auto t_end = t;
	  
	  while(1) {
	    if(t_end == wf.size() - 1) break;
	    if( wf[t_end] < (_baseline + _height))  {
	      t_end--;
	      break;
	    }
	    
	    ++t_end;
	  }
	  
	  ttl.tend  = t_end;
	  ttl.amp   = wf[ttl.tstart + (size_t)((ttl.tend - ttl.tend)/2.0)] - _baseline;
	  ttl.ch    = wf.channel_number();
	  ttl.width = ttl.tend - ttl.tstart;
	  flasher_list.push_back(ttl);
	  t = t_end + 1;
	}
	
	++t;
	found_ttl = false;
      }
    }
    
    
    return flasher_list;
    
  }
}
#endif
