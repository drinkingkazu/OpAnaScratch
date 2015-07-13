#ifndef PEDESTIMATOR_CXX
#define PEDESTIMATOR_CXX

#include "PedEstimator.h"

namespace opana {

  //takes vector, and window size, rms cutoff - if start = true then will start from beginning, false starts at end
  std::pair<float,float> PedEstimator::Calculate(const std::vector<unsigned short>& wf, bool start, int window, float cutoff) const
  {
    float mean = 0;
    float rms = 0;
    int n = wf.size();
    int k = 0;
 
    //number of points to consider in calculation;
    // int window = 10;

    bool below = false;

    //need minimum number to calculate
    if (n >= window) {
      if (start == true){
	while (below == false && k+window < n){
	  std::cout << k+window << std::endl;
	 
	  rms = getrms(wf, k, k+window, window).second;
	  mean = getrms(wf, k, k+window, window).first;
	  if (rms < cutoff){
	    below = true;
	  }
	  k++;
	}
      }

      else{
	k = n-1;
	while (below == false && k - window > 0){
	  rms = getrms(wf, k-window, k, window).second;
	  mean = getrms(wf, k-window, k, window).first;
	  if (rms < cutoff){
	    below = true;
	  }
	  k--;
	}
      }
    }
   
    
    //returns <mean, rms>, or 0,0 if nothing in vector or bad index or not below cutoff
    return std::pair<float,float>(mean,rms);
  }

  const std::pair<float,float> PedEstimator::getrms (const std::vector<unsigned short>& wf, int k, int m, int window) const{
    float mean = 0;
    float rms = 0;
    for (int i  = k; i < m; i++){
      mean += wf.at(i);
    }

    mean = mean/window;

    for (int i= k; i < m; i++){
      float diff = wf.at(i)-mean;
      rms += diff*diff;
    }
    rms = sqrt(rms/window);
    return  std::pair<float,float>(mean,rms);
}

  

}

#endif
