/**
 * \file PulseFinder.h
 *
 * \ingroup OpAnaTreeMaker
 * 
 * \brief Class def header for a class PulseFinder
 *
 * @author kazuhiro
 */

/** \addtogroup OpAnaTreeMaker

    @{*/
#ifndef PULSEFINDER_H
#define PULSEFINDER_H

#include <iostream>
#include <vector>
#include "DataFormat/fifo.h"
#include "PedEstimator.h"
namespace opana {

  struct Pulse_t {
    short ch;
    short tstart;
    short tend;
    short tmax;
    float ped_mean;
    float amp;
    float area;

    Pulse_t() {
      ch = -1;
      tstart = tend = tmax = -1;
      ped_mean = -1;
      amp = area = -1;
    }
  };
  /**
     \class PulseFinder
     User defined class PulseFinder ... these comments are used to generate
     doxygen documentation!
  */
  class PulseFinder{
    
  public:
    
    /// Default constructor
    PulseFinder(){}
    
    /// Default destructor
    ~PulseFinder(){}

    const std::vector< opana::Pulse_t> Reconstruct(const ::larlite::fifo& wf) const;

    /// Access to pedestal estimator algorithm
    PedEstimator& Algo() { return _algo; }
    
  protected:

    PedEstimator _algo;
  };
}

#endif
/** @} */ // end of doxygen group 

