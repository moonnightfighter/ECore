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

#ifndef Core_Exception_H
#define Core_Exception_H


#include "ECore/Core/Core.h"
#include <stdexcept>
#include <typeinfo>


namespace Core {


class Core_API Exception: public std::exception
{
public:
    Exception(const std::string& msg, int code = 0);
    Exception(const std::string& msg, const std::string& arg, int code = 0);
    Exception(const std::string& msg, const Exception& nested, int code = 0);
    Exception(const Exception& exc);
    ~Exception() throw();

    Exception& operator = (const Exception& exc);

    virtual const char* name() const throw();

    virtual const char* className() const throw();

    virtual const char* what() const throw();

    const Exception* nested() const;

    const std::string& message() const;

    int code() const;

    std::string displayText() const;

    virtual Exception* clone() const;

    virtual void rethrow() const;

protected:
    Exception(int code = 0);

    void message(const std::string& msg);

    void extendedMessage(const std::string& arg);

private:
    std::string _msg;
    Exception*  _pNested;
    int			_code;
};


//
// inlines
//
inline const Exception* Exception::nested() const
{
    return _pNested;
}


inline const std::string& Exception::message() const
{
    return _msg;
}


inline void Exception::message(const std::string& msg)
{
    _msg = msg;
}


inline int Exception::code() const
{
    return _code;
}


#define CORE_DECLARE_EXCEPTION_CODE(API, CLS, BASE, CODE) \
    class API CLS: public BASE													\
    {																			\
    public:																		\
    CLS(int code = CODE);														\
    CLS(const std::string& msg, int code = CODE);								\
    CLS(const std::string& msg, const std::string& arg, int code = CODE);		\
    CLS(const std::string& msg, const Core::Exception& exc, int code = CODE);	\
    CLS(const CLS& exc);														\
    ~CLS() throw();																\
    CLS& operator = (const CLS& exc);											\
    const char* name() const throw();											\
    const char* className() const throw();										\
    Core::Exception* clone() const;												\
    void rethrow() const;														\
    };

#define CORE_DECLARE_EXCEPTION(API, CLS, BASE) \
    CORE_DECLARE_EXCEPTION_CODE(API, CLS, BASE, 0)

#define CORE_IMPLEMENT_EXCEPTION(CLS, BASE, NAME)													\
    CLS::CLS(int code): BASE(code)																	\
    {																								\
    }																								\
    CLS::CLS(const std::string& msg, int code): BASE(msg, code)										\
    {																								\
    }																								\
    CLS::CLS(const std::string& msg, const std::string& arg, int code): BASE(msg, arg, code)		\
    {																								\
    }																								\
    CLS::CLS(const std::string& msg, const Core::Exception& exc, int code): BASE(msg, exc, code)	\
    {																								\
    }																								\
    CLS::CLS(const CLS& exc): BASE(exc)																\
    {																								\
    }																								\
    CLS::~CLS() throw()																				\
    {																								\
    }																								\
    CLS& CLS::operator = (const CLS& exc)															\
    {																								\
        BASE::operator = (exc);																		\
        return *this;																				\
    }																								\
    const char* CLS::name() const throw()															\
    {																								\
        return NAME;																				\
    }																								\
    const char* CLS::className() const throw()														\
    {																								\
        return typeid(*this).name();																\
    }																								\
    Core::Exception* CLS::clone() const																\
    {																								\
        return new CLS(*this);																		\
    }																								\
    void CLS::rethrow() const																		\
    {																								\
        throw *this;																				\
    }


CORE_DECLARE_EXCEPTION(Core_API, LogicException, Exception)
CORE_DECLARE_EXCEPTION(Core_API, NullPointerException, LogicException)
CORE_DECLARE_EXCEPTION(Core_API, InvalidArgumentException, LogicException)
CORE_DECLARE_EXCEPTION(Core_API, SignalException, LogicException)

CORE_DECLARE_EXCEPTION(Core_API, RuntimeException, Exception)
CORE_DECLARE_EXCEPTION(Core_API, NotFoundException, RuntimeException)
CORE_DECLARE_EXCEPTION(Core_API, ExistsException, RuntimeException)
CORE_DECLARE_EXCEPTION(Core_API, TimeoutException, RuntimeException)
CORE_DECLARE_EXCEPTION(Core_API, SystemException, RuntimeException)
CORE_DECLARE_EXCEPTION(Core_API, DataException, RuntimeException)

CORE_DECLARE_EXCEPTION(Core_API, SyntaxException, DataException)
CORE_DECLARE_EXCEPTION(Core_API, PathSyntaxException, SyntaxException)
CORE_DECLARE_EXCEPTION(Core_API, IOException, RuntimeException)
CORE_DECLARE_EXCEPTION(Core_API, FileException, IOException)
CORE_DECLARE_EXCEPTION(Core_API, FileExistsException, FileException)
CORE_DECLARE_EXCEPTION(Core_API, FileNotFoundException, FileException)
CORE_DECLARE_EXCEPTION(Core_API, FileReadOnlyException, FileException)
CORE_DECLARE_EXCEPTION(Core_API, FileAccessDeniedException, FileException)
CORE_DECLARE_EXCEPTION(Core_API, OpenFileException, FileException)


}   // namespace Core


#endif  // Core_Exception_H
