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

#ifndef Core_AutoPtr_H
#define Core_AutoPtr_H


#include "ECore/Core/Core.h"
#include "ECore/Core/Exception.h"
#include <algorithm>


namespace Core {


template <class C>
class AutoPtr
{
public:
	AutoPtr(): _ptr(0)
	{
	}

	AutoPtr(C* ptr): _ptr(ptr)
	{
	}

	AutoPtr(C* ptr, bool shared): _ptr(ptr)
	{
		if (shared && _ptr) 
		{
			_ptr->duplicate();
		}
	}

	AutoPtr(const AutoPtr& ptr): _ptr(ptr._ptr)
	{
		if (_ptr) 
		{
			_ptr->duplicate();
		}
	}

	template <class Other> 
	AutoPtr(const AutoPtr<Other>& ptr): _ptr(const_cast<Other*>(ptr.get()))
	{
		if (_ptr) 
		{
			_ptr->duplicate();
		}
	}

	~AutoPtr()
	{
		if (_ptr) 
		{
			_ptr->release();
		}
	}
	
	AutoPtr& assign(C* ptr)
	{
		if (_ptr != ptr)
		{
			if (_ptr)
			{
				_ptr->release();
			}
			_ptr = ptr;
		}
		return *this;
	}

	AutoPtr& assign(C* ptr, bool shared)
	{
		if (_ptr != ptr)
		{
			if (_ptr) 
			{
				_ptr->release();
			}
			
			_ptr = ptr;
			
			if (shared && _ptr) 
			{
				_ptr->duplicate();
			}
		}
		return *this;
	}
	
	AutoPtr& assign(const AutoPtr& ptr)
	{
		if (&ptr != this)
		{
			if (_ptr) 
			{
				_ptr->release();
			}
			
			_ptr = ptr._ptr;
			
			if (_ptr) 
			{
				_ptr->duplicate();
			}
		}
		return *this;
	}
	
	template <class Other> 
	AutoPtr& assign(const AutoPtr<Other>& ptr)
	{
		if (ptr.get() != _ptr)
		{
			if (_ptr) 
			{
				_ptr->release();
			}
			
			_ptr = const_cast<Other*>(ptr.get());
			
			if (_ptr)
			{
				_ptr->duplicate();
			}
		}
		return *this;
	}

	AutoPtr& operator = (C* ptr)
	{
		return assign(ptr);
	}

	AutoPtr& operator = (const AutoPtr& ptr)
	{
		return assign(ptr);
	}
	
	template <class Other> 
	AutoPtr& operator = (const AutoPtr<Other>& ptr)
	{
		return assign<Other>(ptr);
	}

	void swap(AutoPtr& ptr)
	{
		std::swap(_ptr, ptr._ptr);
	}
	
	template <class Other> 
	AutoPtr<Other> cast() const
	{
		Other* pOther = dynamic_cast<Other*>(_ptr);
		return AutoPtr<Other>(pOther, true);
	}

	template <class Other> 
	AutoPtr<Other> unsafeCast() const
	{
		Other* pOther = static_cast<Other*>(_ptr);
		return AutoPtr<Other>(pOther, true);
	}

	C* operator -> ()
	{
		if (_ptr)
		{
			return _ptr;
		}
		else
		{
			throw NullPointerException();
		}
	}

	const C* operator -> () const
	{
		if (_ptr)
		{
			return _ptr;
		}
		else
		{
			throw NullPointerException();
		}
	}

	C& operator * ()
	{
		if (_ptr)
		{
			return *_ptr;
		}
		else
		{
			throw NullPointerException();
		}
	}

	const C& operator * () const
	{
		if (_ptr)
		{
			return *_ptr;
		}
		else
		{
			throw NullPointerException();
		}
	}

	C* get()
	{
		return _ptr;
	}

	const C* get() const
	{
		return _ptr;
	}

	operator C* ()
	{
		return _ptr;
	}
	
	operator const C* () const
	{
		return _ptr;
	}
	
	bool operator ! () const
	{
		return _ptr == 0;
	}

	bool isNull() const
	{
		return _ptr == 0;
	}
	
	C* duplicate()
	{
		if (_ptr) 
		{
			_ptr->duplicate();
		}
		return _ptr;
	}

	bool operator == (const AutoPtr& ptr) const
	{
		return _ptr == ptr._ptr;
	}

	bool operator == (const C* ptr) const
	{
		return _ptr == ptr;
	}

	bool operator == (C* ptr) const
	{
		return _ptr == ptr;
	}

	bool operator != (const AutoPtr& ptr) const
	{
		return _ptr != ptr._ptr;
	}

	bool operator != (const C* ptr) const
	{
		return _ptr != ptr;
	}

	bool operator != (C* ptr) const
	{
		return _ptr != ptr;
	}

	bool operator < (const AutoPtr& ptr) const
	{
		return _ptr < ptr._ptr;
	}

	bool operator < (const C* ptr) const
	{
		return _ptr < ptr;
	}

	bool operator < (C* ptr) const
	{
		return _ptr < ptr;
	}

	bool operator <= (const AutoPtr& ptr) const
	{
		return _ptr <= ptr._ptr;
	}

	bool operator <= (const C* ptr) const
	{
		return _ptr <= ptr;
	}

	bool operator <= (C* ptr) const
	{
		return _ptr <= ptr;
	}

	bool operator > (const AutoPtr& ptr) const
	{
		return _ptr > ptr._ptr;
	}

	bool operator > (const C* ptr) const
	{
		return _ptr > ptr;
	}

	bool operator > (C* ptr) const
	{
		return _ptr > ptr;
	}

	bool operator >= (const AutoPtr& ptr) const
	{
		return _ptr >= ptr._ptr;
	}

	bool operator >= (const C* ptr) const
	{
		return _ptr >= ptr;
	}

	bool operator >= (C* ptr) const
	{
		return _ptr >= ptr;
	}

private:
	C* _ptr;
};


template <class C>
inline void swap(AutoPtr<C>& p1, AutoPtr<C>& p2)
{
	p1.swap(p2);
}


}   // namespace Core


#endif  // Core_AutoPtr_H

