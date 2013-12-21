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

#ifndef Core_HashTable_H
#define Core_HashTable_H


#include "ECore/Core/Core.h"
#include "ECore/Core/Exception.h"
#include "ECore/Core/HashFunction.h"
#include "ECore/Core/HashStatistic.h"
#include <vector>
#include <map>
#include <cstddef>
#include <cstring>


namespace Core {


template <class Key, class Value, class KeyHashFunction = HashFunction<Key> >
class HashTable
{
public:
    typedef std::map<Key, Value> HashEntryMap;
    typedef HashEntryMap**       HashTableVector;

    typedef typename HashEntryMap::const_iterator ConstIterator;
    typedef typename HashEntryMap::iterator Iterator;

    HashTable(UInt32 initialSize = 251): 
        _entries(0), 
        _size(0), 
        _maxCapacity(initialSize)
    {
        _entries = new HashEntryMap*[initialSize];
        memset(_entries, '\0', sizeof(HashEntryMap*)*initialSize);
    }

    HashTable(const HashTable& ht):
    _entries(new HashEntryMap*[ht._maxCapacity]),
        _size(ht._size),
        _maxCapacity(ht._maxCapacity)
    {
        for (UInt32 i = 0; i < _maxCapacity; ++i)
        {
            if (ht._entries[i])
                _entries[i] = new HashEntryMap(ht._entries[i]->begin(), ht._entries[i]->end());
            else
                _entries[i] = 0;
        }
    }

    ~HashTable()
    {
        clear();
    }

    HashTable& operator = (const HashTable& ht)
    {
        if (this != &ht)
        {
            clear();
            _maxCapacity = ht._maxCapacity;
            core_assert_dbg (_entries == 0);
            _entries = new HashEntryMap*[_maxCapacity];
            _size = ht._size;

            for (UInt32 i = 0; i < _maxCapacity; ++i)
            {
                if (ht._entries[i])
                    _entries[i] = new HashEntryMap(ht._entries[i]->begin(), ht._entries[i]->end());
                else
                    _entries[i] = 0;
            }
        }
        return *this;
    }

    void clear()
    {
        if (!_entries)
            return;
        for (UInt32 i = 0; i < _maxCapacity; ++i)
        {
            if (_entries[i])
                delete _entries[i];
        }
        delete[] _entries;
        _entries     = 0;
        _size        = 0;
        _maxCapacity = 0;
    }

    UInt32 insert(const Key& key, const Value& value)
    {
        UInt32 hsh = hash(key);
        insertRaw(key, hsh, value);
        return hsh;
    }

    Value& insertRaw(const Key& key, UInt32 hsh, const Value& value)
    {
        if (!_entries[hsh])
            _entries[hsh] = new HashEntryMap();
        std::pair<typename HashEntryMap::iterator, bool> res(_entries[hsh]->insert(std::make_pair(key, value)));
        if (!res.second)
            throw InvalidArgumentException("HashTable::insert, key already exists.");
        _size++;
        return res.first->second;
    }

    UInt32 update(const Key& key, const Value& value)
    {
        UInt32 hsh = hash(key);
        updateRaw(key, hsh, value);
        return hsh;
    }

    void updateRaw(const Key& key, UInt32 hsh, const Value& value)
    {
        if (!_entries[hsh])
            _entries[hsh] = new HashEntryMap();
        std::pair<Iterator, bool> res = _entries[hsh]->insert(std::make_pair(key, value));
        if (res.second == false)
            res.first->second = value;
        else
            _size++;
    }

    void remove(const Key& key)
    {
        UInt32 hsh = hash(key);
        removeRaw(key, hsh);
    }

    void removeRaw(const Key& key, UInt32 hsh)
    {
        if (_entries[hsh])
        {
            _size -= _entries[hsh]->erase(key);
        }
    }

    UInt32 hash(const Key& key) const
    {
        return _hash(key, _maxCapacity);
    }

    const Value& get(const Key& key) const
    {
        UInt32 hsh = hash(key);
        return getRaw(key, hsh);
    }

