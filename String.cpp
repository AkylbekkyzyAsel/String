#include "String.h"
#include <iostream>
using namespace std;

char* expand(const char* p, int n) {
	char* q = new char[n];
	strcpy(q, p);
	return q;
}

String& String::operator+=(char ch) {
	if(sz == short_max) {
		int n = sz + sz + 2;
		ptr = expand(ptr, n);
		space = n - sz - 2;
	}
	else if(sz > short_max) {
		if(space == 0) {
			int n = sz + sz + 2;
			char* p = expand(ptr, n);
			delete[] ptr;
			ptr = p;
			space = n - sz - 2;
		}
		else 
			space--;
	}
	ptr[sz] = ch;
	ptr[++sz] = 0;
	return *this;
}

void String::copy_from(const String& s) 
{
	if(s.sz <= short_max) {
		memcpy(this, &s, sizeof(s));
		ptr = ch;
	}
	else {
		ptr = expand(s.ptr, s.sz + 1);
		sz = s.sz;
		space = 0;
	} 
}
void String::move_from(String& s)
{
	if(sz > short_max) {
		memcpy(this, &s, sizeof(s));
		ptr = ch;
	}
	else {
		ptr = s.ptr;
		sz = s.sz;
		space = s.space;
		s.ptr = ch;
		s.sz = 0;
		s.ch[0] = 0;
	}
}

String& operator+= (String& a, const String& b) {
	for(auto x : b) {
		a += b;
	}
	return a;
}

String operator+(const String& a, const String& b) {
	String res(a);
	res += b;
	return res;
}

bool operator==(const String& a, const String& b) {
	if(a.size() != b.size())
		return false;
	for(int i = 0;  i != a.size(); i++) {
		if(a[i] != b[i])
			return false;
	}
	return true;
}
bool operator!=(const String& a, const String& b) {
	return !(a == b);
}

ostream& operator<<(ostream& outp, const String& s) {
	return outp << s.c_str();;
}

istream& operator>>(istream& inp, String& s) {
	s = "";
	inp >> ws;
	char ch;
	if(inp.get(ch) and !(isspace(ch))) {
		s += ch;
	}
	return inp;
}


