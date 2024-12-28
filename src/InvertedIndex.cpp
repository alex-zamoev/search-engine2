//
// Created by alex on 24.01.2024.
//

#include "../include/InvertedIndex.h"

std::mutex mtx;

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word){
    std::vector<Entry> freq;
    for (auto & element : freq_dictionary){
        if(word == element.first) {
            for (const auto &v : element.second){
                freq.push_back({v.doc_id , v.count});
            }
        }
    }
    return freq;
}

void InvertedIndex::UpdateDocumentBase(std::vector<std::vector<std::string>> input_docs){
    //Заполняем вектор docs уникальными словами
    docs.clear();
    std::unordered_set<std::string> uniqueWords;
    std::regex sepre(R"([\s,\.\!\-,]+)");
    for(auto  & tf : input_docs) {
        for(auto & ts : tf){
            std::sregex_token_iterator iter(ts.begin(), ts.end(), sepre, -1), end;
            for (; iter != end; ++iter) uniqueWords.insert(*iter);
        }
    }

    for (auto & t : uniqueWords){
        docs.push_back(t);
    }
// Запускаем потоки для индексирования
    numDocs = input_docs.size();
    std::thread threads[numDocs];
    int i = 0;
    for(auto  & tf : input_docs) {
        threads[i] = std::thread(&InvertedIndex::Thread, this ,i, tf);
        threads[i].join();
        i++;
    }
}

void InvertedIndex::Thread(int i, std::vector<std::string> txt){
    Entry entry;
    //Разбиваем файл на отдельные слова
    std::vector<std::string> words;
    std::regex sepre(R"([\s,\.\!\-,]+)");
    for (auto & t : txt){
 /*       const char *temp = t.c_str();
        char * str = (char*)temp;
        char *res1 = std::strtok (str," ,.+-!?"); // во втором параметре указаны разделитель (пробел, запятая, точка, тире)

        while (res1 != NULL)                         // пока есть лексемы
        {
            words.push_back(res1);
            res1 = strtok (NULL, " ,.-!?");
        }*/
        std::sregex_token_iterator iter(t.begin(), t.end(), sepre, -1), end;
        for (; iter != end; ++iter) words.push_back(*iter);

    }

//Записываем в словарь
    mtx.lock();
    for(auto &un : docs){
        int f = 0;
        for(auto  &w: words){
            if (un == w) f++;
        }
        if(f != 0) {
            entry.doc_id = i;
            entry.count = f;
            freq_dictionary[un].push_back(entry);
        }
    }
    std::cout << std::endl;
    mtx.unlock();
}

int InvertedIndex::GetNumDocs(){
    return numDocs;
}
