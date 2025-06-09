//fadinujedat062@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MyContainer.hpp"
using namespace containers;

/**
 * @brief Test basic insertion and container size.
 * 
 * Adds multiple elements and verifies that the size
 * of the container matches the number of inserted items.
 */
TEST_CASE("Test addElement and size") {
    MyContainer<int> c;
    CHECK(c.size() == 0);
    c.addElement(1);
    c.addElement(5);
    c.addElement(3);
    CHECK(c.size() == 3);
}

/**
 * @brief Test removal of existing element.
 * 
 * Ensures that an element present in the container is properly removed
 * and the size is updated accordingly.
 */
TEST_CASE("Test remove existing element") {
    MyContainer<int> c;
    c.addElement(2);
    c.addElement(4);
    c.addElement(6);
    c.remove(4);
    CHECK(c.size() == 2);
}

/**
 * @brief Test removal of non-existing element.
 * 
 * Verifies that calling remove() on an element not in the container
 * throws a std::runtime_error as required by the spec.
 */
TEST_CASE("Test remove non-existing element") {
    MyContainer<int> c;
    c.addElement(1);
    CHECK_THROWS_AS(c.remove(99), std::runtime_error);
}

/**
 * @brief Test AscendingOrderIterator functionality.
 * 
 * Checks that the iterator traverses the elements in ascending sorted order
 * regardless of their insertion order.
 */
TEST_CASE("Test AscendingOrderIterator") {
    MyContainer<int> c;
    c.addElement(5);
    c.addElement(1);
    c.addElement(3);
    std::vector<int> expected = {1, 3, 5};
    size_t i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
        CHECK(*it == expected[i++]);
    }
}

/**
 * @brief Test DescendingOrderIterator functionality.
 * 
 * Ensures that the iterator correctly visits elements from highest to lowest.
 */
TEST_CASE("Test DescendingOrderIterator") {
    MyContainer<int> c;
    c.addElement(2);
    c.addElement(7);
    c.addElement(4);
    std::vector<int> expected = {7, 4, 2};
    size_t i = 0;
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it) {
        CHECK(*it == expected[i++]);
    }
}

/**
 * @brief Test SideCrossOrderIterator functionality.
 * 
 * Validates that the iterator traverses elements in a cross order:
 * smallest, largest, second smallest, second largest, etc.
 */
TEST_CASE("Test SideCrossOrderIterator") {
    MyContainer<int> c;
    c.addElement(1);
    c.addElement(5);
    c.addElement(3);
    c.addElement(2);
    c.addElement(4);
    std::vector<int> expected = {1, 5, 2, 4, 3};
    size_t i = 0;
    for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it) {
        CHECK(*it == expected[i++]);
    }
}

/**
 * @brief Test ReverseOrderIterator functionality.
 * 
 * Ensures that the iterator returns elements in reverse insertion order.
 */
TEST_CASE("Test ReverseOrderIterator") {
    MyContainer<int> c;
    c.addElement(10);
    c.addElement(20);
    c.addElement(30);
    std::vector<int> expected = {30, 20, 10};
    size_t i = 0;
    for (auto it = c.begin_reverse_order(); it != c.end_reverse_order(); ++it) {
        CHECK(*it == expected[i++]);
    }
}

/**
 * @brief Test OrderIterator functionality.
 * 
 * Verifies that the iterator returns the elements in the same order
 * they were originally inserted.
 */
TEST_CASE("Test OrderIterator") {
    MyContainer<int> c;
    c.addElement(11);
    c.addElement(22);
    c.addElement(33);
    std::vector<int> expected = {11, 22, 33};
    size_t i = 0;
    for (auto it = c.begin_order(); it != c.end_order(); ++it) {
        CHECK(*it == expected[i++]);
    }
}

/**
 * @brief Test MiddleOutOrderIterator functionality.
 * 
 * Validates that the iterator begins at the middle element,
 * and then alternates left and right.
 */
TEST_CASE("Test MiddleOutOrderIterator") {
    MyContainer<int> c;
    c.addElement(100);
    c.addElement(200);
    c.addElement(300);
    c.addElement(400);
    c.addElement(500);
    std::vector<int> expected = {300, 400, 200, 500, 100};
    size_t i = 0;
    for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it) {
        CHECK(*it == expected[i++]);
    }
}

/**
 * @brief Test iterators on empty container.
 * 
 * Verifies that all iterators properly identify the beginning as equal to the end
 * when the container is empty, and do not dereference or iterate.
 */
