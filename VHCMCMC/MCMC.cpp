#include "MCMC.h"

MCMC::MCMC()
{
	step = 0;
	proposedLayout.change();
}

void MCMC::accept()
{
	layout = proposedLayout;
	step++;
}

void MCMC::reject()
{
	step++;
}

void MCMC::generateProposal()
{
	proposedLayout = layout;
	proposedLayout.change();
}
