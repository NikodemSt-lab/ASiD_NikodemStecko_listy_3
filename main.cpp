#include "arraylist.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <sstream>

void test_constructors() {
    std::cout << "Testowanie konstruktorow i operatorow przypisania..." << std::endl;

    ArrayList<int> list1;
    assert(list1.empty());
    assert(!list1.full());
    assert(list1.size() == 0);
    assert(list1.max_size() == 10);

    ArrayList<int> list2(5);
    assert(list2.empty());
    assert(!list2.full());
    assert(list2.size() == 0);
    assert(list2.max_size() == 5);

    for (int i = 1; i <= 5; ++i) {
        list2.push_back(i * 10);
    }
    assert(list2.full());
    assert(list2.size() == 5);

    ArrayList<int> list3(list2);
    assert(list3.size() == list2.size());
    assert(list3.max_size() == list2.max_size());
    for (std::size_t i = 0; i < list2.size(); ++i) {
        assert(list3[i] == list2[i]);
    }
    list3[0] = 999;
    assert(list2[0] == 10);
    assert(list3[0] == 999);

    ArrayList<int> list4;
    list4 = list2;
    assert(list4.size() == list2.size());
    assert(list4.max_size() == list2.max_size());
    for (std::size_t i = 0; i < list2.size(); ++i) {
        assert(list4[i] == list2[i]);
    }
    list4 = list4;
    assert(list4.size() == 5);
    assert(list4[0] == 10);

    ArrayList<int> list5(std::move(list3));
    assert(list5.size() == 5);
    assert(list5[0] == 999);
    assert(list3.empty());
    assert(list3.size() == 0);
    assert(list3.max_size() == 0);

    ArrayList<int> list6;
    list6 = std::move(list5);
    assert(list6.size() == 5);
    assert(list6[0] == 999);
    assert(list5.empty());
    assert(list5.size() == 0);
    assert(list5.max_size() == 0);

    std::cout << "Testy konstruktorow i przypisania zakonczone pomyslnie." << std::endl;
}

void test_push_pop_front_back() {
    std::cout << "Testowanie push_front, push_back, pop_front, pop_back..." << std::endl;

    ArrayList<int> list(6);

    list.push_back(20);
    list.push_back(30);
    list.push_front(10);
    assert(list.size() == 3);
    assert(list.front() == 10);
    assert(list.back() == 30);
    assert(list[0] == 10);
    assert(list[1] == 20);
    assert(list[2] == 30);

    int val = 40;
    list.push_back(std::move(val));
    list.push_front(0);
    assert(list.size() == 5);
    assert(list.front() == 0);
    assert(list.back() == 40);

    list.push_back(50);
    assert(list.full());
    assert(list.size() == 6);
    assert(list.back() == 50);

    list.front() = 5;
    assert(list.front() == 5);
    assert(list[0] == 5);

    list.back() = 55;
    assert(list.back() == 55);
    assert(list[5] == 55);

    const ArrayList<int>& const_list = list;
    assert(const_list.front() == 5);
    assert(const_list.back() == 55);
    assert(const_list[0] == 5);
    assert(const_list[5] == 55);

    list.pop_front();
    assert(list.size() == 5);
    assert(list.front() == 10);
    assert(!list.full());

    list.pop_back();
    assert(list.size() == 4);
    assert(list.back() == 40);

    list.pop_front();
    list.pop_back();
    list.pop_front();
    list.pop_back();
    assert(list.empty());
    assert(list.size() == 0);

    std::cout << "Testy push/pop front/back zakonczone pomyslnie." << std::endl;
}

void test_clear_and_empty() {
    std::cout << "Testowanie clear, empty, full..." << std::endl;

    ArrayList<int> list(4);
    assert(list.empty());

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    assert(list.full());

    list.clear();
    assert(list.empty());
    assert(list.size() == 0);
    assert(!list.full());

    list.push_back(100);
    assert(list.size() == 1);
    assert(list.front() == 100);

    std::cout << "Testy clear i empty zakonczone pomyslnie." << std::endl;
}

void test_indexing_and_search() {
    std::cout << "Testowanie operator[] oraz index()..." << std::endl;

    ArrayList<int> list(5);
    list.push_back(11);
    list.push_back(22);
    list.push_back(33);
    list.push_back(44);

    assert(list[0] == 11);
    assert(list[1] == 22);
    assert(list[2] == 33);
    assert(list[3] == 44);

    list[1] = 222;
    assert(list[1] == 222);

    assert(list.index(11) == 0);
    assert(list.index(222) == 1);
    assert(list.index(33) == 2);
    assert(list.index(44) == 3);
    assert(list.index(999) == -1);

    std::cout << "Testy indeksowania i wyszukiwania zakonczone pomyslnie." << std::endl;
}

