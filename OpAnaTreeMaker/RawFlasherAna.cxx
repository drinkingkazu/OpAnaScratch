#ifndef LARLITE_RAWFLASHERANA_CXX
#define LARLITE_RAWFLASHERANA_CXX

#include "RawFlasherAna.h"


namespace larlite {

  RawFlasherAna::RawFlasherAna() : ana_base()
  {
    //_algo = nullptr;
    _name="RawFlasherAna";
    _fout=0;
    _pulse_tree = _raw_wf_tree = nullptr;
    _evt_num = 0;
  }
  
  bool RawFlasherAna::initialize() {

    // if(!_algo)
    //   throw std::exception();
    
    if(_store_wf){
      _raw_wf_tree = new TTree("raw_wf_tree","Raw Waveforms");
      _raw_wf_tree->Branch("event",&_event,"event/i");
      _raw_wf_tree->Branch("slot",&_slot,"slot/s");
      _raw_wf_tree->Branch("ch",&_ch,"ch/s");
      _raw_wf_tree->Branch("frame",&_frame,"frame/s");
      _raw_wf_tree->Branch("sample",&_sample,"sample/s");
      _raw_wf_tree->Branch("fem"   ,&_fem,"fem/s");
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


    _flash_tree = new TTree("flasher_tree","Flasher Pulse Info");
    _flash_tree->Branch("event",&_event,"event/i");
    _flash_tree->Branch("ch",&_ch,"ch/S");
    _flash_tree->Branch("frame",&_frame,"frame/S");
    _flash_tree->Branch("sample",&_sample,"sample/S");
    _flash_tree->Branch("ped",&_pulse.ped_mean,"ped/F");
    _flash_tree->Branch("tstart",&_pulse.tstart,"tstart/S");
    _flash_tree->Branch("tend",&_pulse.tend,"tend/S");
    _flash_tree->Branch("tmax",&_pulse.tmax,"tmax/S");
    _flash_tree->Branch("amp",&_pulse.amp,"amp/F");
    _flash_tree->Branch("area",&_pulse.area,"area/F");
    _flash_tree->Branch("width",&_pulse.width,"width/F");

    return true;
  }
  
  bool RawFlasherAna::analyze(storage_manager* storage) {
    
    // if(_evt_num != storage->event_id())
    // _evt_num = storage->event_id();
    // get waveform
    
    //    std::cout << "On event... " << storage->event_id() << "\n";
    
    auto ev_fifo = storage->get_data<event_fifo>("pmt_xmit");
    
    //std::cout << "checksum() " << ev_fifo->checksum() << "\n";
    //Return if no wf available
    if(!ev_fifo || ev_fifo->empty())
      return true;
    
    _event = ev_fifo->event_number();
    _slot = ev_fifo->module_address();
    
    // if(storage->event_id()%2 == 0) {
    //   _FEM5 = *ev_fifo;
    //   return false;
    // }
    
    for(auto const& wf : *ev_fifo) {
      
      _ch     = wf.channel_number();
      _frame  = wf.readout_frame_number();
      _sample = wf.readout_sample_number_RAW();
      _fem    = wf.module_address();
      
      if(_store_wf) {
    	if( _wf.size() != wf.size())
    	  _wf.resize(wf.size());
    	for(size_t i=0; i<wf.size(); ++i) _wf[i]=wf[i];
    	_raw_wf_tree->Fill();
      }
    }
    
    //auto pulse_v = _algo->Reconstruct(wf.channel_number(),wf);
    //_lpf->dump();
    //need to ensure that you only get the flashes once per event
    //std::vector<Pulse_t> flashes;
    //if(storage->event_id()%2 != 0) {
    auto flashes = _lpf->GetPulses(*ev_fifo);
    // }
    // else {
    //   return false;
    // }
    
    //auto flashes = _lpf->GetPulses(*ev_fifo);
    std::cout << "Found ... " << flashes.size() << " flashes\n";
    for(auto const& p : flashes) {
      _pulse = p;
      _flash_tree->Fill();
    }
    for(auto& f: flashes)
      f.dump();

    auto pulse_v = _up ->Reconstruct(flashes,*ev_fifo);
        
    for(auto const& p : pulse_v) {
      _pulse = p;
      _pulse_tree->Fill();
    }
    
    //_FEM5.clear();
      
    
    
    return true;
  }
  
  bool RawFlasherAna::finalize() {
    if(_fout) {
      _fout->cd();
      if(_pulse_tree)  _pulse_tree->Write();
      if(_flash_tree)  _flash_tree->Write();
      if(_raw_wf_tree) _raw_wf_tree->Write();
    }
    return true;
  }

}
#endif
