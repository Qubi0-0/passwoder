#ifndef JSONWORDS_H_
#define JSONWORDS_H_

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include <ostream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>


namespace JsonHandler {

std::string get_word_from_json(int words_num, const std::string& jsonFilePath) {
    // Open the JSON file
    FILE* fp = fopen(jsonFilePath.c_str(), "r");
    if (!fp) {
        std::cerr << "Could not open file: " << jsonFilePath << std::endl;
        return "";
    }

    // Read the JSON file
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    // Parse the JSON content
    rapidjson::Document document;
    document.ParseStream(is);
    fclose(fp);

    // Check if parsing was successful
    if (document.HasParseError()) {
        std::cerr << "Error parsing JSON file: " << jsonFilePath << std::endl;
        return "";
    }

    // Extract the keys (words) from the JSON object
    std::vector<std::string> words;
    for (auto& m : document.GetObject()) {
        words.push_back(m.name.GetString());
    }

    // Randomly select words
    if (!words.empty()) {
        std::srand(std::time(nullptr)); // use current time as seed for random generator
        std::string password;
        for (int i = 0; i < words_num; ++i) {
            int randomIndex = std::rand() % words.size();
            password += words[randomIndex];
            if (i < words_num - 1) {
                password += " "; // Add space between words
            }
        }
        return password;
    } else {
        std::cerr << "No words found in JSON file" << std::endl;
        return "";
    }
}

slint::SharedString get_new_password(int words_num, const slint::SharedString& wordset) {
    std::string jsonFilePath;
    if (wordset == "Common Words") {
        jsonFilePath = "data/common_words.json"; 
    } else if (wordset == "Words Dictionary") {
        jsonFilePath = "data/words_dictionary.json";
    } else {
        jsonFilePath = "data/common_words.json"; // Default
    }

    auto password = get_word_from_json(words_num, jsonFilePath);
    slint::SharedString result {password};
    return result;
}

} // namespace JsonHandler

#endif // JSONWORDS_H_