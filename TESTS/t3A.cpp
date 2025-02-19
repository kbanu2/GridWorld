
#include "GridWorld.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "_test.h"
#include "_util.h"

using std::cout;
using std::cin;
using std::string;



/**
  birth n people into district 5,5
  kill  people 0..n-1

  THEN:  n calls to members (5,5)
**/

bool t3(int n) {
  GridWorld *gw = new GridWorld(20, 20);
  int i, id;
  vector<int> ref;
  vector<int> *m;

  for(i=0; i<n; i++) {
    gw->birth(0, 0, id);
    if(id != i) {
      // std::cout << "FAILURE type-1:  id mismatch on birth\n";
      return false;
    }
    ref.push_back(i);
  }

  m = gw->members(0, 0);
  if(*m != ref) {
    // std::cout << "FAILURE type-2:  members wrong?\n";
    return false;
  }


  for(i=n/2; i<n; i++) {
    if(!gw->death(i)) {
      /*
      std::cout << "FAILURE type-3:  attempted death failed?\n";
      std::cout << "    attempted kill:  " << i << "\n";
      */
      return false;
    }
  }



  if(gw->population() != n/2) {
    /*
    std::cout << "FAILURE type-4:  world pop wrong?\n";
    std::cout << "  expected:  " << n/2 << "\n";
    std::cout << "  reported:  " << gw->population() << "\n";
    */
    return false;
  }

  vector<int> ref2;
  for(i=0; i<n/2; i++) {
    ref2.push_back(i);
  }
  delete m;
  m = gw->members(0, 0);
  if(*m != ref2) {
    // std::cout << "FAILURE type-5:  members (0,0) wrong after death ops??\n";
    return false;
  }

  //  make sure the 1st half is still alive and in (0,0)
  for(i=0; i<n/2; i++) {
    int r, c;
    r=-1; c=-1;
    if(!gw->whereis(i, r, c)) {
      // std::cout << "FAILURE type-5.1:  whereis failed?\n";
      return false;
    }
    if(r != 0 || c != 0) {
      /*
      std::cout << "FAILURE type-5.2:  whereis " << i << " wrong?\n";
      std::cout << "  expected:  (0, 0)\n";
      std::cout << "  reported:  (" << r << ", " << c << ")\n";
      */
      return false;
    }
  }
  // make sure the 2nd half is dead
  for(i=n/2; i<n; i++) {
    int r, c;

    r=-1; c=-1;
    if(gw->whereis(i, r, c)) {
      /*
      std::cout << "FAILURE type-5.3:  whereis error?\n";
      std::cout << "  person " << i << " should be dead\n";
      std::cout << "  reported as alive!\n";
      */
      return false;
    }
  }
  // this sequence of births should restore (0,0) to exactly original
  //   member list of 0..n-1
  for(i=n/2; i<n; i++) {
    gw->birth(0,0,id);
    if(id != i) {
      /*
      std::cout << "FAILURE type-6:  birth(0,0) wrong ??\n";
      std::cout << "   expected id:  " << i << "\n";
      std::cout << "   reported id:  " << id << "\n";
      */
      return false;
    }
  }
  delete m;
  m = gw->members(0,0);
  if(*m != ref) {
    // std::cout << "FAILURE type-7:  members (0,0) wrong?\n";
    return false;
  }



  if(gw->population(0, 0) != n) {
    /*
    std::cout << "FAILURE type-8:  (0,0) pop wrong?\n";
    std::cout << "  expected:  " << n << "\n";
    std::cout << "  reported:  " << gw->population(0,0) << "\n";
    */
    return false;
  }
  if(gw->population() != n) {
    /*
    std::cout << "FAILURE type-9:  world pop wrong?\n";
    std::cout << "  expected:  " << n << "\n";
    std::cout << "  reported:  " << gw->population(0,0) << "\n";
    */
    return false;
  }
  int r, c;

  for(i=0; i<n; i++) {
    r=-1; c=-1;
    if(!gw->whereis(i, r, c)) {
     //  std::cout << "FAILURE type-8:  whereis failed?\n";
      return false;
    }
    if(r != 0 || c != 0) {
      /*
      std::cout << "FAILURE type-9:  whereis " << i << " wrong?\n";
      std::cout << "  expected:  (0, 0)\n";
      std::cout << "  reported:  (" << r << ", " << c << ")\n";
      */
      return false;
    }
  }
  delete m;
  delete gw;
  return true;
}



















/*
 *
 * Optional cmd-line arg is "n" which is used to determine
 *   number of operations (births, etc.) performed.
 *
 */
int main(int argc, char *argv[]){
  int n = ___N;
  int ntrials = __NTRIALS;

  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2)
    ntrials = atoi(argv[2]);

  set_ntrials(ntrials);


  START("~ TIMED TEST");
  {

    PtsPer = 15.0;

    TIME_RATIO(t3(n), t3(2*n), 
        "Big mishmash test! (timed)",
        1, 2.5, PtsPer);
  }
  END
  return 0;
}
