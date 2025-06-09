//fadinujedat062@gmail.com
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace containers {
    /**
     * @brief A generic container that supports custom iteration orders.
     * 
     * Provides insertion, removal, and multiple ways to iterate
     * over the elements using various strategies (ascending, descending, etc.).
     */
    template<typename T = int>
    class MyContainer {
    private:
        std::vector<T> data;///< Internal storage for container elements


        /**
         * @brief Base class for all iterators in MyContainer.
         * 
         * Manages a copy of the ordered data and traversal index.
         * Provides common operator implementations for all derived iterators.
         */
        template<typename IterType>
        class BaseIterator {
        protected:
            std::vector<IterType> ordered_data;
            size_t index = 0;

        public:
            /**
             * @brief Default constructor.
             */
            BaseIterator() = default;

             /**
             * @brief Dereference operator.
             * 
             * @return const IterType& Reference to the current element.
             * @throws std::out_of_range if attempting to dereference end().
             */
            const IterType& operator*() const {
                if (index >= ordered_data.size()) {
                    throw std::out_of_range("Dereferencing end() iterator");
                }
                return ordered_data[index];
            }
            /**
             * @brief Prefix increment operator.
             * 
             * Advances the iterator to the next element.
             * @return BaseIterator& Reference to the updated iterator.
             */
            BaseIterator& operator++() {
                ++index;
                return *this;
            }

            /**
             * @brief Inequality comparison operator.
             * 
             * @param other Another iterator to compare with.
             * @return true if iterators point to different positions.
             */
            bool operator!=(const BaseIterator& other) const {
                return index != other.index;
            }

             /**
             * @brief Equality comparison operator.
             * 
             * @param other Another iterator to compare with.
             * @return true if iterators point to the same position.
             */
            bool operator==(const BaseIterator& other) const {
                return index == other.index;
            }

            /**
             * @brief Assignment operator.
             * 
             * @param other Iterator to assign from.
             * @return BaseIterator& Reference to this.
             */
            BaseIterator& operator=(const BaseIterator& other) {
                if (this != &other) {
                    this->ordered_data = other.ordered_data;
                    this->index = other.index;
                }
                return *this;
            }

             /**
             * @brief Returns the current position within the ordered data.
             * 
             * @return size_t Index of the iterator.
             */
            size_t position() const {
                return index;
            }
        };

    public:
        /**
         * @brief Default constructor.
         */
        MyContainer() = default;
        /**
         * @brief Adds a new element to the container.
         * 
         * @param value The element to insert.
         */
        void addElement(const T& value) {
            data.push_back(value);
        }

        /**
         * @brief Removes all occurrences of a given value from the container.
         * 
         * @param value The value to remove.
         * @throws std::runtime_error if the value is not found.
         */
        void remove(const T& value) {
            auto it = std::remove(data.begin(), data.end(), value);
            if (it == data.end()) {
                throw std::runtime_error("Item not found in container");
            }
            data.erase(it, data.end());
        }

        /**
         * @brief Returns the number of elements in the container.
         * 
         * @return size_t Current size of the container.
         */
        size_t size() const {
            return data.size();
        }

        /**
         * @brief Stream insertion operator.
         * 
         * Outputs the contents of the container in standard format.
         * @param os Output stream.
         * @param container The container to print.
         * @return std::ostream& The output stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const MyContainer<T>& container) {
            os << "[";
            for (size_t i = 0; i < container.data.size(); ++i) {
                os << container.data[i];
                if (i + 1 != container.data.size()) os << ", ";
            }
            os << "]";
            return os;
        }

        /**
         * @brief Returns a const reference to the internal data vector.
         * 
         * Useful for testing or building custom iterators.
         * @return const std::vector<T>& Reference to the data vector.
         */
        const std::vector<T>& get_data() const {
            return data;
        }

        /**
         * @brief Iterator that traverses elements in ascending order.
         * 
         * Creates a sorted copy of the container's data in increasing order.
         * The `index` controls whether to start at the beginning or end.
         */
        class AscendingOrderIterator : public BaseIterator<T> {
        public:
            /**
             * @brief Constructs an AscendingOrderIterator.
             * 
             * @param original_data Original unordered container data.
             * @param begin If true, starts from index 0; otherwise from end.
             */
            AscendingOrderIterator(const std::vector<T>& original_data, bool begin) {
                this->ordered_data = original_data;
                std::sort(this->ordered_data.begin(), this->ordered_data.end());
                this->index = begin ? 0 : this->ordered_data.size();
            }
        };
        /**
         * @brief Returns an iterator to the beginning of ascending order.
         * 
         * @return AscendingOrderIterator
         */
        AscendingOrderIterator begin_ascending_order() const 
        { 
            return AscendingOrderIterator(data, true);
        }

        /**
         * @brief Returns an iterator to the end of ascending order.
         * 
         * @return AscendingOrderIterator
         */
        AscendingOrderIterator end_ascending_order() const 
        {
            return AscendingOrderIterator(data, false); 
        }


        /**
         * @brief Iterator that traverses elements in descending order.
         * 
         * Creates a sorted copy of the container's data in decreasing order.
         */
        class DescendingOrderIterator : public BaseIterator<T> {
        public:
            /**
             * @brief Constructs a DescendingOrderIterator.
             * 
             * @param original_data Original unordered container data.
             * @param begin If true, starts from index 0; otherwise from end.
             */
            DescendingOrderIterator(const std::vector<T>& original_data, bool begin) {
                this->ordered_data = original_data;
                std::sort(this->ordered_data.begin(), this->ordered_data.end(), std::greater<T>());
                this->index = begin ? 0 : this->ordered_data.size();
            }
        };

        /**
         * @brief Returns an iterator to the beginning of descending order.
         * 
         * @return DescendingOrderIterator
         */
        DescendingOrderIterator begin_descending_order() const 
        { 
            return DescendingOrderIterator(data, true); 
        }

        /**
         * @brief Returns an iterator to the end of descending order.
         * 
         * @return DescendingOrderIterator
         */
        DescendingOrderIterator end_descending_order() const 
        { 
            return DescendingOrderIterator(data, false); 
        }

        /**
         * @brief Iterator that traverses elements in a cross pattern:
         * smallest, largest, 2nd smallest, 2nd largest, etc.
         */
        class SideCrossOrderIterator : public BaseIterator<T> {
        public:
            /**
             * @brief Constructs a SideCrossOrderIterator.
             * 
             * Sorts the data and builds a zigzag traversal starting from both ends.
             * 
             * @param original_data Original container elements.
             * @param begin Whether to initialize at the start (0) or at end().
             */
            SideCrossOrderIterator(const std::vector<T>& original_data, bool begin) {
                std::vector<T> sorted = original_data;
                std::sort(sorted.begin(), sorted.end());
                size_t left = 0, right = sorted.size() - 1;
                while (left <= right) {
                    if (left == right) this->ordered_data.push_back(sorted[left]);
                    else {
                        this->ordered_data.push_back(sorted[left]);
                        this->ordered_data.push_back(sorted[right]);
                    }
                    ++left;
                    if (right > 0) --right;
                }
                this->index = begin ? 0 : this->ordered_data.size();
            }
        };

        /**
         * @brief Returns iterator to beginning of SideCrossOrder.
         */
        SideCrossOrderIterator begin_side_cross_order() const {
            return SideCrossOrderIterator(data, true);
        }

        /**
         * @brief Returns iterator to end of SideCrossOrder.
         */
        SideCrossOrderIterator end_side_cross_order() const {
            return SideCrossOrderIterator(data, false);
        }

        /**
         * @brief Iterator that traverses elements in reverse of insertion order.
         */
        class ReverseOrderIterator : public BaseIterator<T> {
        public:
            /**
             * @brief Constructs a ReverseOrderIterator.
             * 
             * Builds a reversed version of the original insertion order.
             * 
             * @param original_data The elements in original insertion order.
             * @param begin Whether to initialize at start or end.
             */
            ReverseOrderIterator(const std::vector<T>& original_data, bool begin) {
                this->ordered_data = original_data;
                std::reverse(this->ordered_data.begin(), this->ordered_data.end());
                this->index = begin ? 0 : this->ordered_data.size();
            }
        };

        /**
         * @brief Returns iterator to beginning of reverse order.
         */
        ReverseOrderIterator begin_reverse_order() const {
            return ReverseOrderIterator(data, true);
        }

        /**
         * @brief Returns iterator to end of reverse order.
         */
        ReverseOrderIterator end_reverse_order() const {
            return ReverseOrderIterator(data, false);
        }

        /**
         * @brief Iterator that traverses elements in original insertion order.
         */
        class OrderIterator : public BaseIterator<T> {
        public:
            /**
             * @brief Constructs an OrderIterator.
             * 
             * Keeps the original insertion order unchanged.
             * 
             * @param original_data Raw container data.
             * @param begin Whether to begin at index 0 or end.
             */
            OrderIterator(const std::vector<T>& original_data, bool begin) {
                this->ordered_data = original_data;
                this->index = begin ? 0 : this->ordered_data.size();
            }
        };
        /**
         * @brief Returns iterator to beginning of insertion order.
         */
        OrderIterator begin_order() const {
            return OrderIterator(data, true);
        }

        /**
         * @brief Returns iterator to end of insertion order.
         */
        OrderIterator end_order() const {
            return OrderIterator(data, false);
        }

        /**
         * @brief Iterator that traverses from the middle element outward.
         * 
         * Starts from the middle, then alternates left/right.
         */
        class MiddleOutOrderIterator : public BaseIterator<T> {
        public:
            /**
             * @brief Constructs a MiddleOutOrderIterator.
             * 
             * Starts from the middle element, then alternates outward: right, left, right, left...
             * 
             * @param original_data The container's current elements.
             * @param begin Whether to start at index 0 or end.
             */
            MiddleOutOrderIterator(const std::vector<T>& original_data, bool begin) {
                size_t n = original_data.size();
                size_t mid = n / 2;
                if (n == 0) {
                    this->index = 0;
                    return;
                }
                this->ordered_data.push_back(original_data[mid]);
                int left = static_cast<int>(mid) - 1;
                size_t right = mid + 1;
                bool takeLeft = false;
                while (left >= 0 || right < n) {
                    if (takeLeft && left >= 0) this->ordered_data.push_back(original_data[left--]);
                    else if (!takeLeft && right < n) this->ordered_data.push_back(original_data[right++]);
                    takeLeft = !takeLeft;
                }
                this->index = begin ? 0 : this->ordered_data.size();
            }
        };
        /**
         * @brief Returns iterator to beginning of middle-out traversal.
         */
        MiddleOutOrderIterator begin_middle_out_order() const {
            return MiddleOutOrderIterator(data, true);
        }

        /**
         * @brief Returns iterator to end of middle-out traversal.
         */
        MiddleOutOrderIterator end_middle_out_order() const {
            return MiddleOutOrderIterator(data, false);
        }
    };

}