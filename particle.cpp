//particle.cpp
#include "particle.h"

// Constructor
Particle::Particle(double charge, double mass, const std::vector<double>& initialVelocity,
                   const std::vector<double>& initialPosition, int id,
                   const std::vector<double>& initialAcceleration)
    : charge(charge), mass(mass), velocity(initialVelocity),
      position(initialPosition), id(id), acceleration(initialAcceleration) {}


// Getters and setters
double Particle::getCharge() const {
    return charge;
}

void Particle::setCharge(double newCharge) {
    charge = newCharge;
}

double Particle::getMass() const {
    return mass;
}

void Particle::setMass(double newMass) {
    mass = newMass;
}

const std::vector<double>& Particle::getPosition() const {
    return position;
}

void Particle::setPosition(const std::vector<double>& newPosition) {
    position = newPosition;
}

const std::vector<double>& Particle::getVelocity() const {
    return velocity;
}

void Particle::setVelocity(const std::vector<double>& newVelocity) {
    velocity = newVelocity;
}

int Particle::getId() const {
    return id;
}

void Particle::setId(int newId) {
    id = newId;
}
const std::vector<double>& Particle::getAcceleration() const {
    return acceleration;
}

void Particle::setAcceleration(const std::vector<double>& newAcceleration) {
    acceleration = newAcceleration;
}
