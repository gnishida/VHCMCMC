#include "HumanComputationEmulator.h"
#include <random>

HumanComputationEmulator::HumanComputationEmulator(int numWorkers)
{
	this->numWorkers = numWorkers;
	//w = cv::Mat(numWorkers, ndims, CV_32F);
	//cv::randu(w, cv::Scalar(0.0), cv::Scalar(1.0));
}


HumanComputationEmulator::~HumanComputationEmulator(void)
{
}

std::vector<bool> HumanComputationEmulator::run(cv::Mat feature1, cv::Mat feature2)
{
	std::mt19937 mtengine;
	std::uniform_real_distribution<double> distribution(0.0,1.0);

	// initialize workers' weight vector
	cv::Mat w(numWorkers, feature1.rows, CV_32F);
	cv::randu(w, cv::Scalar(0.0), cv::Scalar(1.0));

	// compute logistic function
	cv::Mat diff;
	cv::exp(w * feature1 - w * feature2, diff);
	cv::Mat logistic;
	cv::divide(1.0, diff, logistic);



	// compute votes
	std::vector<bool> results;
	for (int i = 0; i < logistic.rows; ++i) {
		if (distribution(mtengine) <= logistic.at<float>(i, 0)) {
			results.push_back(true);
		} else {
			results.push_back(false);
		}
	}

	return results;
}
