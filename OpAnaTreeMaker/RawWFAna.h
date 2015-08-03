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
#include "PulseFinderBase.h"
#include <TTree.h>
namespace larlite {
  /**
     \class RawWFAna
     User custom analysis class made by SHELL_USER_NAME
   */
  class RawWFAna : public ana_base{
  
  public:

    /// Default constructor
    RawWFAna();

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

    /// Store waveform flag
    void StoreWaveform(bool doit=true) { _store_wf = doit; }

    /// Algorithm Setter
    void SetAlgo(::opana::PulseFinderBase* algo) { _algo = algo; }

    /// Target ch to calculate dt
    void TargetCh(int ch) { _target_ch = ch; }

  protected:
    /// Optical reconstruction algorithm
    ::opana::PulseFinderBase* _algo;

    /// Raw Waveform ttree
    TTree* _raw_wf_tree;

    /// Pulse Waveform ttree
    TTree* _pulse_wf_tree;
    
    /// Pulse TTree
    TTree* _pulse_tree;

    bool _store_wf;
    unsigned int _event;
    unsigned short _slot,_ch, _frame, _sample;
    double _ts;
    double _dt;
    int _target_ch;
    std::vector<unsigned short> _wf;
    ::opana::Pulse_t _pulse;
    
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
