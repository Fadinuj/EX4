//fadinujedat062@gmail.com
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace containers {
    template<typename T = int>
    class MyContainer {
    private:
        std::vector<T> data;

        // ============================
        // Base Iterator
        // ============================
        template<typename IterType>
        class BaseIterator {
        protected:
            std::vector<IterType> ordered_data;
            size_t index = 0;

        public:
            BaseIterator() = default;

            const IterType& operator*() const {
                if (index >= ordered_data.size()) {
                    throw std::out_of_range("Dereferencing end() iterator");
                }
                return ordered_data[index];
            }

            BaseIterator& operator++() {
                ++index;
                return *this;
            }

            bool operator!=(const BaseIterator& other) const {
                return index != other.index;
            }

            bool operator==(const BaseIterator& other) const {
                return index == other.index;
            }

            BaseIterator& operator=(const BaseIterator& other) {
                if (this != &other) {
                    this->ordered_data = other.ordered_data;
                    this->index = other.index;
                }
                return *this;
            }

            size_t position() const {
                return index;
            }
        };

    public:
        MyContainer() = default;

        void addElement(const T& value) {
            data.push_back(value);
        }

        void remove(const T& value) {
            auto it = std::remove(data.begin(), data.end(), value);
            if (it == data.end()) {
                throw std::runtime_error("Item not found in container");
            }
            data.erase(it, data.end());
        }

        size_t size() const {
            return data.size();
        }

        friend std::ostream& operator<<(std::ostream& os, const MyContainer<T>& container) {
            os << "[";
            for (size_t i = 0; i < container.data.size(); ++i) {
                os << container.data[i];
                if (i + 1 != container.data.size()) os << ", ";
            }
            os << "]";
            return os;
        }

        const std::vector<T>& get_data() const {
            return data;
        }

        // ===== Iterators =====
        class AscendingOrderIterator : public BaseIterator<T> {
        public:
            AscendingOrderIterator(const std::vector<T>& original_data, bool begin) {
                this->ordered_data = original_data;
                std::sort(this->ordered_data.begin(), this->ordered_data.end());
                this->index = begin ? 0 : this->ordered_data.size();
            }
        };
        AscendingOrderIterator begin_ascending_order() const { return AscendingOrderIterator(data, true); }
        AscendingOrderIterator end_ascending_order() const { return AscendingOrderIterator(data, false); }

        class DescendingOrderIterator : public BaseIterator<T> {
        public:
            DescendingOrderIterator(const std::vector<T>& original_data, bool begin) {
                this->ordered_data = original_data;
                std::sort(this->ordered_data.begin(), this->ordered_data.end(), std::greater<T>());
                this->index = begin ? 0 : this->ordered_data.size();
            }
        };
        DescendingOrderIterator begin_descending_order() const { return DescendingOrderIterator(data, true); }
        DescendingOrderIterator end_descending_order() const { return DescendingOrderIterator(data, false); }

        class SideCrossOrderIterator : public BaseIterator<T> {
        public:
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
        SideCrossOrderIterator begin_side_cross_order() const { return SideCrossOrderIterator(data, true); }
        SideCrossOrderIterator end_side_cross_order() const { return SideCrossOrderIterator(data, false); }

        class ReverseOrderIterator : public BaseIterator<T> {
        public:
            ReverseOrderIterator(const std::vector<T>& original_data, bool begin) {
                this->ordered_data = original_data;
                std::reverse(this->ordered_data.begin(), this->ordered_data.end());
                this->index = begin ? 0 : this->ordered_data.size();
            }
        };
        ReverseOrderIterator begin_reverse_order() const { return ReverseOrderIterator(data, true); }
        ReverseOrderIterator end_reverse_order() const { return ReverseOrderIterator(data, false); }

        class OrderIterator : public BaseIterator<T> {
        public:
            OrderIterator(const std::vector<T>& original_data, bool begin) {
                this->ordered_data = original_data;
                this->index = begin ? 0 : this->ordered_data.size();
            }
        };
        OrderIterator begin_order() const { return OrderIterator(data, true); }
        OrderIterator end_order() const { return OrderIterator(data, false); }

        class MiddleOutOrderIterator : public BaseIterator<T> {
        public:
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
        MiddleOutOrderIterator begin_middle_out_order() const { return MiddleOutOrderIterator(data, true); }
        MiddleOutOrderIterator end_middle_out_order() const { return MiddleOutOrderIterator(data, false); }
    };

}