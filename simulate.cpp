#include <fstream>
#include <iostream>
#include <cmath>
#include "particle.h"
#include "Space.h"
#include <chrono>
#include <iomanip>
void writeParticleDynamicsToCSV(const std::string& filename, double dt, double duration, int fps, const Space& space) {
    // Open the file for writing
    std::ofstream outputFile(filename);
    outputFile << std::fixed << std::setprecision(10); // Set precision for output
    outputFile << std::scientific; // Use scientific notation
    std::cout << "CSV Size: " << (long long)space.getParticles().size() * fps * duration << " Lines "
              << "(approximately " << space.getParticles().size() * fps * duration / 1024 << " KBs)." /*<<"Estimated Time : "<< 3.5e-5*duration/dt <<" seconds."*/<< std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    // Write header
    outputFile << "Time,ParticleID,PositionX,PositionY,PositionZ\n";
    // Simulate particle dynamics and accumulate data
    for (double t = 0; t <= duration; t += dt) {
        std::vector<Particle> particles = space.getParticles();
        space.updateParticles(particles, dt);

        // Check if the current time is a multiple of the frame duration
        if (std::fmod(t, 1.0 / fps) < dt) {
            for (const auto& particle : particles) {
                outputFile << t << ","
                            << particle.getId() << ","
                            << particle.getPosition()[0] << ","
                            << particle.getPosition()[1] << ","
                            << particle.getPosition()[2] << "\n";
                //std::cout << "Time: " << t << ", Particle ID: " << particle.getId() << std::endl;
            }
        }
    }
    // Stop measuring time
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration_seconds = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

    // Print the time taken
    std::cout << "Time taken: " << duration_seconds.count() << " seconds\n";
}

void writeParticleDynamicsToJSON(const std::string& filename, double dt, double duration, int fps, const Space& space) {
    // Open the file for writing
    std::ofstream outputFile(filename);
    outputFile << std::fixed << std::setprecision(10); // Set precision for output
    outputFile << std::scientific; // Use scientific notation
    
    auto start = std::chrono::high_resolution_clock::now();

    // Write the JSON header
    outputFile << "[\n";

    // Simulate particle dynamics and accumulate data

    std::vector<Particle> particles = space.getParticles();
    space.updateParticles(particles, dt);
    outputFile << "\n  {\n";
    outputFile << "    \"Time\": " << 0.0 << ",\n";
    outputFile << "    \"Particles\": [\n";
    for (size_t i = 0; i < particles.size(); ++i) {
        const auto& particle = particles[i];

        // Write particle data to JSON
        outputFile << "      {\n";
        outputFile << "        \"ParticleID\": " << particle.getId() << ",\n";
        outputFile << "        \"Position\": {\n";
        outputFile << "          \"X\": " << particle.getPosition()[0] << ",\n";
        outputFile << "          \"Y\": " << particle.getPosition()[1] << ",\n";
        outputFile << "          \"Z\": " << particle.getPosition()[2] << "\n";
        outputFile << "        }\n";

        if (i < particles.size() - 1) {
            outputFile << "      },\n";
        } else {
            outputFile << "      }\n";
        }
    }

    outputFile << "    ]\n";
    outputFile << "  }\n";

    for (double t = dt; t <= duration; t += dt) {
        space.updateParticles(particles, dt);

        // Check if the current time is a multiple of the frame duration
        if (std::fmod(t, 1.0 / fps) < dt) {
            outputFile << ",\n  {\n";
            outputFile << "    \"Time\": " << t << ",\n";
            outputFile << "    \"Particles\": [\n";

            for (size_t i = 0; i < particles.size(); ++i) {
                const auto& particle = particles[i];

                // Write particle data to JSON
                outputFile << "      {\n";
                outputFile << "        \"ParticleID\": " << particle.getId() << ",\n";
                outputFile << "        \"Position\": {\n";
                outputFile << "          \"X\": " << particle.getPosition()[0] << ",\n";
                outputFile << "          \"Y\": " << particle.getPosition()[1] << ",\n";
                outputFile << "          \"Z\": " << particle.getPosition()[2] << "\n";
                outputFile << "        }\n";

                if (i < particles.size() - 1) {
                    outputFile << "      },\n";
                } else {
                    outputFile << "      }\n";
                }
            }

            outputFile << "    ]\n";
            outputFile << "  }\n";
        }
    }

    // Write the JSON footer
    outputFile << "]\n";

    // Stop measuring time
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration_seconds = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

    // Print the time taken
    std::cout << "Time taken: " << duration_seconds.count() << " seconds\n";
}
