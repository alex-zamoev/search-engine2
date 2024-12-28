#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <stdexcept>
#include "../include/ConverterJSON.h"
#include "../include/InvertedIndex.h"
#include "../include/SearchServer.h"



int main() {

    std::vector<std::vector<std::string>> content;
    std::vector<std::string> requests;

    std::unique_ptr<ConverterJSON>  json;
    std::unique_ptr<InvertedIndex> indx;
    std::unique_ptr<SearchServer> ss;

    try{
        json = std::make_unique<ConverterJSON>();
    }
    catch(const std::runtime_error& re){
        std::cerr << re.what() << std::endl;
        return 0;
    }

    indx = std::make_unique<InvertedIndex>();

    auto t = json->GetConfig();
    auto it_name = t.find("name");
    auto it_version = t.find("version");
    std::cout << it_name.value() << ". Version: " << it_version.value() << std::endl;

    int operation{-2};
    do{
        std::cout << "Enter operation (1 - show requests, 2 - indexing BD, 3 - print files, 4 - search, 0 - exit): ";
        std::cin >> operation;
        switch(operation){
            case 1:
                std::cout << "Show requests: " << std::endl;
                requests = json->GetRequests();
                for (auto & element : requests)
                {
                    std::cout << element << std::endl;
                }
                break;
            case 2:
                std::cout << "Indexing: " << std::endl;
                content = json->GetTextDocuments();
                indx->UpdateDocumentBase(content);
                break;
            case 3:
                std::cout << "Show files content: " << std::endl;
                content = json->GetTextDocuments();
                for (auto t : content){
                    for (auto element : t)
                    {
                        std::cout << element << std::endl;
                    }
                }
                break;
            case 4:
                std::cout << "Search: " << std::endl;
                ss = std::make_unique<SearchServer>(*indx);
                json->putAnswers(ss->search(requests));
                break;
            case 0:
               std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Incorrect input. Try again, please." << std::endl;
                break;
        }
    }while(operation != 0);

    return 0;
}

