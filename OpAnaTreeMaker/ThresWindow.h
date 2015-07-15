/**
 * \file ThresWindow.h
 *
 * \ingroup OpAnaTreeMaker
 * 
 * \brief Class def header for a class ThresWindow
 *
 * @author kazuhiro
 */

/** \addtogroup OpAnaTreeMaker

    @{*/
#ifndef THRESWINDOW_H
#define THRESWINDOW_H

#include <iostream>
#include "PulseFinderBase.h"
namespace opana {
  /**
     \class ThresWindow
     User defined class ThresWindow ... these comments are used to generate
     doxygen documentation!
  */
  class ThresWindow : public PulseFinderBase {
    
  public:
    
    /// Default constructor
    ThresWindow(){}
    
    /// Default destructor
    ~ThresWindow(){}

    virtual const PulseVector_t Reconstruct(const unsigned int ch,
					    const Waveform_t& wf) const
    {
      PulseVector_t res;
      return res;
    }
  };
}

#endif
/** @} */ // end of doxygen group 

