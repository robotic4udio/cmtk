#include "InterfaceGPT.h"

#define SYSTEM_PROMPT "You are a music composer. \
    You will return a JSON object with the following keys: \
    - chords: a list of chords in the progression in this format: [c, F6, c, G7] \
    - tempo: the tempo of the progression, in this format: 120 \
    the model will generate a chord progression and melody based on the prompt. \
    The returned JSON string should not contain any newlines or tabs. \
    The string should be a single line with no leading or trailing whitespace. \
    "

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
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFunction);

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
size_t InterfaceGPT::WriteFunction(void *ptr, size_t size, size_t nmemb, std::string *data)
{
    // Append the data to the string
    data->append((char *)ptr, size * nmemb);

    // Return the size
    return size * nmemb;
}




// Function to send a prompt to the OpenAI API and return the response
std::string InterfaceGPT::generateMusic(std::string prompt, std::string API_KEY, std::string model)
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
        std::string data = "{\"model\": \"" + model + "\", \"messages\": [{\"role\": \"system\", \"content\": \"" + SYSTEM_PROMPT + "\"},{\"role\": \"user\", \"content\": \"" + prompt + "\"}], \"temperature\": 0.7}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        // Set the write function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFunction);

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
