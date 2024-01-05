// In main.cpp
#include "space.h"
#include "simulate.h"
#include "particle.h"
#include "pyrunner.h"

int main() {
    double dt = 1e-12;
    double duration = 1e-3;

    std::vector<Particle> particles = {
        { -1.602e-19, 9.109e-31, {0, 0, 0}, {0, 0, 0}, 1, {0, 0, 0} },
        { -1.602e-19, 2 * 9.109e-31, {0, 0, 0}, {1e-6, 0, 0.5e-6}, 2, {0, 0, 0} },
        { 1.602e-19, 3 * 9.109e-31, {0, 0, 0}, {0.5e-6, 1e-6, 0}, 3 , {0, 0, 0} }
    };

    // Create an instance of the Space class
    Space space( 0, 0, 0);

    // Set particles in the Space
    space.setParticles(particles);

    int fps = 30;
    
    std::string sent_data_json = "sent2.json";
    std::string tablename = "test_animation_of_table2";
    std::string retrieved_data_json = "test_animation_ret2.json";

    const char* sent_data_json_cstr = sent_data_json.c_str();
    const char* tablename_cstr = tablename.c_str();
    const char* retrieved_data_json_cstr = retrieved_data_json.c_str();

    writeParticleDynamicsToJSON(sent_data_json, dt, duration,fps, space);
    sendDataToDatabase(tablename_cstr, sent_data_json_cstr);
    retrieveDataFromDatabase(tablename_cstr, retrieved_data_json_cstr);

    animateParticles(retrieved_data_json_cstr , "50");
    return 0;
}

