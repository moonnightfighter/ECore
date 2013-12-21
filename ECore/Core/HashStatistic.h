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

#ifndef Core_HashStatistic_H
#define Core_HashStatistic_H


#include "ECore/Core/Core.h"
#include <vector>


namespace Core {


class Core_API HashStatistic
{
public:
    HashStatistic(
        UInt32 tableSize, 
        UInt32 numEntries, 
        UInt32 numZeroEntries, 
        UInt32 maxEntry, 
        std::vector<UInt32> details = std::vector<UInt32>());

    virtual ~HashStatistic();

    UInt32 maxPositionsOfTable() const;

    UInt32 numberOfEntries() const;

    UInt32 numberOfZeroPositions() const;

    double avgEntriesPerHash() const;

    double avgEntriesPerHashExclZeroEntries() const;

    UInt32 maxEntriesPerHash() const;

    const std::vector<UInt32> detailedEntriesPerHash() const;
    
    std::string toString() const;

private:
    UInt32 _sizeOfTable;
    UInt32 _numberOfEntries;
    UInt32 _numZeroEntries;
    UInt32 _maxEntriesPerHash;
    std::vector<UInt32> _detailedEntriesPerHash;
};


inline UInt32 HashStatistic::maxPositionsOfTable() const
{
    return _sizeOfTable;
}


inline UInt32 HashStatistic::numberOfEntries() const
{
    return _numberOfEntries;
}


inline UInt32 HashStatistic::numberOfZeroPositions() const
{
    return _numZeroEntries;
}


inline double HashStatistic::avgEntriesPerHash() const
{
    return ((double) numberOfEntries()) / maxPositionsOfTable();
}


inline double HashStatistic::avgEntriesPerHashExclZeroEntries() const
{
    return ((double) numberOfEntries()) / (maxPositionsOfTable() - numberOfZeroPositions());
}


inline UInt32 HashStatistic::maxEntriesPerHash() const
{
    return _maxEntriesPerHash;
}


inline const std::vector<UInt32> HashStatistic::detailedEntriesPerHash() const
{
    return _detailedEntriesPerHash;
}


}   // namespace Core


#endif  // Core_HashStatistic_H
