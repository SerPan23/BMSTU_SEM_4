#include <iostream>

#include "./list/list.h"

int main()
{
    std::cout << "List 1\n";
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(4);
    std::cout << list1 << std::endl;

    std::cout << "List 2\n";
    List<int> list2(list1);
    std::cout << list2 << std::endl;

    std::cout << "List 3\n";
    int arr[] = {3, 2, 1};
    List<int> list3(arr, 3);
    std::cout << list3 << std::endl;

    std::cout << "List 4\n";
    List<int> list4 = {6, 7, 8, 9, 10, 11};
    std::cout << list4 << std::endl;

    std::cout << "List 5\n";
    auto first = list4.begin();
    auto end = list4.begin() + 2;

    List<int> list5(first, end);
    std::cout << list5 << std::endl;

    std::cout << "List 6\n";
    auto first_2 = list4.cbegin() + 1;
    auto end_2 = list4.cbegin() + 2;

    List<int> list6(first_2, end_2);
    std::cout << list6 << std::endl;

    std::cout << "\nTry create list with negative size:\n";
    try
    {
        List<int> list_tmp_1(arr, -1);
    }
    catch (InvalidSize &error)
    {
        std::cout << error.what();
    }

    std::cout << "\n------------------\n";
    std::cout << "Test methods\n";

    std::cout << "Is empty (list6): " << list6.empty() << std::endl;

    std::cout << "After clear method: ";
    list6.clear();
    std::cout << "Is empty (list6): " << list6.empty() << std::endl;

    std::cout << "\nPush front element\n";
    list6.push_front(100);
    std::cout << list6 << std::endl;
    std::cout << "Push front List 1\n";
    list6.push_front(list1);
    std::cout << list6 << std::endl;

    std::cout << "\nPush back element\n";
    list6.push_back(1000);
    std::cout << list6 << std::endl;
    std::cout << "Push back List 1\n";
    list6.push_back(list1);
    std::cout << list6 << std::endl;

    std::cout << "\nInsert in head\n";
    list6.insert(list6.begin(), 999);
    std::cout << list6 << std::endl;
    std::cout << "Insert in 3d pos\n";
    list6.insert(list6.begin() + 3, 999);
    std::cout << list6 << std::endl;
    std::cout << "Insert in 3d pos List 1\n";
    list6.insert(list6.begin() + 3, list1);
    std::cout << list6 << std::endl;

    std::cout << "\nInsert const in head\n";
    list5.insert(list5.cbegin(), 777);
    std::cout << list5 << std::endl;
    std::cout << "Insert const in 3d pos\n";
    list5.insert(list5.cbegin() + 3, 555);
    std::cout << list5 << std::endl;
    std::cout << "Insert const in 3d List 1\n";
    list5.insert(list5.cbegin() + 3, list1);
    std::cout << list5 << std::endl;

    std::cout << "\nPop front\n";
    std::cout << "Before:\n";
    std::cout << list6 << std::endl;
    list6.pop_front();
    std::cout << "After:\n";
    std::cout << list6 << std::endl;

    std::cout << "\nPop back\n";
    std::cout << "Before:\n";
    std::cout << list6 << std::endl;
    list6.pop_back();
    std::cout << "After:\n";
    std::cout << list6 << std::endl;

    std::cout << "\nErase second element\n";
    std::cout << "Before:\n";
    std::cout << list6 << std::endl;
    list6.erase(list6.begin() + 1);
    std::cout << "After:\n";
    std::cout << list6 << std::endl;

    std::cout << "\nTry pop from empty list:\n";
    list6.clear();
    try
    {
        list6.pop_back();
    }
    catch (EmptyList &error)
    {
        std::cout << error.what();
    }

    std::cout << "\nReverse\n";
    std::cout << "Before:\n";
    std::cout << list2 << std::endl;
    list2.reverse();
    std::cout << "After:\n";
    std::cout << list2 << std::endl;

    std::cout << "\nMerge\n";
    list2.merge(list1);
    list2.merge(1999);
    std::cout << list2 << std::endl;

    std::cout << "\nTest operators\n";
    List<int> list_t_1 = {1, 2, 3, 4};
    List<int> list_t_2 = {5, 6};

    std::cout << "First list:\n";
    std::cout << list_t_1 << std::endl;
    std::cout << "Second list:\n";
    std::cout << list_t_2 << std::endl;

    std::cout << "\noperator =: ";
    list_t_1 = list_t_2;
    std::cout << list_t_1 << std::endl;

    std::cout << "\noperator += : ";
    list_t_1 += list_t_2;
    list_t_1 += 10;
    std::cout << list_t_1 << std::endl;

    std::cout << "\noperator +: ";
    list_t_1 = list1 + list_t_2;
    list_t_1 += 100;
    std::cout << list_t_1 << std::endl;

    std::cout << "\nTest cmp operators\n";
    List<int> list_cmp_1 = {1, 2, 3, 4};
    List<int> list_cmp_2 = {1, 2, 3, 4};

    std::cout << "\noperator ==: ";
    if (list_cmp_1 == list_cmp_2)
        std::cout << "Equal\n";
    else
        std::cout << "Not Equal\n";

    list_cmp_1.pop_back();

    std::cout << "\noperator !=: ";
    if (list_cmp_1 != list_cmp_1)
        std::cout << "Not Equal\n";
    else
        std::cout << "Equal\n";

    std::cout << "\nTest iterators:\n";
    List<int> test_list = {1, 2, 3};

    std::cout << "Change second value by iterator:\n";
    std::cout << "Before:\n";
    std::cout << test_list << std::endl;

    auto iter = test_list.begin();
    iter++;
    *iter = 500;
    std::cout << "After:\n";
    std::cout << test_list << std::endl;
    // This dont work, because by const iterator we can't change value
    // auto const_iter = test_list.cbegin();
    // const_iter++;
    // *const_iter = 900;
    auto iter_2 = test_list.begin();
    ++iter_2;

    std::cout << "\noperator ==: ";
    if (iter == iter_2)
        std::cout << "Equal\n";
    else
        std::cout << "Not Equal\n";

    std::cout << "\noperator !=: ";
    if (iter != iter_2)
        std::cout << "Not Equal\n";
    else
        std::cout << "Equal\n";

    std::cout << "\nTest bool in iterator: ";
    std::cout << (bool)test_list.begin() << std::endl;

    return 0;
}