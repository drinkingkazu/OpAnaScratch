/**
 * \file RawWFAna.h
 *
 * \ingroup OpAnaTreeMaker
 * 
 * \brief Class def header for a class RawFlasherAna
 *
 * @author kazuhiro
 */

/** \addtogroup OpAnaTreeMaker
    
    @{*/

#ifndef LARLITE_RAWFLASHERANA_H
#define LARLITE_RAWFLASHERANA_H

#include "Analysis/ana_base.h"
#include "PulseFinderBase.h"
#include "LogicPulseFinder.h"
#include "UnbiasedPulse.h"
#include "DataFormat/fifo.h"

#include <TTree.h>
namespace larlite {
  /**
     \class RawFlasherAna
     User custom analysis class made by SHELL_USER_NAME
   */
  class RawFlasherAna : public ana_base{
  
  public:

    /// Default constructor
    RawFlasherAna();

    /// Default destructor
    virtual ~RawFlasherAna(){}

    /** IMPLEMENT in RawFlasherAna.cc!
        Initialization method to be called before the analysis event loop.
    */ 
    virtual bool initialize();

    /** IMPLEMENT in RawFlasherAna.cc! 
        Analyze a data event-by-event  
    */
    virtual bool analyze(storage_manager* storage);

    /** IMPLEMENT in RawFlasherAna.cc! 
        Finalize method to be called after all events processed.
    */
    virtual bool finalize();

    /// Store waveform flag
    void StoreWaveform(bool doit=true) { _store_wf = doit; }

    /// Algorithm Setter
    //void SetAlgo            (::opana::PulseFinderBase*  algo) { _algo = algo; }
    void SetUnbiasedPulse   (::opana::UnbiasedPulse*    algo) { _up   = algo; }
    void SetLogicPulseFinder(::opana::LogicPulseFinder* algo) { _lpf  = algo; }

  protected:

    /// Optical reconstruction algorithm
    //::opana::PulseFinderBase *  _algo;
    ::opana::LogicPulseFinder* _lpf;
    ::opana::UnbiasedPulse   * _up;

    /// Raw Waveform ttree
    TTree* _raw_wf_tree;

    /// Pulse Waveform ttree
    TTree* _pulse_wf_tree;
    
    /// Pulse TTree
    TTree* _pulse_tree;

    /// Flasher TTree
    TTree* _flash_tree;

    bool _store_wf;
    unsigned int _event;
    unsigned short _slot,_ch, _frame, _sample, _fem;
    std::vector<unsigned short> _wf;
    ::opana::Pulse_t _pulse;

    int _evt_num;
    
    //::larlite::event_fifo _FEM5;
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
