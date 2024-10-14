#include "Wavefunction.h"

#include <ranges>


Wavefunction::Wavefunction()
= default;

Wavefunction::Wavefunction(int width, int height)
{
	this->width = width;
	this->height = height;
}