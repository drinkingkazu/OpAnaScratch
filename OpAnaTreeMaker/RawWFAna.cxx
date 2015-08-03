#ifndef LARLITE_RAWWFANA_CXX
#define LARLITE_RAWWFANA_CXX

#include "RawWFAna.h"
#include "DataFormat/fifo.h"
namespace larlite {

  RawWFAna::RawWFAna() : ana_base()
  {
    _algo = nullptr;
    _name="RawWFAna";
    _fout=0;
    _pulse_tree = _raw_wf_tree = nullptr;
    _target_ch = -1;
  }
  
  bool RawWFAna::initialize() {

    if(!_algo)
      throw std::exception();
    
    if(_store_wf){
      _raw_wf_tree = new TTree("raw_wf_tree","Raw Waveforms");
      _raw_wf_tree->Branch("event",&_event,"event/i");
      _raw_wf_tree->Branch("slot",&_slot,"slot/s");
      _raw_wf_tree->Branch("ch",&_ch,"ch/s");
      _raw_wf_tree->Branch("timestamp",&_ts,"timestamp/D");
      //_raw_wf_tree->Branch("frame",&_frame,"frame/s");
      //_raw_wf_tree->Branch("sample",&_sample,"sample/s");
      _raw_wf_tree->Branch("wf","std::vector<unsigned short>",&_wf);
    }
    
    _pulse_tree = new TTree("pulse_tree","Pulse Info");
    _pulse_tree->Branch("event",&_event,"event/i");
    _pulse_tree->Branch("ch",&_ch,"ch/s");
    _pulse_tree->Branch("slot",&_slot,"slot/s");
    _pulse_tree->Branch("frame",&_frame,"frame/S");
    _pulse_tree->Branch("sample",&_sample,"sample/S");
    _pulse_tree->Branch("timestamp",&_ts,"timestamp/D");
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
    if(!ev_fifo || ev_fifo->empty()) {
      std::cout<<"nothing fuck you " <<std::endl;
      return true;
    }

    int event_frame  = ev_fifo->fem_trig_frame_number();
    int event_sample = ev_fifo->fem_trig_sample_number_RAW();

    _event = ev_fifo->event_number();
    //std::cout<<ev_fifo->event_number()<<" : "<<(int)(ev_fifo->module_address())<<std::endl;
    //if((storage->get_index()%2)==0) _slot=6;

    std::vector<opana::Pulse_t> result_v;
    std::vector<double> result_time_v;
    std::vector<double> target_time_v;
    for(auto const& wf : *ev_fifo) {
      _ch = wf.channel_number();
      _frame = wf.readout_frame_number();
      _sample = wf.readout_sample_number_RAW();
      _slot = (int)(wf.module_address());
      if(_store_wf) {
	if( _wf.size() != wf.size())
	  _wf.resize(wf.size());
	for(size_t i=0; i<wf.size(); ++i) _wf[i]=wf[i];

	_ts  = ( (int)_frame - event_frame ) * 1600.;
	_ts += ( (int)_sample - event_sample ) * 0.0156;
	_raw_wf_tree->Fill();
      }
      
      auto pulse_v = _algo->Reconstruct(wf.channel_number(),wf);

      result_v.reserve(result_v.size() + pulse_v.size());

      for(auto &p : pulse_v) {
	if((int)(p.ch) == _target_ch)
	  target_time_v.push_back( _ts + p.tstart * 0.0156 );
	result_time_v.push_back( _ts + p.tstart * 0.0156 );
	result_v.emplace_back(p);
      }
    }


    // Find target channel's timings
    for(size_t i=0; i<result_v.size(); ++i) {

      auto const& p  = result_v[i];
      auto const& ts = result_time_v[i];

      _dt = -1;
      if((int)(p.ch) == _target_ch) _ts = 0;
      else{
	for(auto const& ref_ts : result_time_v) {

	  if(std::abs(_dt) > std::abs(ts - ref_ts))

	    _dt = (ref_ts - ts);
	}
      }
      
      _pulse = p;
      _pulse_tree->Fill();
    }
    
    return true;
  }

  bool RawWFAna::finalize() {
    if(_fout) {
      _fout->cd();
      if(_raw_wf_tree) _raw_wf_tree->Write();
      if(_pulse_tree) _pulse_tree->Write();

    }
    return true;
  }

}
#endif
