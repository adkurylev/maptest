#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <unordered_map>
#include <chrono>

int main()
{
    std::vector<std::string> vector;
    std::string allChars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 mersenne(rd());

    typedef std::chrono::microseconds ms;

    for (int i = 0; i < 5000000; ++i)
    {
        std::string str;
        size_t size = mersenne() % 11 + 10;
        for (int j = 0; j < size; ++j)
        {
            str.push_back(allChars[mersenne() % allChars.length()]);
        }
        vector.push_back(str);
    }

    std::map<int, std::string> testMap;
    for (int i = 0; i < 1000000; ++i)
        testMap.insert({i, vector[i]});

    std::unordered_map<int, std::string> testUMap;
    for (int i = 0; i < 1000000; ++i)
        testUMap.insert({i, vector[i]});

    std::cout << "Following data will be presented in triples: first element is "
                 "i = index of inserting element, second - duration of insertion of elements from 1000001 to i, third - "
                 "duration of insertion of i-string.\n";

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1000001; i < 5000000; ++i)
    {
        if (i % 100000 == 0)
        {
            std::cout << i << " ";
            auto currentTime = std::chrono::high_resolution_clock::now();
            ms micsec = std::chrono::duration_cast<ms>(currentTime - start);
            std::cout << micsec.count() << " ";
            currentTime = std::chrono::high_resolution_clock::now();
            testMap.insert({i, vector[i]});
            micsec = std::chrono::duration_cast<ms>(std::chrono::high_resolution_clock::now() - currentTime);
            std::cout << micsec.count() << " ";
            std::cout << std::endl;
            continue;
        }
        testMap.insert({i, vector[i]});
    }

    std::cout << std::endl << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 1000001; i < 5000000; ++i)
    {
        if (i % 100000 == 0)
        {
            std::cout << i << " ";
            auto currentTime = std::chrono::high_resolution_clock::now();
            ms micsec = std::chrono::duration_cast<ms>(currentTime - start);
            std::cout << micsec.count() << " ";
            currentTime = std::chrono::high_resolution_clock::now();
            testUMap.insert({i, vector[i]});
            micsec = std::chrono::duration_cast<ms>(std::chrono::high_resolution_clock::now() - currentTime);
            std::cout << micsec.count() << " ";
            std::cout << std::endl;
            continue;
        }
        testUMap.insert({i, vector[i]});
    }

    return 0;
}