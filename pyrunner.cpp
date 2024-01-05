#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Function to read Python path from JSON file
std::string readPythonPathFromJson(const std::string& configPath) {
    std::ifstream configFile(configPath);
    if (!configFile.is_open()) {
        std::cerr << "Error: Unable to open the JSON file." << std::endl;
        return "";
    }

    std::string jsonContent((std::istreambuf_iterator<char>(configFile)),
                             std::istreambuf_iterator<char>());

    // Search for the "python" key and then extract the "path" value
    size_t pythonKeyPos = jsonContent.find("\"python\"");
    size_t pathKeyPos = jsonContent.find("\"path\"", pythonKeyPos);
    size_t colonPos = jsonContent.find(":", pathKeyPos);
    size_t quotePos1 = jsonContent.find("\"", colonPos);
    size_t quotePos2 = jsonContent.find("\"", quotePos1 + 1);

    if (quotePos1 != std::string::npos && quotePos2 != std::string::npos) {
        return jsonContent.substr(quotePos1 + 1, quotePos2 - quotePos1 - 1);
    } else {
        std::cerr << "Error: Unable to extract Python path from the JSON file." << std::endl;
        return "";
    }
}

// Function to execute Python script with parameters
int executePythonScript(const std::string& scriptPath, const std::string& functionName, const std::vector<std::string>& parameters) {
    // Build the command to execute the Python script with parameters
    std::string command = readPythonPathFromJson("config.json");
    command += " ";
    command += scriptPath;
    command += " ";
    command += functionName;

    for (const auto& parameter : parameters) {
        command += " ";
        command += parameter;
    }
    //std::cout<< command<<std::endl;
    // Execute the Python script from C++
    int result = std::system(command.c_str());

    // Check if the execution was successful
    if (result == 0) {
        std::cout << "Python script executed successfully." << std::endl;
    } else {
        std::cerr << "Error: Failed to execute Python script." << std::endl;
    }

    return result;
}

// Function to send data to the database using the Python script
int sendDataToDatabase(const char* tableName, const char* jsonDataPath) {
    return executePythonScript("database.py", "send_data_to_db", {tableName, "config.json", jsonDataPath});
}

// Function to retrieve data from the database using the Python script
int retrieveDataFromDatabase(const char* tableName, const char* jsonOutputPath) {
    return executePythonScript("database.py", "retrieve_and_save_to_json", {tableName, "config.json", jsonOutputPath});
}

// Function to animate particle motion
int animateParticles(const char* json_data_path , const char* interval) {
    return executePythonScript("animate.py" , "animate_particles" , {json_data_path , interval});
}

#ifdef MAIN_TEST
int main() {
    // Replace these paths and names with the actual ones
    const std::string tableName = "test4";
    const std::string jsonDataPath = "cpp2.json";

    // Run the Python script with parameters to send data
    int resultSend = sendDataToDatabase(tableName.c_str(), jsonDataPath.c_str());

    // Check the result
    if (resultSend == 0) {
        std::cout << "Send data function executed successfully." << std::endl;
    } else {
        std::cerr << "Error during execution of send data function." << std::endl;
        return resultSend;
    }

    // Run the Python script with parameters to retrieve data
    const std::string jsonOutputPath = "retrieved_data.json";
    int resultRetrieve = retrieveDataFromDatabase(tableName.c_str(), jsonOutputPath.c_str());

    // Check the result
    if (resultRetrieve == 0) {
        std::cout << "Retrieve data function executed successfully." << std::endl;
    } else {
        std::cerr << "Error during execution of retrieve data function." << std::endl;
    }

    return resultRetrieve;
}
#endif
