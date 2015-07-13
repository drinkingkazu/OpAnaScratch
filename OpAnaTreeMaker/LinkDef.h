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
#pragma link C++ class opana::Pulse_t;
#pragma link C++ class std::vector<opana::Pulse_t>+;
#pragma link C++ class opana::PedEstimator+;
#pragma link C++ class opana::PulseFinder+;
//ADD_NEW_CLASS ... do not change this line
#endif