    const Value& getRaw(const Key& key, UInt32 hsh) const
    {
        if (!_entries[hsh])
            throw InvalidArgumentException("key not found");

        ConstIterator it = _entries[hsh]->find(key);
        if (it == _entries[hsh]->end())
            throw InvalidArgumentException("key not found");

        return it->second;
    }

    Value& get(const Key& key)
    {
        UInt32 hsh = hash(key);
        return const_cast<Value&>(getRaw(key, hsh));
    }

    const Value& operator [] (const Key& key) const
    {
        return get(key);
    }

    Value& operator [] (const Key& key)
    {
        UInt32 hsh = hash(key);

        if (!_entries[hsh])
            return insertRaw(key, hsh, Value());

        ConstIterator it = _entries[hsh]->find(key);
        if (it == _entries[hsh]->end())
            return insertRaw(key, hsh, Value());

        return it->second;
    }

    const Key& getKeyRaw(const Key& key, UInt32 hsh)
    {
        if (!_entries[hsh])
            throw InvalidArgumentException("key not found");
        ConstIterator it = _entries[hsh]->find(key);
        if (it == _entries[hsh]->end())
            throw InvalidArgumentException("key not found");
        return it->first;
    }

    bool get(const Key& key, Value& v) const
    {
        UInt32 hsh = hash(key);
        return getRaw(key, hsh, v);
    }

    bool getRaw(const Key& key, UInt32 hsh, Value& v) const
    {
        if (!_entries[hsh])
            return false;

        ConstIterator it = _entries[hsh]->find(key);
        if (it == _entries[hsh]->end())
            return false;

        v = it->second;
        return true;
    }

    bool exists(const Key& key)
    {
        UInt32 hsh = hash(key);
        return existsRaw(key, hsh);
    }

    bool existsRaw(const Key& key, UInt32 hsh)
    {
        return _entries[hsh] && (_entries[hsh]->end() != _entries[hsh]->find(key));
    }

    std::size_t size() const
    {
        return _size;
    }

    UInt32 maxCapacity() const
    {
        return _maxCapacity;
    }

    void resize(UInt32 newSize)
    {
        if (_maxCapacity != newSize)
        {
            HashTableVector cpy = _entries;
            _entries = 0;
            UInt32 oldSize = _maxCapacity;
            _maxCapacity = newSize;
            _entries = new HashEntryMap*[_maxCapacity];
            memset(_entries, '\0', sizeof(HashEntryMap*)*_maxCapacity);

            if (_size == 0)
            {
                delete[] cpy;
                return;
            }
            _size = 0;
            for (UInt32 i = 0; i < oldSize; ++i)
            {
                if (cpy[i])
                {
                    ConstIterator it = cpy[i]->begin();
                    ConstIterator itEnd = cpy[i]->end();
                    for (; it != itEnd; ++it)
                    {
                        insert(it->first, it->second);
                    }
                    delete cpy[i];
                }
            }
            delete[] cpy;
        }
    }

    HashStatistic currentState(bool details = false) const
    {
        UInt32 numberOfEntries = (UInt32)_size;
        UInt32 numZeroEntries = 0;
        UInt32 maxEntriesPerHash = 0;
        std::vector<UInt32> detailedEntriesPerHash;
#ifdef DEBUG
        UInt32 totalSize = 0;
#endif
        for (UInt32 i = 0; i < _maxCapacity; ++i)
        {
            if (_entries[i])
            {
                UInt32 size = (UInt32)_entries[i]->size();
                core_assert_dbg(size != 0);
                if (size > maxEntriesPerHash)
                    maxEntriesPerHash = size;
                if (details)
                    detailedEntriesPerHash.push_back(size);
#ifdef DEBUG
                totalSize += size;
#endif
            }
            else
            {
                numZeroEntries++;
                if (details)
                    detailedEntriesPerHash.push_back(0);
            }
        }
#ifdef DEBUG
        core_assert_dbg(totalSize == numberOfEntries);
#endif
        return HashStatistic(_maxCapacity, numberOfEntries, numZeroEntries, maxEntriesPerHash, detailedEntriesPerHash);
    }

private:
    HashTableVector _entries;
    std::size_t     _size;
    UInt32          _maxCapacity;
    KeyHashFunction _hash;
};


}   // namespace Core


#endif  // Core_HashTable_H
