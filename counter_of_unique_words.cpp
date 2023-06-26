#include "counter_of_unique_words.h"
#include <thread>
#include <fstream>
#include <sstream>

std::int64_t Counter_of_unique_words::countUnique(const std::string& path)
{
    std::unordered_set<std::string> unique_words;
    std::ifstream file(path);

    if(file.fail())
        return -1;

    auto threads_num = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    threads.reserve(threads_num);

    unique_words_main.resize(threads_num);

    for(int i = 0; i < threads_num; ++i)
    {
        threads.push_back(std::thread([&, i]()
                                            {

                                                countWord(file, i);

                                            }));
    }

    for (auto &t : threads)
    {
        t.join();
    }

    for(int i = 0; i < unique_words_main.size(); ++i)
    {
        unique_words.insert(unique_words_main[i].begin(), unique_words_main[i].end());
    }

    file.close();

    return unique_words.size();
}

void Counter_of_unique_words::countWord(std::ifstream &file, const int index)
{
    while(!stop)
    {
        std::string words;
        {
            std::lock_guard l(m1);
            std::getline(file, words);
        }

        if(words.empty())
        {
            stop = true;
            return;
        }

        std::stringstream ss(std::move(words));
        std::string word;

        while(ss >> word)
        {
            unique_words_main[index].insert(std::move(word));
        }
    }
}
