#ifndef LARLITE_RAWWFANA_CXX
#define LARLITE_RAWWFANA_CXX

#include "RawWFAna.h"

namespace larlite {

  bool RawWFAna::initialize() {

    return true;
  }
  
  bool RawWFAna::analyze(storage_manager* storage) {

    // get waveform
    auto ev_fifo = storage->get_data<event_fifo>("pmt_xmit");

    // Return if no wf available
    if(!ev_fifo || ev_fifo->empty()) return true;

    for(auto const& wf : *ev_fifo) {

      auto pulse_v = _algo.Reconstruct(wf);

    }
    
    return true;
  }

  bool RawWFAna::finalize() {

    return true;
  }

}
#endif
