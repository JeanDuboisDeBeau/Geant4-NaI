Geant4-NaI
This repository contains code used for simulating the NaI detector and for analyzing the data using Python and C++.

Instructions
Step 1: Geant4
Download the Geant4-NaIDetector.zip file into the Geant4 directory.
Step 2: Geant4
Modify the run_matt.mac file located in B1/build/. Set your desired number of events (note that you need to make this change in two places).
Step 3: Geant4
Execute run_matt.mac with Geant4 from the B1/build/ directory (after completing the cmake and build steps, of course). Geant4 will run in console mode and create an output file named B1/build/DataG4.txt.
Step 4: C++
Retrieve the ConsoleApplication1 file from the C++/ directory and adapt the code (specifically line 16) to read the output file from the previous step. Choose a name and location for the output file (line 65). Execute the program. It will run in console mode and produce an output file.
Step 5: Python
Obtain the output file from the previous step, which contains the merged results of Geant4 runs 1 and 2 (for the two energies). Download the Python script located at Python/Analyse.py. Modify the code (line 13) to specify the path to the file from the previous step.
Step 6: Python
Download the file Python/data_NaI.txt and add it to the folder containing Python/Analyse.py.
Step 7: Python
Modify lines 4-7 to set the parameters as needed.
Step 8: Python
Finally, run the Python script. It will create four graphs comparing the simulated data to the actual spectrum. Congratulations! You've successfully completed the process!
