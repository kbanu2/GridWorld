
DISCLAIMER:  These test cases will be included in
the complete test suite used to grade your submission.
However, they may not be the ONLY test cases used for
grading.

DISCLAIMER 2:  some of these test cases are runtime
based.  They are pretty robust, but "false negatives"
are still possible.  If you fail a test that you 
think you should pass:

  Check the output - there will be the results of a
    "ratio test".  Check how much over the cutoff your
    run was.  if it was close, it is likely a 
    false negative.

  Run the test again...

------------------------------------

Test programs:

  t1AB.cpp
  t1A_timed.cpp
  t1CD.cpp
  t1D_timed.cpp
  t1E.cpp
  t1E_timed.cpp

  t2A.cpp
  t2A_timed.cpp
  t2B.cpp
  t2C.cpp
  t2C_timed.cpp

  t3A.cpp
  t4A.cpp
  t5A.cpp

These tests total 200 points.

RUNNING TESTS:

  Place your implementation of GridWorld.h into
  a directory containing all of these files.

  You can run the tests individually or in
  'batch' mode by running the script run_tests.
  The script will produce a subdirectory called
  _TEST_RESULTS containing summaries of the
  tests.


         IMPORTANT SIDE NOTE:  the file run_tests is a bash script
         and must have "executable permission" to run as shown
         above.

         As given, it does have executable permission, but if
         you download it directly, your downloaded version may
         not have executable permission (kind of a safety thing
         I suppose).

         In the unix world, you correct this with 

              chmod +x run_tests

