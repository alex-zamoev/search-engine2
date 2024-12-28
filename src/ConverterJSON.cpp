//
// Created by alex on 11.10.2023.
//
#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include "../include/ConverterJSON.h"
#include <iterator>


using json = nlohmann::json;

ConverterJSON::ConverterJSON() {
    std::ifstream config_file("../config.json");
    if (!config_file) {
            throw std::runtime_error("config file is missing");
    }
    config_file >> config_json;
    auto it_config = config_json.find("config");
    if (it_config == config_json.end()) {
            throw std::runtime_error("config file is empty");
    }
    config_file.close();

    std::ofstream answers;
    answers.open("answers.json", std::ios_base::out | std::ios_base::trunc);
    answers.close();
}

std::vector<std::vector<std::string>> ConverterJSON::GetTextDocuments(){
    std::string line;
    std::vector<std::vector<std::string>> fullContent;
    std::vector<std::string> contentFile;
    auto it_files = config_json.find("files");
    auto t = it_files.value();
    for (auto it : t)
    {
        std::cout << it << std::endl;
        std::ifstream in(it);
         contentFile.clear();
        if (in.is_open())
        {
            while(!in.eof())
            {
                getline(in, line);
                contentFile.push_back(line);
            }
        }
        fullContent.push_back(contentFile);
    }
    return fullContent;
}

int ConverterJSON::GetResponsesLimit(){
    auto it_config = config_json.find("config");
    auto t = it_config.value();
    auto it_max = t.find("max_responses");
    return it_max.value();
}

std::vector<std::string> ConverterJSON::GetRequests(){
    std::vector<std::string> requests;
    std::ifstream request_file("../requests.json");
    request_file >> requests_json;
    auto it_request = requests_json.find("requests");
    auto t = it_request.value();
    for (auto it : t){
        requests.push_back(it);
    }
    return requests;
}

int ConverterJSON::GetNumRequests() {
    int n{0};
    std::vector<std::string> requests;
    std::ifstream request_file("../requests.json");
    request_file >> requests_json;
    auto it_request = requests_json.find("requests");
    auto t = it_request.value();
    for (auto it : t){
        n++;
    }
    return n;
}

void ConverterJSON::putAnswers(std::map<int, std::vector<RelativeIndex>> answers){
    std::ofstream outFile("../answers.json", std::ios_base::trunc);
    std::map<int,std::vector<RelativeIndex>>::iterator it;
    std::string request = "";
    int numRequests = GetNumRequests();

    for(int i = 0; i < numRequests; i++){
        request = "request" + std::to_string(i);
        if (answers.find(i) == answers.end()) {
            answers_json[request]="false";
        } else {
            answers_json[request]["result"]="true";
            for(auto &t : answers[i]){
                   answers_json[request]["relevance"].push_back(json::object({{"doc_id", t.doc_id}, {"rank", t.rank}}));
            }
           }
        request = "";
    }
    outFile << answers_json;
    outFile.close();
}

json ConverterJSON::GetConfig(){
    auto it_config = config_json.find("config");
    auto t = it_config.value();
    return t;
}
