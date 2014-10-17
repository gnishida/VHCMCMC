#pragma once

#include "Layout.h"
class MCMC
{
public:
	MCMC();
	void accept();
	void reject();
	void generateProposal();

public:
	int step;
	Layout layout;
	Layout proposedLayout;
};

