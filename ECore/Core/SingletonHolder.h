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

#ifndef Core_SingletonHolder_H
#define Core_SingletonHolder_H


#include "ECore/Core/Core.h"
#include "ECore/Core/Mutex.h"


namespace Core {


template <class S>
class SingletonHolder
{
public:
	
	SingletonHolder()
	{
		_pS = 0;
	}
	
	~SingletonHolder()
	{
		delete _pS;
	}
	
	S* get()
	{
		FastMutex::ScopedLock lock(_m);
		if (!_pS) 
		{
			_pS = new S;
		}
		return _pS;
	}
	
private:
	
	S* _pS;
	FastMutex _m;
};


}   // namespace Core


#endif // Core_SingletonHolder_H
