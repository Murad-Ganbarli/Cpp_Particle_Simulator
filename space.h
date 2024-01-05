#ifndef SPACE_H
#define SPACE_H

#include <vector>
#include "particle.h"

class Space {
public:
    Space(double width, double height, double depth);


    void setParticles(const std::vector<Particle>& particles);
    void updateParticles(std::vector<Particle>& particles, double timeStep) const;

    const std::vector<double>& getElectricField() const;
    const std::vector<double>& getMagneticField() const;
    void updateParticlePosition(Particle& particle, double timeStep) const;
    void updateParticleVelocity(Particle& particle, double timeStep) const;
    void updateParticleAcceleration(const std::vector<Particle>& particles, Particle& particle) const;

    std::vector<double> calculateElectricForce(const std::vector<Particle>& particles, const Particle& calculationPoint) const;
    std::vector<double> calculateMagneticForce(const std::vector<Particle>& particles, const Particle& calculationPoint) const;
    std::vector<double> vectorSubtraction(const std::vector<double>& a, const std::vector<double>& b) const;
    double vectorDotProduct(const std::vector<double>& a, const std::vector<double>& b) const;
    std::vector<double> vectorCrossProduct(const std::vector<double>& a, const std::vector<double>& b) const;
    std::vector<double> calculateTotalForce(const std::vector<double>& electricForce, const std::vector<double>& magneticForce) const;
    std::vector<double> calculateAcceleration(const std::vector<double>& totalForce, const Particle& particle) const;
    const std::vector<Particle>& getParticles() const;
private:
    std::vector<Particle> particles;
    double width_;
    double height_;
    double depth_;
    std::vector<double> electricField_;
    std::vector<double> magneticField_;
    std::vector<Particle> particles_;
};

#endif // SPACE_H
