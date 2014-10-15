#pragma once

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "Layout.h"

class HumanComputationEmulator
{
public:
	HumanComputationEmulator(int numWorkers);
	~HumanComputationEmulator(void);
	std::vector<bool> run(cv::Mat feature1, cv::Mat feature2);

private:
	int numWorkers;
};

