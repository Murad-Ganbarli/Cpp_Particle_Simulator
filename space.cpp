#include "space.h"
#include "constants.h"
#include "particle.h"
#include <algorithm>
#include <math.h>
#include <iostream>

Space::Space(double width, double height, double depth)
    : width_(width), height_(height), depth_(depth) {
    // Initialize electric and magnetic fields to zero initially
    electricField_.resize(3, 0.0);
    magneticField_.resize(3, 0.0);
}

void Space::setParticles(const std::vector<Particle>& particles) {
    particles_ = particles;
}

// Implement other member functions in the correct order
void Space::updateParticles(std::vector<Particle>& particles, double timeStep) const {
    for (auto& particle : particles) {
        updateParticlePosition(particle, timeStep);
        updateParticleVelocity(particle, timeStep);
        updateParticleAcceleration(particles, particle);

    }
}

void Space::updateParticlePosition(Particle& particle, double timeStep) const {
    // Calculate new position based on velocity and timeStep
    std::vector<double> newPosition = particle.getPosition();
    for (size_t i = 0; i < 3; ++i) {
        newPosition[i] += particle.getVelocity()[i] * timeStep;
    }
    particle.setPosition(newPosition);
}

void Space::updateParticleVelocity(Particle& particle, double timeStep) const {
    // Update velocity based on electric and magnetic fields
    // This is a simplified example; you may need a more sophisticated approach
    std::vector<double> electricForce = calculateElectricForce(particles, particle);
    std::vector<double> magneticForce = calculateMagneticForce(particles, particle);

    std::vector<double> totalForce = calculateTotalForce(electricForce, magneticForce);
    
    std::vector<double> acceleration = calculateAcceleration(totalForce, particle);

    std::vector<double> newVelocity(particle.getVelocity().size());
    for (std::size_t i = 0; i < particle.getVelocity().size(); ++i) {
        newVelocity[i] = particle.getVelocity()[i] + acceleration[i] * timeStep;
    }

    particle.setVelocity(newVelocity);
}

void Space::updateParticleAcceleration(const std::vector<Particle>& particles, Particle& particle) const {
    // Calculate acceleration based on electric and magnetic fields
    // This is a simplified example; you may need a more sophisticated approach
    std::vector<double> electricForce = calculateElectricForce(particles, particle);
    std::vector<double> magneticForce = calculateMagneticForce(particles, particle);

    std::vector<double> totalForce = calculateTotalForce(electricForce, magneticForce);
    std::vector<double> acceleration = calculateAcceleration(totalForce, particle);

    particle.setAcceleration(acceleration);
}

std::vector<double> Space::calculateElectricForce(const std::vector<Particle>& particles, const Particle& calculationPoint) const {
    std::vector<double> electricField(electricField_.size(), 0.0);

    for (const auto& particle : particles) {
        if (&particle != &calculationPoint) {
            std::vector<double> positionDifference = vectorSubtraction(particle.getPosition(), calculationPoint.getPosition());
            double distanceSquared = vectorDotProduct(positionDifference, positionDifference);

            for (size_t i = 0; i < 3; ++i) {
                electricField[i] += particle.getCharge() / (4.0 * Constants::getPi() * Constants::getVacuumPermittivity() * distanceSquared) * positionDifference[i] / sqrt(distanceSquared);
            }
        }
    }

    return electricField;
}

std::vector<double> Space::calculateMagneticForce(const std::vector<Particle>& particles, const Particle& calculationPoint) const {
    std::vector<double> magneticField(magneticField_.size(), 0.0);

    for (const auto& particle : particles) {
        if (&particle != &calculationPoint) {
            std::vector<double> positionDifference = vectorSubtraction(particle.getPosition(), calculationPoint.getPosition());
            double distanceSquared = vectorDotProduct(positionDifference, positionDifference);

            // Assuming constant velocity for simplicity
            std::vector<double> crossProduct = vectorCrossProduct(particle.getVelocity(), positionDifference);

            for (size_t i = 0; i < 3; ++i) {
                magneticField[i] += particle.getCharge() / (4.0 * Constants::getPi() * distanceSquared) * crossProduct[i] / (sqrt(distanceSquared));
            }
        }
    }

    return magneticField;
}

std::vector<double> Space::vectorSubtraction(const std::vector<double>& a, const std::vector<double>& b) const {
    std::vector<double> result(a.size());
    std::transform(a.begin(), a.end(), b.begin(), result.begin(), std::minus<double>());
    return result;
}

double Space::vectorDotProduct(const std::vector<double>& a, const std::vector<double>& b) const {
    if (a.size() != b.size()) {
        // Handle the error as needed
        // For example, throw an exception or return a default value
        return 0.0; // Adjust the default value based on your requirements
    }

    double result = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }

    return result;
}

std::vector<double> Space::vectorCrossProduct(const std::vector<double>& a, const std::vector<double>& b) const {
    std::vector<double> result(3);
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
    return result;
}

std::vector<double> Space::calculateTotalForce(const std::vector<double>& electricForce,
                                              const std::vector<double>& magneticForce) const {
    std::vector<double> totalForce;
    totalForce.reserve(electricForce.size());  // Reserve space to avoid reallocation

    for (std::size_t i = 0; i < electricForce.size(); ++i) {
        totalForce.push_back(electricForce[i] + magneticForce[i]);
    }

    return totalForce;
}

std::vector<double> Space::calculateAcceleration(const std::vector<double>& totalForce,
                                                 const Particle& particle) const {
    std::vector<double> acceleration;
    acceleration.reserve(totalForce.size());  // Reserve space to avoid reallocation

    for (const auto& force : totalForce) {
        acceleration.push_back(force / particle.getMass());
    }

    return acceleration;
}


const std::vector<double>& Space::getElectricField() const {
    return electricField_;
}

const std::vector<double>& Space::getMagneticField() const {
    return magneticField_;
}

const std::vector<Particle>& Space::getParticles() const {
    return particles_;
}