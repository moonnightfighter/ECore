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

#ifndef  Core_Timespan_H
#define  Core_Timespan_H


#include "ECore/Core/Core.h"
#include "ECore/Core/Timestamp.h"


namespace Core {


class Core_API Timespan
 {
public:
	typedef Timestamp::TimeDiff TimeDiff;

	Timespan();
	Timespan(TimeDiff microseconds);
	Timespan(long seconds, long microseconds);
	Timespan(int days, int hours, int minutes, int seconds, int microseconds);
	Timespan(const Timespan& timespan);
	~Timespan();

	Timespan& operator = (const Timespan& timespan);
	Timespan& operator = (TimeDiff microseconds);
	Timespan& assign(int days, int hours, int minutes, int seconds, int microseconds);	
	Timespan& assign(long seconds, long microseconds);

	void swap(Timespan& timespan);

	bool operator == (const Timespan& ts) const;
	bool operator != (const Timespan& ts) const;
	bool operator >  (const Timespan& ts) const;
	bool operator >= (const Timespan& ts) const;
	bool operator <  (const Timespan& ts) const;
	bool operator <= (const Timespan& ts) const;

	bool operator == (TimeDiff microseconds) const;
	bool operator != (TimeDiff microseconds) const;
	bool operator >  (TimeDiff microseconds) const;
	bool operator >= (TimeDiff microseconds) const;
	bool operator <  (TimeDiff microseconds) const;
	bool operator <= (TimeDiff microseconds) const;
	
	Timespan operator + (const Timespan& d) const;
	Timespan operator - (const Timespan& d) const;
	Timespan& operator += (const Timespan& d);
	Timespan& operator -= (const Timespan& d);

	Timespan operator + (TimeDiff microseconds) const;
	Timespan operator - (TimeDiff microseconds) const;
	Timespan& operator += (TimeDiff microseconds);
	Timespan& operator -= (TimeDiff microseconds);

	int days() const;
	int hours() const;
	int totalHours() const;
	int minutes() const;
	int totalMinutes() const;
	int seconds() const;
	int totalSeconds() const;	
	int milliseconds() const;
	TimeDiff totalMilliseconds() const;	
	int microseconds() const;
	int useconds() const;
	TimeDiff totalMicroseconds() const;

	static const TimeDiff MILLISECONDS;
	static const TimeDiff SECONDS;
	static const TimeDiff MINUTES; 
	static const TimeDiff HOURS;
	static const TimeDiff DAYS;

private:
	TimeDiff _span;
};


//
// inlines
//
inline int Timespan::days() const
{
	return int(_span/DAYS);
}


inline int Timespan::hours() const
{
	return int((_span/HOURS) % 24);
}

	
inline int Timespan::totalHours() const
{
	return int(_span/HOURS);
}

	
inline int Timespan::minutes() const
{
	return int((_span/MINUTES) % 60);
}

	
inline int Timespan::totalMinutes() const
{
	return int(_span/MINUTES);
}

	
inline int Timespan::seconds() const
{
	return int((_span/SECONDS) % 60);
}

	
inline int Timespan::totalSeconds() const
{
	return int(_span/SECONDS);
}

	
inline int Timespan::milliseconds() const
{
	return int((_span/MILLISECONDS) % 1000);
}

	
inline Timespan::TimeDiff Timespan::totalMilliseconds() const
{
	return _span/MILLISECONDS;
}

	
inline int Timespan::microseconds() const
{
	return int(_span % 1000);
}


inline int Timespan::useconds() const
{
	return int(_span % 1000000);
}

	
inline Timespan::TimeDiff Timespan::totalMicroseconds() const
{
	return _span;
}


inline bool Timespan::operator == (const Timespan& ts) const
{
	return _span == ts._span;
}


inline bool Timespan::operator != (const Timespan& ts) const
{
	return _span != ts._span;
}


inline bool Timespan::operator >  (const Timespan& ts) const
{
	return _span > ts._span;
}


inline bool Timespan::operator >= (const Timespan& ts) const
{
	return _span >= ts._span;
}


inline bool Timespan::operator <  (const Timespan& ts) const
{
	return _span < ts._span;
}


inline bool Timespan::operator <= (const Timespan& ts) const
{
	return _span <= ts._span;
}


inline bool Timespan::operator == (TimeDiff microseconds) const
{
	return _span == microseconds;
}


inline bool Timespan::operator != (TimeDiff microseconds) const
{
	return _span != microseconds;
}


inline bool Timespan::operator >  (TimeDiff microseconds) const
{
	return _span > microseconds;
}


inline bool Timespan::operator >= (TimeDiff microseconds) const
{
	return _span >= microseconds;
}


inline bool Timespan::operator <  (TimeDiff microseconds) const
{
	return _span < microseconds;
}


inline bool Timespan::operator <= (TimeDiff microseconds) const
{
	return _span <= microseconds;
}


inline void swap(Timespan& s1, Timespan& s2)
{
	s1.swap(s2);
}


} // namespace Core


#endif // Core_Timespan_H
