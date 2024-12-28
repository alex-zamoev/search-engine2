//
// Created by alex on 24.01.2024.
//
#include <cstddef>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <set>
#include <regex>
#include <mutex>
#include <thread>
//#include "ConverterJSON.h"
#include <utility>

#ifndef SEARCH_ENGINE_INVERTEDINDEX_H
#define SEARCH_ENGINE_INVERTEDINDEX_H

struct Entry {
    size_t doc_id, count;
// Данный оператор необходим для проведения тестовых сценариев
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};

class InvertedIndex {
public:
    InvertedIndex() = default;
/*
Обновить или заполнить базу документов, по которой будем совершать поиск
@param texts_input содержимое документов
*/
    void UpdateDocumentBase(std::vector<std::vector<std::string>> input_docs);
/*
Метод определяет количество вхождений слова word в загруженной базе документов
* @param word слово, частоту вхождений которого необходимо определить
* @return возвращает подготовленный список с частотой слов
*/
    std::vector<Entry> GetWordCount(const std::string& word);

    void Thread(int i, std::vector<std::string> txt);
    int GetNumDocs();
private:
    std::vector<std::string> docs; // список содержимого документов (уникальные слова)
    std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный    словарь
    int numDocs;
};

#endif //SEARCH_ENGINE_INVERTEDINDEX_H
