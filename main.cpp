////////////////////////////////////////////////////////////////////////////////
// Jason Ellis, Harry Hull
// Project 3.
// CPSC 3385: File Structures and Multimedia
// Spring 2010
// This creates a CExperiment object and runs each trial.
////////////////////////////////////////////////////////////////////////////////
#include "CExperiment.h"

using namespace std;

int main()
{	
	static CExperiment Experiment;
	
	Experiment.Setup();
	Experiment.Run(64);
	Experiment.Run(512);
	Experiment.Run(1024);
	Experiment.Run(2048);
	Experiment.Run(3072);
	Experiment.Run(4096);
	Experiment.Run(6144);
	Experiment.Run(8192);
	Experiment.Run(16384);
	


	return 0;
}