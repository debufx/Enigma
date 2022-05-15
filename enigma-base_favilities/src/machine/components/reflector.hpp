#ifndef REFLECTOR_HPP
#define REFLECTOR_HPP

#include <string>
#include <iostream>
#include "../letter.hpp"

/******************************************************************************\
|* CLASS : Reflector                                                          *|
|*                                                                            *|
\******************************************************************************/
class Reflector {
private:
/* --  ARGUMENTS  ----------------------------------------------------------- */
	std::vector<Letter> _seq; // !< encoding sequence

/* --  INSTANCES  ----------------------------------------------------------- */
	static const Reflector _A; // !< original A reflector
	static const Reflector _B; // !< original B reflector
	static const Reflector _C; // !< original C reflector

public:
/* --  CONSTRUCTOR  --------------------------------------------------------- */
	/*\
	 *  /brief constructor
	 *
	 *  /param str swap sequence
	 *  /TODO: use variadic parameter
	\*/
	Reflector(const std::string& str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

/* --  SETTERS  ------------------------------------------------------------- */
	/*\
	 *  /brief swaps two letters
	 *
	 *  /param l1,l2 letters to connect
	 *  /return true if the pairing is rejected
	\*/
	bool set(Letter l1, Letter l2);

/* --  ENIGMA UI  ----------------------------------------------------------- */
	/*\
	 *  /brief encodes a letter
	 *
	 *  /param l letter to encode
	 *  /return the encoded letter
	\*/
	Letter encode(Letter l);

/* --  OTHERS  -------------------------------------------------------------- */
	/*\
	 *  /brief displays the current state
	\*/
	void display(std::ostream& os = std::cout) const;

/* --  OPERATORS  ----------------------------------------------------------- */
	/*\
	 * /brief assigns a copy of another reflector to the current one
	 *
	 * /param r a reflector
	 * /output a copy of r
	\*/
	Reflector& operator=(const Reflector& r);

private:
/* --  PRIVATE METHODS  ----------------------------------------------------- */
	/*\
	 *  /brief checks if an input string is valid (unicity, reflexivity)
	 *
	 *  /param str input string
	\*/
	bool check(const std::string&) const;

public:
/* --  EXISTING REFLECTORS  ------------------------------------------------- */
	// TODO comments ?
	static const Reflector A() { return _A; }
	static const Reflector B() { return _B; }
	static const Reflector C() { return _C; }
};

#endif
