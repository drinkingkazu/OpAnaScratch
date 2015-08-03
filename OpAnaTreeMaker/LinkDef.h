//
// cint script to generate libraries
// Declaire namespace & classes you defined
// #pragma statement: order matters! Google it ;)
//

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class larlite::RawWFAna+;
#pragma link C++ class larlite::RawFlasherAna+;
#pragma link C++ class opana::Pulse_t;
#pragma link C++ class std::vector<opana::Pulse_t>+;
#pragma link C++ class opana::PedEstimator+;
#pragma link C++ class opana::PulseFinder+;
//#pragma link C++ class opana::PulseFinderBase+;
#pragma link C++ class opana::ThresWindow+;
//#pragma link C++ class larlite::FindChannel+;
#pragma link C++ class opana::LogicPulseFinder+;
#pragma link C++ class opana::UnbiasedPulse+;

//ADD_NEW_CLASS ... do not change this line
#endif






