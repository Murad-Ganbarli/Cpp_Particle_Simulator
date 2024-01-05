#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include <string>

class Particle {
public:
    Particle(double charge, double mass, const std::vector<double>& initialVelocity,
             const std::vector<double>& initialPosition, int id,
             const std::vector<double>& initialAcceleration);

    // Getters and setters
    double getCharge() const;
    void setCharge(double newCharge);

    double getMass() const;
    void setMass(double newMass);

    const std::vector<double>& getPosition() const;
    void setPosition(const std::vector<double>& newPosition);

    const std::vector<double>& getVelocity() const;
    void setVelocity(const std::vector<double>& newVelocity);

    const std::vector<double>& getAcceleration() const;  // New getter for acceleration
    void setAcceleration(const std::vector<double>& newAcceleration);  // New setter for acceleration

    int getId() const;
    void setId(int newId);

private:
    double charge;
    double mass;
    std::vector<double> velocity;
    std::vector<double> position;
    std::vector<double> acceleration;  // New member for acceleration
    int id; // Change std::int to int
};

#endif // PARTICLE_H
