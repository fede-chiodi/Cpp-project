#include <iostream>
#include "linkedList.hpp"

int main() {
    LinkedList<int> list;

    list.push_at_head(10);
    list.push_at_head(20);
    list.push_at_head(30);
    std::cout << "After pushing at head: ";
    list.print_list();

    list.push_at_tail(40);
    std::cout << "After pushing at tail: ";
    list.print_list();

    list.push_at_position(2, 25);
    std::cout << "After pushing at position 2: ";
    list.print_list();

    list.pop();
    std::cout << "After popping (head): ";
    list.print_list();

    list.delete_at_tail();
    std::cout << "After deleting at tail: ";
    list.print_list();

    list.delete_at_position(1);
    std::cout << "After deleting at position 1: ";
    list.print_list();

    int result = list.search_and_return([](int data) { return data == 25; });
    std::cout << "Search and return for 25: " << result << std::endl;

    result = list.at([]() { return 1; });
    std::cout << "Element at position 1: " << result << std::endl;

    bool found = list.search([](int data) { return data == 10; });
    std::cout << "Search for 10: " << (found ? "Found" : "Not Found") << std::endl;

    LinkedList<int> mappedList = list.map([](int data) {
        if (data % 2 == 0) {
            return data * 2;
        } else {
            return data * 3 + 10;
        }
    });
    std::cout << "After map (complex transformation): ";
    mappedList.print_list();

    LinkedList<int> filteredList = list.filter([](int data) { 
        return data % 2 == 0 && data % 3 == 0;  
    });
    std::cout << "After filter (even and divisible by 3): ";
    filteredList.print_list();

    int foundElement = list.find([](int data) { return data == 20; });
    std::cout << "Find element 20: " << foundElement << std::endl;

    list.reverse();
    std::cout << "After reversing: ";
    list.print_list();

    std::cout << "List size: " << list.list_size() << std::endl;

    list.push_at_tail(20);
    list.push_at_tail(30);
    list.unique();
    std::cout << "After removing duplicates: ";
    list.print_list();

    return 0;
}
