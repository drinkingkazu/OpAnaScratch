/**
 * \file PedEstimator.h
 *
 * \ingroup OpAnaTreeMaker
 * 
 * \brief Class def header for a class PedEstimator
 *
 * @author kazuhiro
 */

/** \addtogroup OpAnaTreeMaker

    @{*/
#ifndef PEDESTIMATOR_H
#define PEDESTIMATOR_H

#include <iostream>
#include <vector>
#include <utility>
#include <math.h> 
namespace opana {
  /**
     \class PedEstimator
     User defined class PedEstimator ... these comments are used to generate
     doxygen documentation!
  */
  class PedEstimator{
    
  public:
    
    /// Default constructor
    PedEstimator(){}
    
    /// Default destructor
    ~PedEstimator(){}

    /// Pedestal Estimator
    std::pair<float,float> Calculate(const std::vector<unsigned short>& wf, bool start, int window, float cutoff) const;


    const std::pair<float,float> getrms (const std::vector<unsigned short>& wf, int k, int m, int window) const;
    
    
  };
}

#endif
/** @} */ // end of doxygen group 

