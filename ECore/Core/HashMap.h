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

#ifndef Core_HashMap_H
#define Core_HashMap_H


#include "ECore/Core/Core.h"
#include "ECore/Core/LinearHashTable.h"
#include "ECore/Core/Exception.h"
#include <utility>


namespace Core {


template <class Key, class Value>
struct HashMapEntry
{
    Key   first;
    Value second;

    HashMapEntry():
    first(),
        second()
    {
    }

    HashMapEntry(const Key& key):
    first(key),
        second()
    {
    }

    HashMapEntry(const Key& key, const Value& value):
    first(key),
        second(value)
    {
    }

    bool operator == (const HashMapEntry& entry) const
    {
        return first == entry.first;
    }

    bool operator != (const HashMapEntry& entry) const
    {
        return first != entry.first;
    }
};


template <class HME, class KeyHashFunc>
struct HashMapEntryHash
{
    std::size_t operator () (const HME& entry) const
    {
        return _func(entry.first);
    }

private:
    KeyHashFunc _func;
};


template <class Key, class Mapped, class HashFunc = Hash<Key> >
class HashMap
{
public:
    typedef Key                 KeyType;
    typedef Mapped              MappedType;
    typedef Mapped&             Reference;
    typedef const Mapped&       ConstReference;
    typedef Mapped*             Pointer;
    typedef const Mapped*       ConstPointer;

    typedef HashMapEntry<Key, Mapped>      ValueType;
    typedef std::pair<KeyType, MappedType> PairType;

    typedef HashMapEntryHash<ValueType, HashFunc> HashType;
    typedef LinearHashTable<ValueType, HashType>  HashTable;

    typedef typename HashTable::Iterator      Iterator;
    typedef typename HashTable::ConstIterator ConstIterator;

    HashMap()
    {
    }

    HashMap(std::size_t initialReserve):
    _table(initialReserve)
    {
    }

    HashMap& operator = (const HashMap& map)
    {
        HashMap tmp(map);
        swap(tmp);
        return *this;
    }

    void swap(HashMap& map)
    {
        _table.swap(map._table);
    }

    ConstIterator begin() const
    {
        return _table.begin();
    }

    ConstIterator end() const
    {
        return _table.end();
    }

    Iterator begin()
    {
        return _table.begin();
    }

    Iterator end()
    {
        return _table.end();
    }

    ConstIterator find(const KeyType& key) const
    {
        ValueType value(key);
        return _table.find(value);
    }

    Iterator find(const KeyType& key)
    {
        ValueType value(key);
        return _table.find(value);
    }

    std::size_t count(const KeyType& key) const
    {
        ValueType value(key);
        return _table.find(value) != _table.end() ? 1 : 0;
    }

    std::pair<Iterator, bool> insert(const PairType& pair)
    {
        ValueType value(pair.first, pair.second);
        return _table.insert(value);
    }

    std::pair<Iterator, bool> insert(const ValueType& value)
    {
        return _table.insert(value);
    }

    void erase(Iterator it)
    {
        _table.erase(it);
    }

    void erase(const KeyType& key)
    {
        Iterator it = find(key);
        _table.erase(it);
    }

    void clear()
    {
        _table.clear();
    }

    std::size_t size() const
    {
        return _table.size();
    }

    bool empty() const
    {
        return _table.empty();
    }

    ConstReference operator [] (const KeyType& key) const
    {
        ConstIterator it = _table.find(key);
        if (it != _table.end())
            return it->second;
        else
            throw NotFoundException();
    }

    Reference operator [] (const KeyType& key)
    {
        ValueType value(key);
        std::pair<Iterator, bool> res = _table.insert(value);
        return res.first->second;
    }

private:
    HashTable _table;
};


}   // namespace Core


#endif  // Core_HashMap_H
