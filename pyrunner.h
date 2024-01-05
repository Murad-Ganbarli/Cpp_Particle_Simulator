#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>

// Function to read Python path from JSON file
std::string readPythonPathFromJson(const std::string& configPath);

// Function to execute Python script with parameters
int executePythonScript(const std::string& scriptPath, const std::string& functionName, const std::vector<std::string>& parameters);

// Function to send data to the database using the Python script
int sendDataToDatabase(const char* tableName, const char* jsonDataPath);

// Function to retrieve data from the database using the Python script
int retrieveDataFromDatabase(const char* tableName, const char* jsonOutputPath);

int animateParticles(const char* json_data_path, const char* interval);
#endif // DATABASE_H
