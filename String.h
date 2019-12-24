#include <cstring>
#include <iostream>
class String {
public:
	String()
	:ptr(ch), sz(0)
	{
		ch[0] = 0;
	}

	String(const char* p) 
	:sz(strlen(p)), ptr((sz <= short_max) ? ch: new char[sz+1]),
	space(0)
	{
		strcpy(ptr, p);
	}

	String(const String& s) 
	{
		copy_from(s);
	}	
	String(String&& s) 
	{
		move_from(s);
	}

	String& operator=(const String& s) 
	{
		if(this == &s) 
			return *this;

		char* p = (sz > short_max) ? ptr : 0;
		copy_from(s);
		delete[] p;
		return *this;
	}


	String& operator=(String&& s) 
	{
		if(this == &s) return *this;

		if(sz > short_max)
			delete[] ptr;
		move_from(s);
		return *this;
	}



	char& operator[](int n) 
	{
		return ptr[n];
	}
	char operator[](int n) const 
	{
		return ptr[n];
	}

	char& at(int n) 
	{
		check(n);
		return ptr[n];
	}

	char at(int n) const 
	{
		check(n);
		return ptr[n];
	} 	

	String& operator+=(char ch);

	char* c_str() 
	{
		return ptr;
	}

	const char* c_str() const 
	{
		return ptr;
	}

	int size() const 
	{
		return sz;
	}	

	int capacity() const 
	{
		return (sz <= short_max) ? short_max : sz + space;
	}	

	~String() 
	{
		if(sz > short_max) 
		{
			delete[] ptr;
		}
	}


 
private:
	static const int short_max = 15;
	int sz;
	char* ptr;
	union
	{
		int space;
		char ch[short_max + 1];
	};

	void check (int n) const
	{
		if(n < 0 or n > short_max) 
		{
			throw std::out_of_range("String::at()");
		}
	}

	void copy_from(const String& s);
	void move_from(String& s);

};

String operator+(const String& a, const String& b);
String& operator+=(String& a, const String& b);

bool operator==(const String& a, const String& b);
bool operator!=(const String& a, const String& b);

std::istream& operator>>(std::istream& inp, String& s);
std::ostream& operator<<(std::istream& outp, const String& s);

char* begin(String& s) {
	return s.c_str();
}

char* end(String& s) {
	return s.c_str() + s.size();
}

const char* begin(const String& s) {
	return s.c_str();
}
const char* end(const String& s) {
	return s.c_str() + s.size();
}


String operator"" _s(const char* p, size_t) {
	return String(p);
}



