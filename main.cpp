// Implementing required libarys
#include <iostream>
#include <curl/curl.h>

// Function to send a message to a Discord webhook
void sendDiscordMessage(const std::string& webhookUrl, const std::string& message) {
    // cURL initialization
    CURL* curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set webhook URL
        curl_easy_setopt(curl, CURLOPT_URL, webhookUrl.c_str());

        // Set payload as JSON
        std::string jsonPayload = R"({"content":")" + message + "\"}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload.c_str());

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;

        // Cleanup
        curl_easy_cleanup(curl);
    }

    // Cleanup global cURL data
    curl_global_cleanup();
}

int main() {
    // Discord webhook URL
    std::string webhookUrl = "YOUR_WEBHOOK_URL_HERE";

    // Message to be sent
    std::string message = "Hello from my C++ application!";

    // Send the message
    sendDiscordMessage(webhookUrl, message);

    return 0;
}
