#ifndef LETTER_HPP
#define LETTER_HPP

#include <iostream>
#include <vector>

/******************************************************************************\
|* CLASS : Letter                                                             *|
|*                                                                            *|
\******************************************************************************/
class Letter {
protected:
/* --  ATTRIBUTES  ---------------------------------------------------------- */
	int _pos; // !< encodes a letter : 'A' --> 0 ; 'B' --> 1 ; ... ; 'Z' --> 25

/* --  PROTECTED METHODS  --------------------------------------------------- */
	/*\
	 * /brief validates a char/int/unsigned to be between 0 and 25
	 *
	 * /param c/pos the letter to check
	 * /return true if c/pos is between 0 and 25
	\*/
	bool check(char c) const;
	bool check(int pos) const;
	bool check(unsigned pos) const;

	/*\
	 * /brief fits the current letter within 0 and 25
	\*/
	void fit();

public:
/* --  CONSTRUCTORS  -------------------------------------------------------- */
	/*\
	 * /brief default constructor
	\*/
	Letter() {}
	Letter(int pos);
	Letter(char c);
	Letter(unsigned pos);

/* --  GETTERS/SETTERS  ----------------------------------------------------- */
	char character() const;
	void character(char c);
	int  value() const;
	void value(int pos);

	bool equals(const Letter& l) const;

	// operateurs
	Letter& operator= (char c);
	Letter& operator= (int pos);
	Letter& operator= (unsigned pos);
	Letter& operator+=(int pos);
	Letter& operator-=(int pos);
	Letter& operator++();
	Letter& operator--();
	Letter  operator+ (int i);
	Letter  operator- (int i);

	// TODO: operator-(Letter l);

	static bool check_unicity(std::string str); // true if ok
};

std::ostream& operator<<(std::ostream& os, const Letter& l);
bool operator==(const Letter& l1, const Letter& l2);
bool operator==(const Letter& l, char c);
bool operator==(char c, const Letter& l);
bool operator==(const Letter& l, int pos);
bool operator==(int pos, const Letter& l);

// conteneur
std::vector<Letter> to_sequence(const std::string& str);
std::string from_sequence(const std::vector<Letter>& v);
#endif
