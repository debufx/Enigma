#ifndef ROTOR_HPP
#define ROTOR_HPP

#include <vector>
#include <iostream>

#include "../letter.hpp"

/******************************************************************************\
|* CLASS : Rotor                                                              *|
|*                                                                            *|
|* encode: R <-- I                                                            *|
|* decode: R --> O                                                            *|
\******************************************************************************/
class Rotor {
private:
/* --  ARGUMENTS  ----------------------------------------------------------- */
	// encoding data
	std::vector<int>    _encoding_shift;  // !< encoding vector
	std::vector<int>    _decoding_shift;  // !< decoding vector

	// rotors parameters
	std::vector<Letter> _input_string;    // !< input string from the constructor
	Letter              _ring_setting;    // !< letter corresponding to the 0 position
	int                 _notch;           // !< next rotor rotates when _ground == _notch
	// TODO: pouvoir utiliser plusieurs notchs

	// state
	Letter              _org_ground;      // !< original ground
	Letter              _ground;          // !< visible letter of the rotor

public:
/* --  CONSTRUCTOR  --------------------------------------------------------- */
	/*\
	 *  /brief constructor
	 *
	 *	/param str     encoding string
	 *  /param rs      letter in the 0 position
	 *  /param notch   rotation position
	 *  /param ground  initial visible letter
	\*/
	Rotor(const std::string& str, int notch, Letter rs = 0, Letter ground = 'A');

/* --  GETTERS  ------------------------------------------------------------- */
	/*\
	 *  /brief gets the current ground
	 *
	 *  /return current ground
	\*/
	Letter ground() const { return _ground; }

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
	 *  /brief rotates the rotor
	 *
	 *  /return true if the rotor hits a notch
	\*/
	bool rotate();

	/*\
	 *  /brief resets the rotor to its initial state
	\*/
	void reset();

/* --  OTHERS  -------------------------------------------------------------- */
	/*\
	 *  /brief displays the rotor settings on a stream
	 *
	 *  /param os display stream
	\*/
	void display(std::ostream& os = std::cout) const;

	/*\
	 *  /brief tests if this has the same parameters as another rotor
	 *
	 *  /param r another rotor
	\*/
	bool equals(const Rotor& r) const;

private:
/* --  PRIVATE METHODS  ----------------------------------------------------- */
	/*\
	 *  /brief checks if an input string is valid (unicity)
	 *
	 *  /param str input string
	\*/
	bool check(const std::string& str) const;

	/*\
	 *  /brief computes the corresponding shifts from the input string
	 *
	 *  /param str input string
	\*/
	void set_shifts(const std::string& str);

public:
/* --  EXISTING ROTORS  ----------------------------------------------------- */
	/*\
	 *  /brief creates one of the original Enigma Rotor
	 *
	 *  /param rs ring setting
	 *  /param ground ring ground
	\*/
	static Rotor DUMMY(Letter rs = 0, Letter ground = 'A');  // !< Dummy rotor
	static Rotor I(Letter rs = 0, Letter ground = 'A');      // !< Enigma I rotor
	static Rotor II(Letter rs = 0, Letter ground = 'A');     // !< Enigma I rotor
	static Rotor III(Letter rs = 0, Letter ground = 'A');    // !< Enigma I rotor
	static Rotor IV(Letter rs = 0, Letter ground = 'A');     // !< M3 Army rotor
	static Rotor V(Letter rs = 0, Letter ground = 'A');      // !< M3 Army rotor
	static Rotor VI(Letter rs = 0, Letter ground = 'A');     // !< M3 & M4 Naval rotor
	static Rotor VII(Letter rs = 0, Letter ground = 'A');    // !< M3 & M4 Naval rotor
	static Rotor VIII(Letter rs = 0, Letter ground = 'A');   // !< M3 & M4 Naval rotor
};

#endif
