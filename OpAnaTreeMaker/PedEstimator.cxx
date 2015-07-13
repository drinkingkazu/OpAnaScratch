#ifndef PEDESTIMATOR_CXX
#define PEDESTIMATOR_CXX

#include "PedEstimator.h"

namespace opana {

  PedEstimator::PedEstimator()
  {
    _cutoff = 0.5;
    _window = 10;
  }

  void PedEstimator::Configure(unsigned int window,
			       float cutoff )
  {
    _window = window;
    _cutoff = cutoff;
  }
  
  //takes vector, and window size, rms cutoff - if start = true then will start from beginning, false starts at end
  std::pair<float,float> PedEstimator::Calculate(const std::vector<unsigned short>& wf, bool start) const
  {
    float mean = 0;
    float rms = 0;
    int n = wf.size();
    int k = 0;
 
    //number of points to consider in calculation;
    // int window = 10;

    bool below = false;

    //need minimum number to calculate
    if (n >= _window) {
      if (start == true){
	while (below == false && k+_window < n){
	  //std::cout << k+_window << std::endl;
	 
	  rms = getrms(wf, k, k+_window).second;
	  mean = getrms(wf, k, k+_window).first;
	  if (rms < _cutoff){
	    below = true;
	  }
	  k++;
	}
      }

      else{
	k = n-1;
	while (below == false && k - _window > 0){
	  rms = getrms(wf, k-_window, k).second;
	  mean = getrms(wf, k-_window, k).first;
	  if (rms < _cutoff){
	    below = true;
	  }
	  k--;
	}
      }
    }
   
    
    //returns <mean, rms>, or 0,0 if nothing in vector or bad index or not below _cutoff
    return std::pair<float,float>(mean,rms);
  }

  const std::pair<float,float> PedEstimator::getrms (const std::vector<unsigned short>& wf, int k, int m) const{
    float mean = 0;
    float rms = 0;
    for (int i  = k; i < m; i++){
      mean += wf.at(i);
    }

    mean = mean/_window;

    for (int i= k; i < m; i++){
      float diff = wf.at(i)-mean;
      rms += diff*diff;
    }
    rms = sqrt(rms/_window);
    return  std::pair<float,float>(mean,rms);
}

  

}

#endif
