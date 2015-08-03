/**
 * \file LogicPulseFinder.h
 *
 * \ingroup OpAnaTreeMaker
 * 
 * \brief Class def header for a class LogicPulseFinder
 *
 * @author vgenty
 */

/** \addtogroup OpAnaTreeMaker

    @{*/
#ifndef LOGICPULSEFINDER_H
#define LOGICPULSEFINDER_H

//C++
#include <iostream>
#include <vector>

//local for Pulse_t struct
#include "PulseFinderBase.h"

#include "PedEstimator.h"
//larlite
#include "DataFormat/fifo.h"

/**
   \class LogicPulseFinder
   User defined class LogicPulseFinder ... these comments are used to generate
   doxygen documentation!
*/
namespace opana {
  class LogicPulseFinder{

  public:

    /// Default constructor
    LogicPulseFinder(){}

    /// Default destructor
    ~LogicPulseFinder(){}

    /// Find logic pulses in channel_num
    std::vector<Pulse_t> GetPulses(const ::larlite::event_fifo& evfifo);
    /// Configure function
      void Configure(float baseline     = 2048, //baseline adc
		     float height       = 100,  //min logic pulse height
		     UInt_t channel_num = 41);  //what channel we on?
  
    void dump() {
      std::cout << "\n\t == LogicPulseFinder == "
		<< "\tbaseline... " << _baseline
		<< "\theight....  " << _height
		<< "\tchannel...  " << _channel_num
		<< "\n\t == End == \n";
    }
    
    PedEstimator& Algo() { return _algo; }
    
  private:
    PedEstimator _algo;
    
    
    float  _baseline;
    float  _height;
    UInt_t _channel_num;
    
  };
}
#endif
/** @} */ // end of doxygen group 

