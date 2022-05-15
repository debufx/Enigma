#include "letter.hpp"

/* --  CONSTRUCTORS  -------------------------------------------------------- */
// Letter::Letter()

Letter::Letter(int pos):
_pos(check(pos) ? pos : -1) {}

Letter::Letter(char c):
_pos(check(c) ? c-'A' : -1) {}

Letter::Letter(unsigned pos):
_pos(check(pos) ? pos : -1) {}

/* --  GETTERS/SETTERS  ----------------------------------------------------- */
char Letter::character() const {
	return 'A' + _pos;
}

void Letter::character(char c) {
	_pos = check(c) ? c-'A' : 0;
}

int Letter::value() const {
	return _pos;
}

void Letter::value(int pos) {
	_pos = check(pos) ? pos : 0;
}

bool Letter::equals(const Letter& l) const {
	return _pos == l._pos;
}

/**  OPERATORS  ***************************************************************/
Letter& Letter::operator=(char c) {
	_pos = check(c) ? c-'A' : 0;
	return *this;
}
Letter& Letter::operator=(int pos) {
	_pos = check(pos) ? pos : 0;
	return *this;
}

Letter& Letter::operator=(unsigned pos) {
	_pos = check(pos) ? pos : 0;
	return *this;
}

Letter& Letter::operator+=(int pos) {
	_pos += pos;
	fit();
	return *this;
}

Letter& Letter::operator-=(int pos) {
	_pos -= pos;
	fit();
	return *this;
}

Letter& Letter::operator++() {
	return operator+=(1);
}

Letter& Letter::operator--() {
	return operator-=(1);
}

Letter Letter::operator+(int i) {
	Letter res = *this;
	res += i;
	return res;
}

Letter Letter::operator-(int i) {
	Letter res = *this;
	res -= i;
	return res;
}

/**  EXTERN  ******************************************************************/
std::ostream& operator<<(std::ostream& os, const Letter& l) {
	os << l.character();
	return os;
}

bool operator==(const Letter& l1, const Letter& l2) {
	return l1.equals(l2);
}

bool operator==(const Letter& l, char c) {
	return l.character() == c;
}

bool operator==(char c, const Letter& l) {
	return l == c;
}

bool operator==(const Letter& l, int pos) {
	return l.value() == pos;
}

bool operator==(int pos, const Letter& l) {
	return l == pos;
}

/**  CONTAINER  ***************************************************************/
std::vector<Letter> to_sequence(const std::string& str) {
	std::vector<Letter> res(str.size());

	for (unsigned i = 0; i < str.size(); ++i) {
		res[i] = str[i];
	}

	return res;
}

std::string from_sequence(const std::vector<Letter>& v) {
	std::string res = "";

	for (unsigned i = 0; i <  v.size(); ++i) {
		res += v[i].character();
	}

	return res;
}

bool Letter::check_unicity(std::string str) {
	for (unsigned i = 0; i < str.size(); ++i) {
		for (unsigned j = i+1; j < str.size(); ++j) {
			if (str[i] == str[j]) {
				return false;
			}
		}
	}

	return true;
}

/* --  PROTECTED METHODS  --------------------------------------------------- */
bool Letter::check(char c) const {
	return 'A' <= c && c <= 'Z';
}

bool Letter::check(int pos) const {
	return 0 <= pos && pos <= 25;
}

bool Letter::check(unsigned pos) const {
	return pos <= 25;
}

void Letter::fit() {
	while (_pos < 0) {
		_pos += 26;
	}

	while (_pos >= 26) {
		_pos -= 26;
	}
}
