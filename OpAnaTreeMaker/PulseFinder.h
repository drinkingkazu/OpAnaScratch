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
    short ch; //channel
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

    void dump() {
      std::cout  << "\n\t==start=="
		 << "\n\tch:       " << ch
		 << "\n\ttstart:   " << tstart
		 << "\n\ttend:     " << tend
		 << "\n\ttmax:     " << tmax
		 << "\n\tped_mean: " << ped_mean
		 << "\n\tamp:      " << amp
		 << "\n\tarea:     " << area
		 << "\n\t==end==\n";
	
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
    
    
    //Auxiliary
    size_t find_peak(const ::larlite::fifo& data, const size_t istart, const size_t iend) const;
    

    /// Access to pedestal estimator algorithm
    PedEstimator& Algo() { return _algo; }

    /// Configure function
    void Configure(float rise_edge=5., float fall_edge=5., float threshold = 3.0);

  protected:

    PedEstimator _algo;
    float _rise_edge, _fall_edge, _threshold;

  };
}

#endif
/** @} */ // end of doxygen group 

