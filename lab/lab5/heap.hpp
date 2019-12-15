#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <cassert>

/*
kopiec binarny
*/
template<typename DataType>
class Heap
{
    private:
    using size_type = size_t;

    std::vector<DataType> vector;

    /**
     * Computes parent's position for a node at `pos`.
     */
    size_type parent(size_type pos) const
    {
        return pos > 0 ? (pos - 1) / 2 : throw std::out_of_range("parent(pos <= 0)");
    }

    /**
     * Computes position of the `rank`-th child for a node at `pos`.
     */
    size_type child( size_type pos, size_type rank) const
    {
        assert(0 <= rank && rank < 2);
        return 2 * pos + rank + 1;
    }

    bool compare( DataType& left, DataType& right) const
    {
        return left.compare(right);
    }

    /**
     * Moves the element at `pos` upwards until heap property is restored.
     */
    void sift_up(size_type pos) {
        while (pos) 
        {
            size_type parent = this->parent(pos);

            if (compare(this->vector[pos], this->vector[parent])) 
            {
                std::swap(this->vector[pos], this->vector[parent]);
                pos = parent;
            } 
            else 
                break;
        }
    }

    /**
     * Moves the element at `pos` downwards until heap property is restored.
     */
    void sift_down(size_type pos) {
        size_type best_pos = pos;

        for (size_type i = 0; i < 2; ++i) {
            size_type child_pos = this->child(pos, i);

            if (child_pos < this->vector.size()) {
                if (this->compare(this->vector[child_pos], this->vector[best_pos])) {
                    best_pos = child_pos;
                }
            }
        }

        if (best_pos != pos) {
            std::swap(this->vector[pos], this->vector[best_pos]);
            this->sift_down(best_pos);
        }
    }

    public:
    const DataType& front() const 
    {
        if (this->vector.empty()) throw std::out_of_range("calling front() for an empty heap");
        return vector.front();
    };

    void push(const DataType& data)
    {
        vector.push_back(data);
        sift_up(vector.size()-1);
    }

    void pop()
    {
        if (!this->vector.empty()) {
            if (this->vector.size() > 1) { std::swap(this->vector.front(), this->vector.back()); }
            this->vector.pop_back();

            if (!this->vector.empty()) { this->sift_down(0); }
        }

    }
};




#endif
