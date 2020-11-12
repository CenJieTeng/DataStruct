#include <ctime>
#include <iostream>
#include <string>
#include <unordered_map>
#include "../DataStruct/HashTable.h"

int main(int argc, char *argv[])
{
    int not_nul = 0;
    if (argc > 1)
        not_nul = atoi(argv[1]);

    HashTable<std::string, std::string> table;
    table.ShowTable(not_nul);
    std::cout << "-------------------------" << std::endl;
    table.Insert("ab", "hello");
    table.ShowTable(not_nul);
    std::cout << "-------------------------" << std::endl;
    table.Insert("cd", "world");
    table.ShowTable(not_nul);
    std::cout << "-------------------------" << std::endl;
    table.Insert("111", "aaa");
    table.ShowTable(not_nul);
    std::cout << "-------------------------" << std::endl;
    table.Insert("222", "bbb");
    table.ShowTable(not_nul);
    std::cout << "-------------------------" << std::endl;
    table.Insert("333", "ccc");
    table.ShowTable(not_nul);

    for (auto iter = table.begin(); iter != table.end(); ++iter)
    {
        std::cout << *iter << std::endl;
        *iter = "new_" + *iter;
    }

    std::cout << "-------------------------" << std::endl;
    table.ShowTable(not_nul);

    std::cout << "\n----------------------------\n" << std::endl;

    int kRun = 1000 * 1000;

    std::unordered_map<int, int> table1;
    time_t start1 = clock();
    for (int i = 0; i < kRun; ++i)
    {
        static int bucket_count = table1.bucket_count();
        table1.insert(std::pair<int,int>(i % kRun, i));
        if (bucket_count != table1.bucket_count())
        {
            std::cout << "bucket_count " << bucket_count << " --> " << table1.bucket_count() << std::endl;
            bucket_count = table1.bucket_count();
        }
    }
    time_t end1 = clock();
    std::cout << table1.load_factor() << std::endl;
    std::cout << "factor " << table1.max_load_factor() << std::endl;
    std::cout << "unorder_map insert time: " << difftime(end1, start1) << " ms" << std::endl;

    {
        time_t start = clock();
        for (int i = 0; i < kRun; ++i)
        {
            table1.find(i);
        }
        time_t end = clock();
        std::cout << "unorder_map find time: " << difftime(end, start) << " ms" << std::endl;
    }

    {
        time_t start = clock();
        auto end_iter = table1.end();
        int count = 0;
        for (auto iter = table1.begin(); iter != end_iter; ++iter)
        {
            ++count;
        }
        time_t end = clock();
        std::cout << "count: " << count << std::endl;
        std::cout << "unorder_map iterator time: " << difftime(end, start) << " ms" << std::endl;
    }

    std::cout << "\n----------------------------\n" << std::endl;

    HashTable<int, int> table2(10, 1);
    time_t start2 = clock();
    for (int i = 0; i < kRun; ++i)
    {
        static int bucket_count = table2.bucket_count();
        table2.Insert(i % kRun, 1);
        if (bucket_count != table2.bucket_count())
        {
            std::cout << "bucket_count " << bucket_count << " --> " << table2.bucket_count() << std::endl;
            bucket_count = table2.bucket_count();
        }
    }
    time_t end2 = clock();
    std::cout << table2.load_factor() << std::endl;
    std::cout << "factor " << table2.max_load_factor() << std::endl;
    std::cout << "HashTable insert time: " << difftime(end2, start2) << " ms" << std::endl;
   
    {
        int result;
        time_t start = clock();
        for (int i = 0; i < kRun; ++i)
        {
            table2.Find(i, result);
        }
        time_t end = clock();
        std::cout << "HashTable find time: " << difftime(end, start) << " ms" << std::endl;
    }

    {
        time_t start = clock();
        auto end_iter = table2.end();
        int count = 0;
        for (auto iter = table2.begin(); iter != end_iter; ++iter)
        {
            ++count;
        }
        time_t end = clock();
        std::cout << "count: " << count << std::endl;
        std::cout << "HashTable iterator time: " << difftime(end, start) << " ms" << std::endl;
    }

    return 0;
}