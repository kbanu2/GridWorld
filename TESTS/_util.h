

#ifndef __UTIL_H
#define __UTIL_H

#define ___N 1000

#ifdef SMALL_TRIALS
#define __NTRIALS 50
#else
#define __NTRIALS 50
#endif

#include <vector>

/** GLOBAL LISTS AND ARRAYS FOR CONVENIENT ACCESS **/




void pvec(vector<int> &vec) {
  int i;

  cout << " [ ";
  for(i=0; i<vec.size(); i++) {
    cout << vec[i] << " ";
  }
  cout << "]\n";
}




#endif
