#include "app-window.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include <ostream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

slint::SharedString get_new_password(int words_num);
std::string get_word_from_json(int words_num);

int main(int argc, char **argv)
{
    auto ui = AppWindow::create();

    ui->on_request_generate_password([&]{
        ui->set_password(get_new_password(ui->get_words_num()));
    });

    ui->on_request_change_words_num([&] {
         ui->get_words_num();
    });

    ui->run();
    return 0;
}

slint::SharedString get_new_password(int words_num) {
    auto password = get_word_from_json(words_num);
    slint::SharedString result {password};
    return result;
}

std::string get_word_from_json(int words_num) {
    // Path to the JSON file
    const char* jsonFilePath = "../data/words_dictionary.json";

    // Open the JSON file
    FILE* fp = fopen(jsonFilePath, "r");
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