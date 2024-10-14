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
	void iterate();
	Wavefunction wavefunction;
private:
	void propagate(int index);
	int width = 0;
	int height = 0;
};

#endif