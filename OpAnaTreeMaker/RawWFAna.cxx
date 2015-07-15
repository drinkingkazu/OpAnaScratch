#ifndef LARLITE_RAWWFANA_CXX
#define LARLITE_RAWWFANA_CXX

#include "RawWFAna.h"
#include "DataFormat/fifo.h"
namespace larlite {

  RawWFAna::RawWFAna() : ana_base()
  {
    _name="RawWFAna";
    _fout=0;
    _pulse_tree = _raw_wf_tree = nullptr;
  }
  
  bool RawWFAna::initialize() {

    if(_store_wf){
      _raw_wf_tree = new TTree("raw_wf_tree","Raw Waveforms");
      _raw_wf_tree->Branch("event",&_event,"event/i");
      _raw_wf_tree->Branch("ch",&_ch,"ch/s");
      _raw_wf_tree->Branch("frame",&_frame,"frame/s");
      _raw_wf_tree->Branch("sample",&_sample,"sample/s");
      _raw_wf_tree->Branch("wf","std::vector<unsigned short>",&_wf);
    }
    
    _pulse_tree = new TTree("pulse_tree","Pulse Info");
    _pulse_tree->Branch("event",&_event,"event/i");
    _pulse_tree->Branch("ch",&_ch,"ch/S");
    _pulse_tree->Branch("frame",&_frame,"frame/S");
    _pulse_tree->Branch("sample",&_sample,"sample/S");
    _pulse_tree->Branch("ped",&_pulse.ped_mean,"ped/F");
    _pulse_tree->Branch("tstart",&_pulse.tstart,"tstart/S");
    _pulse_tree->Branch("tend",&_pulse.tend,"tend/S");
    _pulse_tree->Branch("tmax",&_pulse.tmax,"tmax/S");
    _pulse_tree->Branch("amp",&_pulse.amp,"amp/F");
    _pulse_tree->Branch("area",&_pulse.area,"area/F");

    return true;
  }
  
  bool RawWFAna::analyze(storage_manager* storage) {

    // get waveform
    auto ev_fifo = storage->get_data<event_fifo>("pmt_xmit");

    // Return if no wf available
    if(!ev_fifo || ev_fifo->empty()) return true;

    _event = ev_fifo->event_number();

    for(auto const& wf : *ev_fifo) {

      _ch = wf.channel_number();
      _frame = wf.readout_frame_number();
      _sample = wf.readout_sample_number_RAW();
      if(_store_wf) {
	if( _wf.size() != wf.size())
	  _wf.resize(wf.size());
	for(size_t i=0; i<wf.size(); ++i) _wf[i]=wf[i];
	_raw_wf_tree->Fill();
      }
      
      auto pulse_v = _algo.Reconstruct(wf.channel_number(),wf);
      for(auto const& p : pulse_v) {
	_pulse = p;
	_pulse_tree->Fill();
      }
      
    }
    
    return true;
  }

  bool RawWFAna::finalize() {
    if(_fout) {
      _fout->cd();
      if(_pulse_tree) _pulse_tree->Write();
      if(_raw_wf_tree) _raw_wf_tree->Write();
    }
    return true;
  }

}
#endif
