#include <iomanip>
#include <cstring>
#include <iostream>

class String {
private:
    char* str;
    friend std::ostream& operator<< (std::ostream &, String &);
	friend std::istream& operator>> (std::istream &, String &); 
public:
    String(const char* s = NULL);
    String(const String &other);
    ~String(void);
    String & operator =(const String& other); 
	String operator +(const String &other) const; 
	bool operator == (const String &);
	char& operator[](unsigned int);
    void reverse(int, int);
	size_t size();
};

String::String(const char* s) {
    if (s == NULL) {
		str = 0;
    } else {
		str = new char[strlen(str) + 1];
		strcpy(str, s);
	}
}

String& String::operator = (const String& other) {
	if(this != &other) {
		delete[] str;
		if(other.str == NULL) { 
			str = 0;
        } else {
            str = new char[strlen(other.str) + 1];
            strcpy(str, other.str);
        }
	}
	return *this;
}

String String::operator + (const String &other) const {
	String newString;
	if(other.str == NULL) {
		newString = *this;
    } else if(str == NULL) {
		newString = other;
    } else {
		newString.str = new char[strlen(str) + strlen(other.str) + 1];
		strcpy(newString.str, str);
		strcat(newString.str, other.str);
	}
	return newString;
}

bool String::operator ==(const String &s) {
	if (strlen(s.str) != strlen(str)) {
        return false;
    }
	return strcmp(str, s.str) ? false : true;
}

char& String::operator[](unsigned int d) {
	if (d <= strlen(str)) {
		return str[d];
    }
}

std::ostream& operator <<(std::ostream& os, String& str) {
	os << str.str;
	return os;
}

std::istream &operator >>(std::istream &input, String &s) {
	char temp[255]; 
	input >> std::setw(255) >> temp;
	s = temp; 
	return input; 
}


String::String(const String &other) {
    if (other.str == NULL) {
        str = 0;
    } else {
		str = new char[strlen(other.str) + 1];
		strcpy(str, other.str);
	}
}

String::~String() {
    if(str) {
        delete [] str;
    }
}

void String::reverse(int l, int r) {
    if(l < 0 || r < 0 || l > r || r > (int)strlen(str)) {
        std::runtime_error("区间范围异常!");
        return;
    }
    if(str == NULL) return;
    for(int i = l, j = r; i < j; i ++, j --) {
        std::swap(str[i], str[j]);
    }
}

size_t String::size() {
    return strlen(str);
}


int main() {
    String s1("12345"), s2;
    s2 = s1;
    s2 = s1 + "678";
    std::cout << s1 << "\n" << s2 << "\n";
    std::cout << s1.size() << " " << s2.size() << std::endl;
    std::cout << s1[0] << " " << s2[1] << "\n";
    s1.reverse(1, 3);
    std::cout << s1 << "\n";
}