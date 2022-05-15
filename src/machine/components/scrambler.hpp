#ifndef ROTORCONTAINER_HPP
#define ROTORCONTAINER_HPP

#include <vector>
#include <string>

#include "rotor.hpp"

/******************************************************************************\
|* CLASS : Scrambler                                                          *|
|*                                                                            *|
|* encode: R <-- I                                                            *|
|* decode: R --> O                                                            *|
\******************************************************************************/
class Scrambler {
private:
/* --  ARGUMENTS  ----------------------------------------------------------- */
	std::vector<Rotor> _rotors;  // !< rotors container

public:
/* --  CONSTRUCTOR  --------------------------------------------------------- */
	/*\
	 *  /brief constructor
	\*/
	Scrambler(): _rotors() {}

/* --  GETTERS  ------------------------------------------------------------- */
	/*\
	 *  /brief gets the number of rotors added
	\*/
	unsigned size() { return _rotors.size(); }

/* --  CONFIG  -------------------------------------------------------------- */
	/*\
	 *  /brief adds a rotor to the scrambler
	 *
	 * /param r rotor to add
	 *
	 * /param other: Rotor constructor parameters
	\*/
	void add_rotor(const Rotor& r);
	void add_rotor(const std::string& str, int notch, Letter rs = 0, Letter ground = 'A');

/* --  ENIGMA UI  ----------------------------------------------------------- */
	/*\
	 *  /brief encodes/decodes a single letter
	 *
	 *  /param l letter to encode/decode
	 *  /return encoded/decoded letter
	\*/
	Letter encode(Letter l) const;
	Letter decode(Letter l) const;

	/*\
	 *  /brief rotates the rotors
	\*/
	void rotate();

	/*\
	 *  /brief resets the rotors to their initial state
	\*/
	void reset();

/* --  OTHERS  -------------------------------------------------------------- */
	/*\
	 *  /brief displays the rotor settings on a stream
	 *
	 *  /param os display stream
	\*/
	void display(std::ostream&  os) const;

/* --  OPERATORS  ----------------------------------------------------------- */
	/*\
	 * /brief gets one of the added rotors
	 *
	 * /param i index of the rotor
	 * /output a rotor
	\*/
	Rotor& operator[](unsigned i);
};

#endif
