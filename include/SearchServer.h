//
// Created by alex on 24.01.2024.
//
#include <cstddef>
#include <vector>
#include <regex>
#include <set>
#include "InvertedIndex.h"

#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H


struct RelativeIndex{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
public:
/*
* @param idx в конструктор класса передаётся ссылка на класс InvertedIndex,
* чтобы SearchServer мог узнать частоту слов встречаемых в запросе
*/
    SearchServer(InvertedIndex& idx) : _index(idx){};
    ~SearchServer(){std::cout << "Destructor\n";}
/*
Метод обработки поисковых запросов @param queries_input поисковые запросы
взятые из файла requests.json
@return возвращает отсортированный список релевантных ответов для заданных запросов
*/
    std::map<int, std::vector<RelativeIndex>> search(const
                                                   std::vector<std::string>& queries_input);
    std::vector<std::vector<RelativeIndex>> searchTest(const std::vector<std::string>& queries_input);
private:
    InvertedIndex _index;
};


#endif //SEARCH_ENGINE_SEARCHSERVER_H
