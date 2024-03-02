#include "../include/InterfaceGPT.h"

// Constructor
InterfaceGPT::InterfaceGPT() 
{
    // Init curl
    curl_global_init(CURL_GLOBAL_ALL);
}


// Function to send a prompt to the OpenAI API and return the response
std::string InterfaceGPT::sendPrompt(std::string prompt, std::string API_KEY, std::string model)
{
    // Create a string to store the response
    std::string response;

    // Create a CURL object
    CURL *curl = curl_easy_init();

    // If the CURL object was created successfully
    if (curl)
    {
        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
        

        // Set the headers
        struct curl_slist *headers = NULL;
        std::string authorizationHeader = "Authorization: Bearer " + API_KEY;
        headers = curl_slist_append(headers, authorizationHeader.c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set the prompt
        std::string data = "{\"model\": \"" + model + "\", \"messages\": [{\"role\": \"user\", \"content\": \"" + prompt + "\"}], \"temperature\": 0.7}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        // Set the write function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);

        // Set the response
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        CURLcode res = curl_easy_perform(curl);

        // If the request was not successful
        if (res != CURLE_OK)
        {
            // Print an error message
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    // Return the response
    return response;
}

// Write function
size_t InterfaceGPT::writeFunction(void *ptr, size_t size, size_t nmemb, std::string *data)
{
    // Append the data to the string
    data->append((char *)ptr, size * nmemb);

    // Return the size
    return size * nmemb;
}

