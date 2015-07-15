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
#include "PedEstimator.h"
#include "PulseFinderBase.h"
namespace opana {

  /**
     \class PulseFinder
     User defined class PulseFinder ... these comments are used to generate
     doxygen documentation!
  */
  class PulseFinder : public PulseFinderBase {
    
  public:
    
    /// Default constructor
    PulseFinder(){}
    
    /// Default destructor
    ~PulseFinder(){}

    const std::vector< opana::Pulse_t>
    Reconstruct(const unsigned int ch,
		const std::vector<unsigned short>& wf) const;
    
    //Auxiliary
    size_t find_peak(const std::vector<unsigned short>& data, const size_t istart, const size_t iend) const;
    

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

