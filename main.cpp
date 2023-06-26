#include "counter_of_unique_words.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2)
        return -1;

    Counter_of_unique_words counter;
    cout << counter.countUnique(argv[1]) << endl;

    return 0;
}