void test_insert_and_erase() {
    std::cout << "Testowanie insert() oraz erase()..." << std::endl;

    ArrayList<int> list(7);
    list.push_back(10);
    list.push_back(30);
    list.push_back(50);

    list.insert(1, 20);
    assert(list.size() == 4);
    assert(list[0] == 10);
    assert(list[1] == 20);
    assert(list[2] == 30);
    assert(list[3] == 50);

    list.insert(0, 5);
    assert(list.size() == 5);
    assert(list.front() == 5);
    assert(list[1] == 10);

    list.insert(list.size(), 60);
    assert(list.size() == 6);
    assert(list.back() == 60);

    int x = 40;
    list.insert(4, std::move(x));
    assert(list.size() == 7);
    assert(list.full());
    assert(list[4] == 40);

    list.erase(4);
    assert(list.size() == 6);
    assert(list[3] == 30);
    assert(list[4] == 50);

    list.erase(0);
    assert(list.size() == 5);
    assert(list.front() == 10);

    list.erase(list.size() - 1);
    assert(list.size() == 4);
    assert(list.back() == 50);

    std::cout << "Testy insert i erase zakonczone pomyslnie." << std::endl;
}

void test_reverse_and_sort() {
    std::cout << "Testowanie reverse() oraz sort()..." << std::endl;

    ArrayList<int> list(6);
    list.push_back(40);
    list.push_back(10);
    list.push_back(50);
    list.push_back(20);
    list.push_back(30);

    list.reverse();
    assert(list[0] == 30);
    assert(list[1] == 20);
    assert(list[2] == 50);
    assert(list[3] == 10);
    assert(list[4] == 40);

    list.reverse();
    assert(list[0] == 40);
    assert(list[1] == 10);
    assert(list[2] == 50);
    assert(list[3] == 20);
    assert(list[4] == 30);

    list.sort();
    assert(list[0] == 10);
    assert(list[1] == 20);
    assert(list[2] == 30);
    assert(list[3] == 40);
    assert(list[4] == 50);

    list.push_back(60);
    list.reverse();
    assert(list[0] == 60);
    assert(list[1] == 50);
    assert(list[2] == 40);
    assert(list[3] == 30);
    assert(list[4] == 20);
    assert(list[5] == 10);

    std::cout << "Testy reverse i sort zakonczone pomyslnie." << std::endl;
}

void test_merge() {
    std::cout << "Testowanie merge()..." << std::endl;

    ArrayList<int> list1(10);
    list1.push_back(10);
    list1.push_back(30);
    list1.push_back(50);
    list1.push_back(70);

    ArrayList<int> list2(5);
    list2.push_back(20);
    list2.push_back(40);
    list2.push_back(60);

    list1.merge(list2);

    assert(list1.size() == 7);
    assert(list2.empty());
    assert(list2.size() == 0);

    for (std::size_t i = 0; i < list1.size(); ++i) {
        assert(list1[i] == static_cast<int>((i + 1) * 10));
    }

    ArrayList<int> empty_list(3);
    list1.merge(empty_list);
    assert(list1.size() == 7);

    list1.merge(list1);
    assert(list1.size() == 7);

    ArrayList<int> empty_target(10);
    ArrayList<int> source(3);
    source.push_back(1);
    source.push_back(2);
    source.push_back(3);
    empty_target.merge(source);
    assert(empty_target.size() == 3);
    assert(empty_target[0] == 1 && empty_target[1] == 2 && empty_target[2] == 3);
    assert(source.empty());

    std::cout << "Testy merge zakonczone pomyslnie." << std::endl;
}

void test_strings() {
    std::cout << "Testowanie ArrayList z typem std::string..." << std::endl;

    ArrayList<std::string> str_list(5);
    str_list.push_back("world");
    str_list.push_front("hello");
    str_list.push_back("aisd");

    assert(str_list.size() == 3);
    assert(str_list.front() == "hello");
    assert(str_list.back() == "aisd");
    assert(str_list[1] == "world");

    assert(str_list.index("world") == 1);
    assert(str_list.index("missing") == -1);

    str_list.sort();
    assert(str_list[0] == "aisd");
    assert(str_list[1] == "hello");
    assert(str_list[2] == "world");

    str_list.clear();
    assert(str_list.empty());

    std::cout << "Testy dla std::string zakonczone pomyslnie." << std::endl;
}

void test_stream_and_display() {
    std::cout << "Testowanie operator<< oraz display()..." << std::endl;

    ArrayList<int> list(5);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    std::ostringstream oss;
    oss << list;
    assert(oss.str() == "1 2 3 ");

    std::cout << "Wynik display: ";
    list.display();

    std::cout << "Testy strumienia i display zakonczone pomyslnie." << std::endl;
}

int main() {
    std::cout << "Uruchamianie testow dla ADT ArrayList..." << std::endl;

    test_constructors();
    test_push_pop_front_back();
    test_clear_and_empty();
    test_indexing_and_search();
    test_insert_and_erase();
    test_reverse_and_sort();
    test_merge();
    test_strings();
    test_stream_and_display();

    std::cout << "Wszystkie testy zakonczone pomyslnie!" << std::endl;

    return 0;
}
