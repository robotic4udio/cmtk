#pragma once
/* 
This class will be used to interface OpenAI API. T-
he prompt will be passed to the API and the response will be returned, and printed. 
*/

// Include libcurl
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <functional>

class InterfaceGPT {

public:
    // Constructor
    InterfaceGPT();

    // Destructor
    ~InterfaceGPT() = default;

    // Function to send a prompt to the OpenAI API and return the response
    std::string sendPrompt(std::string prompt, std::string API_KEY, std::string model = "gpt-3.5-turbo");

    std::string generateMusic(std::string prompt, std::string API_KEY, std::string model = "gpt-3.5-turbo");

    // Write function
    static size_t WriteFunction(void *ptr, size_t size, size_t nmemb, std::string *data);

private:



};