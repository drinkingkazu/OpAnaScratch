/**
 * \file RawWFAna.h
 *
 * \ingroup OpAnaTreeMaker
 * 
 * \brief Class def header for a class RawWFAna
 *
 * @author kazuhiro
 */

/** \addtogroup OpAnaTreeMaker

    @{*/

#ifndef LARLITE_RAWWFANA_H
#define LARLITE_RAWWFANA_H

#include "Analysis/ana_base.h"
#include "PulseFinder.h"

namespace larlite {
  /**
     \class RawWFAna
     User custom analysis class made by SHELL_USER_NAME
   */
  class RawWFAna : public ana_base{
  
  public:

    /// Default constructor
    RawWFAna(){ _name="RawWFAna"; _fout=0;}

    /// Default destructor
    virtual ~RawWFAna(){}

    /** IMPLEMENT in RawWFAna.cc!
        Initialization method to be called before the analysis event loop.
    */ 
    virtual bool initialize();

    /** IMPLEMENT in RawWFAna.cc! 
        Analyze a data event-by-event  
    */
    virtual bool analyze(storage_manager* storage);

    /** IMPLEMENT in RawWFAna.cc! 
        Finalize method to be called after all events processed.
    */
    virtual bool finalize();


    /// Algorithm instance getter
    ::opana::PulseFinder& Algo() {return _algo; }

  protected:
    ::opana::PulseFinder _algo;
  };
}
#endif

//**************************************************************************
// 
// For Analysis framework documentation, read Manual.pdf here:
//
// http://microboone-docdb.fnal.gov:8080/cgi-bin/ShowDocument?docid=3183
//
//**************************************************************************

/** @} */ // end of doxygen group 
