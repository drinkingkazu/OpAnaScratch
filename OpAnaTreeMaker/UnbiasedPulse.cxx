#ifndef UNBIASEDPULSE_CXX
#define UNBIASEDPULSE_CXX

#include "UnbiasedPulse.h"

namespace opana {
  
  void UnbiasedPulse::Configure(std::vector<UInt_t> channels,
				std::vector<UInt_t> fems,
				UInt_t delay,
				UInt_t window_size,
                                UInt_t left_offset,
				UInt_t right_offset,
				Int_t  tstart,
				Int_t  tend,
				bool   edge_flag)
  {
    _delay        = delay;
    _left_offset  = left_offset; 
    _right_offset = right_offset; 
    _tstart       = tstart;
    _tend         = tend;
    //_baseline_num = baseline_num;
    _window_size  = window_size;
    _edge_flag    = edge_flag;
    
    //need to configure with fhicllite!!!!
    _channels = channels;
    _fems     = fems;
    
  }
  
  std::vector<Pulse_t> UnbiasedPulse::Reconstruct(const std::vector<Pulse_t>& flashes,
						  const ::larlite::event_fifo& evfifo)
  {
    std::vector<Pulse_t> pulses;
    
    for(const auto& flash : flashes) {
      for(const auto& wf : evfifo) {
	UInt_t ch_num  = (UInt_t)wf.channel_number();
	UInt_t fem_num = (UInt_t)wf.module_address();
     	if(connected_channel(ch_num) && connected_fem(fem_num)) {
	    pulses.push_back(create_unbiased_pulse(wf,flash.tstart,flash.tend));
	  }
	
      }
    }
  
    return pulses;  
  }
  
  std::vector<Pulse_t> UnbiasedPulse::Reconstruct(const ::larlite::event_fifo& evfifo)
  {
    
    std::vector<Pulse_t> pulses;	
    for(const auto& wf : evfifo) 
      if(connected_channel(wf.channel_number()))
	pulses.push_back(create_unbiased_pulse(wf));
							  
    return pulses;
  }
  
  
  
  
  Pulse_t UnbiasedPulse::create_unbiased_pulse( const ::larlite::fifo& wf,
						Int_t t_start, 
						Int_t t_end)
  {
    
    Pulse_t p;
    if(t_start == -1) t_start = _tstart;
    if(t_end   == -1) t_end   = _tend;
    
    t_start = (Int_t)t_start;
    t_end   = (Int_t)t_end;
    
    t_start += _delay;
    t_end   += _delay;

    if(t_end >= wf.size()) t_end -= _delay;
    
    t_start -= _left_offset;    
    t_end   += _right_offset;

    if(t_start < 0)          t_start += _left_offset;
    if(t_end   >= wf.size()) t_end   -= _right_offset;

    // auto baseline        = float{0.0};
    // Int_t baseline_start = t_start - _baseline_num;
    // Int_t baseline_end   = t_start;

    // if(baseline_start < 0) {
    //   baseline_start = t_end + 1;
    //   baseline_end   = baseline_start + _baseline_num;  
    // }

    // for(unsigned short t = baseline_start; t < baseline_end; ++t)
    //   baseline += wf[t];
    // baseline /= _baseline_num;

    auto baseline = _algo.Calculate(wf,1).first;

    p.ch       = wf.channel_number();
    p.tmax     = find_peak(wf, t_start, t_end);	
    p.amp      = wf[p.tmax] - baseline;
    p.ped_mean = baseline;
    p.tstart   = t_start;
    p.tend     = t_end;
    
    auto area = float{0.0};    
    for(unsigned short t = t_start; t <= t_end; ++t)
      if(wf[t] > baseline) area += wf[t] - baseline;
        
    p.area = area;
    return p; 
  }

  size_t UnbiasedPulse::find_peak(const std::vector<unsigned short>& data, const size_t istart, const size_t iend) const
  {
    auto the_max = double{0.0};
    size_t cl = 4096;
    
    for(size_t i = istart; i < iend; ++i) {
      if(data[i] > the_max) { the_max = data[i]; cl = i; }
    }
    
    return cl;
  }

}  

#endif
