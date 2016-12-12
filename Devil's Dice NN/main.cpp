/*******************************************************************
* Neural Network Training Example
* ------------------------------------------------------------------
* Bobby Anguelov - takinginitiative.wordpress.com (2008)
* MSN & email: banguelov@cs.up.ac.za
*********************************************************************/

//standard libraries
#include <iostream>
#include <ctime>

//custom includes
#include "neuralNetwork.h"
#include "neuralNetworkTrainer.h"

//use standard namespace
using namespace std;

int main()
{		
	/*
	//seed random number generator
	srand( (unsigned int) time(0) );
	
	//create data set reader and load data file
	dataReader d;
	d.loadDataFile("OriginalAI_Data.csv",5,1);
	d.setCreationApproach( STATIC, 10 );	
	*/
	//create neural network
	neuralNetwork nn(5,3,1);
	/*
	//create neural network trainer
	neuralNetworkTrainer nT( &nn );
	nT.setTrainingParameters(0.001, 0.9, false);
	nT.setStoppingConditions(1000, 100);
	nT.enableLogging("log.csv", 5);
	
	//train neural network on data sets
	for (int i=0; i < d.getNumTrainingSets(); i++ )
	{
		nT.trainNetwork( d.getTrainingDataSet() );
	}	

	//save the weights
	nn.saveWeights("weights.csv");
	*/


	nn.loadWeights("weights.csv");
	double* pattern = new double[5];
	pattern[0] = 1.0;
	pattern[1] = 2.0;
	pattern[2] = 3.0;
	pattern[3] = 4.0;
	pattern[4] = 5.0;
	int* result = nn.feedForwardPattern(pattern);


	cout << endl << endl << "-- END OF PROGRAM --" << endl;
	char c; cin >> c;

	return 0;
}
