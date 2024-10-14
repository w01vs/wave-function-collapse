#pragma once

#ifndef	WFMODEL_H
#define WFMODEL_H

#include <vector>
#include <map>
#include "Wavefunction.h"
#include <stack>
#include "Util.h"
#include <string>

class WFModel
{
public:
	WFModel();
	WFModel(int width, int height);
	void Iterate();
	Wavefunction wavefunction;
private:
	void Propagate(int index);
	int width;
	int height;
};

#endif