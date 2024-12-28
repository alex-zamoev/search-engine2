//
// Created by alex on 24.01.2024.
//

#include "../include/SearchServer.h"
#include <cstring>

std::map<int, std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input){
    std::map<int, std::vector<RelativeIndex>> rltIndx;
    std::vector<RelativeIndex> temp;
    std::vector<Entry> entry;
    std::unordered_set<std::string> uniqWords;
    int numDocs = _index.GetNumDocs();
    int absRel[numDocs] = {};
    std::multimap<int, int> results;
    std::regex sepre(R"([\s,\.\!\-,]+)");
    size_t ind;
    float mrank;
    int maxi = 0;

    for (auto & t : queries_input){
        std::cout << t << std::endl;
    }
    std::cout << "--------end requests--------" << std::endl;

    int numReq = 0;
    for (auto & t : queries_input){

        //Разбиваем файл  с запросом на отдельные уникальные слова
        std::sregex_token_iterator iter(t.begin(), t.end(), sepre, -1), end;
        for (; iter != end; ++iter) uniqWords.insert(*iter);

        //Считаем абсолютную релевантность
        for (auto & t : uniqWords){
            entry = _index.GetWordCount(t);
            if(entry.size()>0){
                for(auto &tt : entry){
                    absRel[int(tt.doc_id)] += tt.count;
                }
            }
        }

        for(int i = 0; i < numDocs; i++){
            if(absRel[i] > 0) results.insert({absRel[i], i});
        }

        if(results.size() > 0){
            std::multimap<int, int>::reverse_iterator it = results.rbegin();
            maxi = it->first;
            while (it != results.rend()) {
                ind = it->second;
                mrank = (float) it->first / maxi;
                temp.push_back({ind , mrank});
                it++;
            }
         } else temp.clear();

        if(temp.size() > 0) rltIndx.insert(std::pair<int, std::vector<RelativeIndex>>(numReq, temp));

        numReq++;
        uniqWords.clear();
        entry.clear();
        std::memset(absRel, 0 , sizeof(absRel));
        results.clear();
        temp.clear();
    }

    for(auto & t : rltIndx){
        std::cout << t.first << ", {" << std::endl;
        for(auto & tt : t.second){
            std::cout << tt.doc_id << ", " << tt.rank << std::endl;
        }
        std::cout << "}" << std::endl;
        std::cout << "--------next--------" << std::endl;
    }
    return rltIndx;
};

std::vector<std::vector<RelativeIndex>> SearchServer::searchTest(const std::vector<std::string>& queries_input){
    std::vector<std::vector<RelativeIndex>> rltIndx;
    std::vector<RelativeIndex> temp;
    std::vector<Entry> entry;
    std::unordered_set<std::string> uniqWords;
    int numDocs = _index.GetNumDocs();
    int absRel[numDocs] = {};
    std::multimap<int, int> results;
    std::regex sepre(R"([\s,\.\!\-,]+)");
    size_t ind;
    float mrank;
    int maxi = 0;

    for (auto & t : queries_input){
        std::cout << t << std::endl;
    }
    std::cout << std::endl;

    for (auto & t : queries_input){

        //Разбиваем файл  с запросом на отдельные уникальные слова
        std::sregex_token_iterator iter(t.begin(), t.end(), sepre, -1), end;
        for (; iter != end; ++iter) uniqWords.insert(*iter);

        for (auto & t : uniqWords){
            entry = _index.GetWordCount(t);
            if(entry.size()>0){
                for(auto &tt : entry){
                    std::cout << t << ", " << "{" << tt.doc_id << ", " << tt.count << "}" << std::endl;
                    absRel[int(tt.doc_id)] += tt.count;
                }
            }
        }
        for(int i = 0; i < numDocs; i++){
            if(absRel[i] > 0) results.insert({absRel[i], i});
        }

        for(auto & t: results){
            std::cout << t.first << ", " << t.second << std::endl;
        }

        if(results.size() > 0){
            std::multimap<int, int>::reverse_iterator it = results.rbegin();
            maxi = it->first;

            while (it != results.rend()) {
                //std::cout << it->first << ", " << it->second << std::endl;
                ind = it->second;
                mrank = (float) it->first / maxi;
                std::cout << "Rank= " << mrank << std::endl;
                temp.push_back({ind , mrank});
                it++;
            }

            std::cout << "Multimap direct:" << std::endl;
            for(std::multimap<int, int>::iterator it = results.begin(); it != results.end(); ++it){
                std::cout << it->first << ", " << it->second << std::endl;
            }

        } else temp.clear();

        if(temp.size() > 0) rltIndx.push_back(temp);

        uniqWords.clear();
        temp.clear();
        entry.clear();
        std::memset(absRel, 0 , sizeof(absRel));
        results.clear();
    }

    for(auto & t : rltIndx){
        for(auto & tt : t){
            std::cout << tt.doc_id << ", " << tt.rank << std::endl;
        }
        std::cout << "--------next--------" << std::endl;
    }

    return rltIndx;
};