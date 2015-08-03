/**
 * \file UnbiasedPulse.h
 *
 * \ingroup OpAnaTreeMaker
 * 
 * \brief Class def header for a class UnbiasedPulse
 *
 * @author vgenty
 */

/** \addtogroup OpAnaTreeMaker

    @{*/
#ifndef UNBIASEDPULSE_H
#define UNBIASEDPULSE_H

#include <iostream>

#include "DataFormat/fifo.h"

#include "PedEstimator.h"
#include "PulseFinderBase.h"

/**
   \class UnbiasedPulse
   User defined class UnbiasedPulse ... these comments are used to generate
   doxygen documentation!
*/
namespace opana {

  class UnbiasedPulse{

  public:

    /// Default constructor
    UnbiasedPulse(){}

    /// Default destructor
    ~UnbiasedPulse(){}

    void Configure(std::vector<UInt_t> channels,
		   std::vector<UInt_t> fems,
		   UInt_t delay        = 0,
		   //UInt_t baseline_num = 5,
		   UInt_t window_size  = 25,
		   UInt_t left_offset  = 0,
		   UInt_t right_offset = 0,
		   Int_t  tstart       = 10,
		   Int_t  tend         = 20,
		   bool   edge_flag    = false);
		       
    std::vector<Pulse_t> Reconstruct(const std::vector<Pulse_t>& flashes,
				     const ::larlite::event_fifo& evfifo);
    std::vector<Pulse_t> Reconstruct(const ::larlite::event_fifo& evfifo);


    /// Access to pedestal estimator algorithm
    PedEstimator& Algo() { return _algo; }

    
  private:
    
    //template <typename T> 
    //const bool connected_channel( std::vector<T>& v, const T& ch ) 
    //this could be templated :-)
    //const bool connected( const UInt_t& ch ) 
    const bool connected_channel(const UInt_t& ch ) 
    {
      if (std::find(_channels.begin(), _channels.end(), ch) != _channels.end())
        return true;
      return false;
    }
    const bool connected_fem(const UInt_t& fem ) 
    {
      if (std::find(_fems.begin(), _fems.end(), fem) != _fems.end())
        return true;
      return false;
    }
    
    Pulse_t create_unbiased_pulse(const ::larlite::fifo& wf,
				  Int_t t_start = -1, 
				  Int_t t_end   = -1);
    
    bool check_for_mod(const ::larlite::event_fifo& evfifo,
		       UInt_t channel,
		       UInt_t fem,
		       UInt_t peak);
    
    UInt_t _delay;
    UInt_t _left_offset;
    UInt_t _right_offset;

    Int_t  _tstart;
    Int_t  _tend;
    //UInt_t _baseline_num;
    UInt_t _window_size;
    bool   _edge_flag;
    
    std::vector<UInt_t> _channels;  
    std::vector<UInt_t> _fems;  

    PedEstimator _algo;

    size_t find_peak(const std::vector<unsigned short>& data, const size_t istart, const size_t iend) const;
  
    
    
  };

}
#endif

/** @} */ // end of doxygen group 

