// simulate.h
#ifndef SIMULATE_H
#define SIMULATE_H

#include <fstream>
#include <iostream>
#include <cmath>
#include "particle.h"
#include "Space.h"
#include <chrono>

void writeParticleDynamicsToCSV(const std::string& filename, double dt, double duration, int fps, const Space& space);
void writeParticleDynamicsToJSON(const std::string& filename, double dt, double duration, int fps, const Space& space);

#endif 
