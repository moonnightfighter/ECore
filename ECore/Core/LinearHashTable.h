/*
The LGPL License (LGPL)

Copyright (c) 2012-2013 moon

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef Core_LinearHashTable_H
#define Core_LinearHashTable_H


#include "ECore/Core/Core.h"
#include "ECore/Core/Hash.h"
#include <functional>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstddef>


namespace Core {


template <class Value, class HashFunc = Hash<Value> >
class LinearHashTable
{
public:
    typedef Value               ValueType;
    typedef Value&              Reference;
    typedef const Value&        ConstReference;
    typedef Value*              Pointer;
    typedef const Value*        ConstPointer;
    typedef HashFunc            Hash;
    typedef std::vector<Value>  Bucket;
    typedef std::vector<Bucket> BucketVec;
    typedef typename Bucket::iterator    BucketIterator;
    typedef typename BucketVec::iterator BucketVecIterator;

    class ConstIterator: public std::iterator<std::forward_iterator_tag, Value>
    {
    public:
        ConstIterator()
        {
        }

        ConstIterator(const BucketVecIterator& vecIt, const BucketVecIterator& endIt, const BucketIterator& buckIt):
            _vecIt(vecIt),
            _endIt(endIt),
            _buckIt(buckIt)
        {
        }

        ConstIterator(const ConstIterator& it):
            _vecIt(it._vecIt),
            _endIt(it._endIt),
            _buckIt(it._buckIt)
        {
        }

        ConstIterator& operator = (const ConstIterator& it)
        {
            ConstIterator tmp(it);
            swap(tmp);
            return *this;
        }

        void swap(ConstIterator& it)
        {
            using std::swap;
            swap(_vecIt, it._vecIt);
            swap(_endIt, it._endIt);
            swap(_buckIt, it._buckIt);
        }

        bool operator == (const ConstIterator& it) const
        {
            return _vecIt == it._vecIt && (_vecIt == _endIt || _buckIt == it._buckIt);
        }

        bool operator != (const ConstIterator& it) const
        {
            return _vecIt != it._vecIt || (_vecIt != _endIt && _buckIt != it._buckIt);
        }

        const typename Bucket::value_type& operator * () const
        {
            return *_buckIt;
        }

        const typename Bucket::value_type* operator -> () const
        {
            return &*_buckIt;
        }

        ConstIterator& operator ++ () // prefix
        {
            if (_vecIt != _endIt)
            {
                ++_buckIt;
                while (_vecIt != _endIt && _buckIt == _vecIt->end())
                {
                    ++_vecIt;
                    if (_vecIt != _endIt) _buckIt = _vecIt->begin();
                }
            }
            return *this;
        }

        ConstIterator operator ++ (int) // postfix
        {
            ConstIterator tmp(*this);
            ++*this;
            return tmp;
        }

    protected:
        BucketVecIterator _vecIt;
        BucketVecIterator _endIt;
        BucketIterator    _buckIt;

        friend class LinearHashTable;
    };

    class Iterator: public ConstIterator
    {
    public:
        Iterator()
        {
        }

        Iterator(const BucketVecIterator& vecIt, const BucketVecIterator& endIt, const BucketIterator& buckIt):
        ConstIterator(vecIt, endIt, buckIt)
        {
        }

        Iterator(const Iterator& it):
        ConstIterator(it)
        {
        }

        Iterator& operator = (const Iterator& it)
        {
            Iterator tmp(it);
            swap(tmp);
            return *this;
        }

        void swap(Iterator& it)
        {
            ConstIterator::swap(it);
        }

        typename Bucket::value_type& operator * ()
        {
            return *this->_buckIt;
        }

        const typename Bucket::value_type& operator * () const
        {
            return *this->_buckIt;
        }

        typename Bucket::value_type* operator -> ()
        {
            return &*this->_buckIt;
        }

        const typename Bucket::value_type* operator -> () const
        {
            return &*this->_buckIt;
        }

        Iterator& operator ++ () // prefix
        {
            ConstIterator::operator ++ ();
            return *this;
        }

        Iterator operator ++ (int) // postfix
        {
            Iterator tmp(*this);
            ++*this;
            return tmp;
        }

        friend class LinearHashTable;
    };

    LinearHashTable(std::size_t initialReserve = 64): 
        _split(0),
        _front(1),
        _size(0)
    {
        _buckets.reserve(calcSize(initialReserve));
        _buckets.push_back(Bucket());
    }

    LinearHashTable(const LinearHashTable& table):
        _buckets(table._buckets),
        _split(table._split),
        _front(table._front),
        _size(table._size)
    {
    }

    ~LinearHashTable()
    {
    }

    LinearHashTable& operator = (const LinearHashTable& table)
    {
        LinearHashTable tmp(table);
        swap(tmp);
        return *this;
    }

    void swap(LinearHashTable& table)
    {
        using std::swap;
        swap(_buckets, table._buckets);
        swap(_split, table._split);
        swap(_front, table._front);
        swap(_size, table._size);
    }

    ConstIterator begin() const
    {
        BucketVecIterator it(_buckets.begin());
        BucketVecIterator end(_buckets.end());
        while (it != end && it->empty())
        {
            ++it;
        }
        if (it == end)
            return this->end();
        else
            return ConstIterator(it, end, it->begin());
    }

    ConstIterator end() const
    {
        return ConstIterator(_buckets.end(), _buckets.end(), _buckets.front().end());
    }

    Iterator begin()
    {
        BucketVecIterator it(_buckets.begin());
        BucketVecIterator end(_buckets.end());
        while (it != end && it->empty())
        {
            ++it;
        }
        if (it == end)
            return this->end();
        else
            return Iterator(it, end, it->begin());
    }

    Iterator end()
    {
        return Iterator(_buckets.end(), _buckets.end(), _buckets.front().end());
    }

    ConstIterator find(const Value& value) const
    {
        std::size_t addr = bucketAddress(value);
        BucketVecIterator it(_buckets.begin() + addr);
        BucketIterator buckIt(std::find(it->begin(), it->end(), value));
        if (buckIt != it->end())
            return ConstIterator(it, _buckets.end(), buckIt);
        else
            return end();
    }

    Iterator find(const Value& value)
    {
        std::size_t addr = bucketAddress(value);
        BucketVecIterator it(_buckets.begin() + addr);
        BucketIterator buckIt(std::find(it->begin(), it->end(), value));
        if (buckIt != it->end())
            return Iterator(it, _buckets.end(), buckIt);
        else
            return end();
    }

    std::size_t count(const Value& value) const
    {
        return find(value) != end() ? 1 : 0;
    }

    std::pair<Iterator, bool> insert(const Value& value)
    {
        std::size_t hash = _hash(value);
        std::size_t addr = bucketAddressForHash(hash);
        BucketVecIterator it(_buckets.begin() + addr);
        BucketIterator buckIt(std::find(it->begin(), it->end(), value));
        if (buckIt == it->end())
        {
            split();
            addr = bucketAddressForHash(hash);
            it = _buckets.begin() + addr;
            buckIt = it->insert(it->end(), value);
            ++_size;
            return std::make_pair(Iterator(it, _buckets.end(), buckIt), true);
        }
        else
        {
            return std::make_pair(Iterator(it, _buckets.end(), buckIt), false);
        }
    }

    void erase(Iterator it)
    {
        if (it != end())
        {
            it._vecIt->erase(it._buckIt);
            --_size;
            merge();
        }
    }

    void erase(const Value& value)
    {
        Iterator it = find(value);
        erase(it);
    }

    void clear()
    {
        LinearHashTable empty;
        swap(empty);
    }

    std::size_t size() const
    {
        return _size;
    }

    bool empty() const
    {
        return _size == 0;
    }

    std::size_t buckets() const
    {
        return _buckets.size();
    }

protected:
    std::size_t bucketAddress(const Value& value) const
    {
        std::size_t n = _hash(value);
        if (n % _front >= _split)
            return n % _front;
        else
            return n % (2*_front);
    }

    std::size_t bucketAddressForHash(std::size_t hash)
    {
        if (hash % _front >= _split)
            return hash % _front;
        else
            return hash % (2*_front);
    }

    void split()
    {
        if (_split == _front)
        {
            _split = 0;
            _front *= 2;
            _buckets.reserve(_front*2);
        }
        Bucket tmp;
        _buckets.push_back(tmp);
        _buckets[_split].swap(tmp);
        ++_split;
        for (BucketIterator it = tmp.begin(); it != tmp.end(); ++it)
        {
            using std::swap;
            std::size_t addr = bucketAddress(*it);
            _buckets[addr].push_back(Value());
            swap(*it, _buckets[addr].back());
        }
    }

    void merge()
    {
        if (_split == 0)
        {
            _front /= 2;
            _split = _front;
        }
        --_split;
        Bucket tmp;
        tmp.swap(_buckets.back());
        _buckets.pop_back();
        for (BucketIterator it = tmp.begin(); it != tmp.end(); ++it)
        {
            using std::swap;
            std::size_t addr = bucketAddress(*it);
            _buckets[addr].push_back(Value());
            swap(*it, _buckets[addr].back());
        }
    }

    static std::size_t calcSize(std::size_t initialSize)
    {
        std::size_t size = 32;
        while (size < initialSize) size *= 2;
        return size;
    }

private:
    mutable BucketVec _buckets;
    std::size_t _split;
    std::size_t _front;
    volatile std::size_t _size;
    HashFunc    _hash;
};


}   // namespace Core


#endif  // Core_LinearHashTable_H
