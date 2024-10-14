#pragma once

#ifndef WAVEFUNCTION_H
#define WAVEFUNCTION_H

#include <vector>
#include <map>
#include "Util.h"
#include <numeric>
#include <iostream>
#include <string>

class Wavefunction
{
public:
	Wavefunction();
	Wavefunction(int width, int height);
private:
	int width= 0;
	int height = 0;
};

#endif