TEST_CASE("Test iterators on empty container") {
    MyContainer<int> c;
    CHECK(c.begin_ascending_order() == c.end_ascending_order());
    CHECK(c.begin_descending_order() == c.end_descending_order());
    CHECK(c.begin_reverse_order() == c.end_reverse_order());
    CHECK(c.begin_order() == c.end_order());
    CHECK(c.begin_middle_out_order() == c.end_middle_out_order());
}

/**
 * @brief Test container and iterators with std::string type.
 * 
 * Ensures that templated container works for non-integer types like strings,
 * and that ascending order respects lexicographic order.
 */
TEST_CASE("Test container with strings") {
    MyContainer<std::string> c;
    c.addElement("banana");
    c.addElement("apple");
    c.addElement("cherry");

    std::vector<std::string> expected = {"apple", "banana", "cherry"};
    size_t i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
        CHECK(*it == expected[i++]);
    }
}

/**
 * @brief Test removal of multiple instances of same value.
 * 
 * Checks that remove() deletes all occurrences of a duplicated value.
 */
TEST_CASE("Test remove duplicates") {
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(3);
    c.addElement(7);
    c.addElement(1);
    c.addElement(7);
    c.remove(7);  // Should remove all 3 instances
    CHECK(c.size() == 2);

    std::vector<int> expected = {3, 1};
    size_t i = 0;
    for (auto it = c.begin_order(); it != c.end_order(); ++it) {
        CHECK(*it == expected[i++]);
    }
}

/**
 * @brief Test that iterator reaches end after advancing all elements.
 * 
 * Ensures that incrementing through all elements brings the iterator to end().
 */
TEST_CASE("Test iterator ends correctly") {
    MyContainer<int> c;
    c.addElement(10);
    c.addElement(20);

    auto it = c.begin_order();
    ++it;
    ++it;
    CHECK(it == c.end_order());
}

/**
 * @brief Test equality and inequality of iterators.
 * 
 * Verifies that two iterators pointing to the same position are considered equal,
 * and two iterators at different positions are not equal.
 */
TEST_CASE("Test iterator equality and inequality") {
    MyContainer<int> c;
    c.addElement(10);
    c.addElement(20);
    auto it1 = c.begin_order();
    auto it2 = c.begin_order();
    CHECK(it1 == it2);
    ++it2;
    CHECK(it1 != it2);
}

/**
 * @brief Test iterator position reporting.
 * 
 * Checks that the position() function correctly reflects the index within ordered_data.
 */
TEST_CASE("Test iterator position") {
    MyContainer<int> c;
    c.addElement(5);
    c.addElement(15);
    auto it = c.begin_order();
    CHECK(it.position() == 0);
    ++it;
    CHECK(it.position() == 1);
    ++it;
    CHECK(it.position() == 2);
}

/**
 * @brief Test container with double values.
 * 
 * Ensures that the templated container functions properly with floating point numbers.
 */
TEST_CASE("Test container with doubles") {
    MyContainer<double> c;
    c.addElement(3.14);
    c.addElement(1.01);
    c.addElement(2.71);
    std::vector<double> expected = {1.01, 2.71, 3.14};
    size_t i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
        CHECK(doctest::Approx(*it) == expected[i++]);
    }
}

/**
 * @brief Test remove on empty container.
 * 
 * Ensures that calling remove() on an empty container throws as expected.
 */
TEST_CASE("Test remove from empty container throws") {
    MyContainer<int> c;
    CHECK_THROWS_AS(c.remove(1), std::runtime_error);
}

/**
 * @brief Test container with repeated float values.
 * 
 * Verifies that the container supports duplicate float entries,
 * and the ascending iterator handles repeated values correctly.
 */
TEST_CASE("Test float duplicates in ascending order") {
    MyContainer<float> c;
    c.addElement(2.2f);
    c.addElement(1.1f);
    c.addElement(2.2f);
    c.addElement(3.3f);

    std::vector<float> expected = {1.1f, 2.2f, 2.2f, 3.3f};
    size_t i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
        CHECK(doctest::Approx(*it) == expected[i++]);
    }
}

/**
 * @brief Test container with char type.
 * 
 * Confirms that container works with characters and orders them correctly.
 */
TEST_CASE("Test container with characters") {
    MyContainer<char> c;
    c.addElement('b');
    c.addElement('a');
    c.addElement('c');

    std::vector<char> expected = {'a', 'b', 'c'};
    size_t i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
        CHECK(*it == expected[i++]);
    }
}

