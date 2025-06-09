//fadinujedat062@gmail.com
#include <iostream>
#include "MyContainer.hpp"
using namespace containers;

void print_section(const std::string& title) {
    std::cout << "\n==== " << title << " ====" << std::endl;
}

int main() {
    MyContainer<int> numbers;
    numbers.addElement(42);
    numbers.addElement(17);
    numbers.addElement(89);
    numbers.addElement(23);
    numbers.addElement(56);

    std::cout << "Container initialized with 5 numbers." << std::endl;
    std::cout << "Total elements: " << numbers.size() << std::endl;

    print_section("Ascending Order");
    for (auto it = numbers.begin_ascending_order(); it != numbers.end_ascending_order(); ++it)
        std::cout << *it << " ";

    print_section("Descending Order");
    for (auto it = numbers.begin_descending_order(); it != numbers.end_descending_order(); ++it)
        std::cout << *it << " ";

    print_section("Side Cross Order");
    for (auto it = numbers.begin_side_cross_order(); it != numbers.end_side_cross_order(); ++it)
        std::cout << *it << " ";

    print_section("Reverse Insertion Order");
    for (auto it = numbers.begin_reverse_order(); it != numbers.end_reverse_order(); ++it)
        std::cout << *it << " ";

    print_section("Insertion Order");
    for (auto it = numbers.begin_order(); it != numbers.end_order(); ++it)
        std::cout << *it << " ";

    print_section("Middle-Out Order");
    for (auto it = numbers.begin_middle_out_order(); it != numbers.end_middle_out_order(); ++it)
        std::cout << *it << " ";

    print_section("Removing 23 and printing Insertion Order again");
    numbers.remove(23);
    for (auto it = numbers.begin_order(); it != numbers.end_order(); ++it)
        std::cout << *it << " ";

    print_section("Done ✔\n");
    return 0;
}