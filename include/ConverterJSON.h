//
// Created by alex on 11.10.2023.
//
#include <vector>
#include <string>
#include <iterator>
#include "nlohmann/json.hpp"
#include "SearchServer.h"


using json = nlohmann::json;

#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H

class ConverterJSON {
public:
    ConverterJSON();

    int GetResponsesLimit();
    std::vector<std::vector<std::string>> GetTextDocuments();

// Метод получения запросов из файла requests.json
    std::vector<std::string> GetRequests();
    int GetNumRequests();
/**
* Положить в файл answers.json результаты поисковых запросов
*/
    void putAnswers(std::map<int, std::vector<RelativeIndex>> answers);
/*
* Получить конфиг из файла config.json
*/
    json GetConfig();

private:
    json config_json;
    json answers_json;
    json requests_json;
};


#endif //SEARCH_ENGINE_CONVERTERJSON_H
