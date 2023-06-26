#ifndef COUNTER_OF_UNIQUE_WORDS_H
#define COUNTER_OF_UNIQUE_WORDS_H
#include <string>
#include <unordered_set>
#include <atomic>
#include <mutex>
#include <vector>

class Counter_of_unique_words
{

public:

    std::int64_t countUnique(const std::string& path);

private:

    void countWord(std::ifstream &file, const int index);

    std::mutex m1;

    std::atomic<bool> stop = false;

    std::vector<std::unordered_set<std::string>> unique_words_main;
};

#endif // COUNTER_OF_UNIQUE_WORDS_H