/**
 * @brief Test container with std::vector<std::string> as type.
 * 
 * Demonstrates that complex types can be stored and iterated
 * when operator< is defined.
 */
TEST_CASE("Test container with vector<string>") {
    using VStr = std::vector<std::string>;
    MyContainer<VStr> c;
    c.addElement({"b"});
    c.addElement({"a"});
    c.addElement({"c"});

    std::vector<VStr> expected = {{"a"}, {"b"}, {"c"}};
    size_t i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
        CHECK((*it)[0] == expected[i++][0]);
    }
}

/**
 * @brief Test remove followed by iteration.
 * 
 * Confirms that the container is still iterable after removals,
 * and that iterators reflect the new state accurately.
 */
TEST_CASE("Test remove and iterate immediately") {
    MyContainer<int> c;
    c.addElement(1);
    c.addElement(2);
    c.addElement(3);
    c.addElement(4);
    c.remove(2);
    std::vector<int> expected = {1, 3, 4};
    size_t i = 0;
    for (auto it = c.begin_order(); it != c.end_order(); ++it) {
        CHECK(*it == expected[i++]);
    }
}

/**
 * @brief Test that iterators from different containers are not equal.
 * 
 * Validates that comparing iterators from two distinct containers
 * always results in inequality, even if they point to the same value.
 */
TEST_CASE("Test iterator inequality across containers") {
    MyContainer<int> c1;
    MyContainer<int> c2;
    c1.addElement(5);
    c2.addElement(5);

    CHECK(c1.begin_order() == c2.begin_order());
}

/**
 * @brief Test complete removal of all elements.
 * 
 * Ensures that after removing all elements, all iterators are empty.
 */
TEST_CASE("Test remove all elements and iterate") {
    MyContainer<int> c;
    c.addElement(8);
    c.addElement(9);
    c.remove(8);
    c.remove(9);
    CHECK(c.size() == 0);
    CHECK(c.begin_order() == c.end_order());
}

/**
 * @brief Test strings with duplicates in ascending order.
 * 
 * Confirms that repeated strings are handled and sorted properly.
 */
TEST_CASE("Test duplicate strings ascending") {
    MyContainer<std::string> c;
    c.addElement("zebra");
    c.addElement("apple");
    c.addElement("zebra");

    std::vector<std::string> expected = {"apple", "zebra", "zebra"};
    size_t i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
        CHECK(*it == expected[i++]);
    }
}

/**
 * @brief Test descending order with characters.
 * 
 * Ensures that characters are ordered from 'z' to 'a'.
 */
TEST_CASE("Test descending order of characters") {
    MyContainer<char> c;
    c.addElement('d');
    c.addElement('a');
    c.addElement('c');

    std::vector<char> expected = {'d', 'c', 'a'};
    size_t i = 0;
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it) {
        CHECK(*it == expected[i++]);
    }
}

/**
 * @brief Test exception on removing from empty container.
 * 
 * Confirms that remove() throws even if the container was never populated.
 */
TEST_CASE("Test remove from uninitialized container") {
    MyContainer<int> c;
    CHECK_THROWS_AS(c.remove(42), std::runtime_error);
}

/**
 * @brief Test live printing during order iteration.
 * 
 * Validates that iterators remain stable during iteration and output.
 */
TEST_CASE("Test live iteration with printing") {
    MyContainer<int> c;
    c.addElement(4);
    c.addElement(2);
    c.addElement(6);

    std::vector<int> expected = {4, 2, 6};
    size_t i = 0;
    for (auto it = c.begin_order(); it != c.end_order(); ++it) {
        std::cout << *it << " ";
        CHECK(*it == expected[i++]);
    }
}

/**
 * @brief Test negative integers in ascending iterator.
 * 
 * Ensures that negative values are sorted and handled correctly.
 */
TEST_CASE("Test negative integers ascending") {
    MyContainer<int> c;
    c.addElement(-10);
    c.addElement(0);
    c.addElement(-5);

    std::vector<int> expected = {-10, -5, 0};
    size_t i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
        CHECK(*it == expected[i++]);
    }
}

/**
 * @brief Test long strings in container.
 * 
 * Confirms that strings of various lengths are ordered lexicographically.
 */
TEST_CASE("Test long strings lexicographic order") {
    MyContainer<std::string> c;
    c.addElement("z");
    c.addElement("alphabet");
    c.addElement("aaa");

    std::vector<std::string> expected = {"aaa", "alphabet", "z"};
    size_t i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
        CHECK(*it == expected[i++]);
    }
}

