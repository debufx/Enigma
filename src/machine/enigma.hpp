#ifndef ENIGMA_HPP
#define ENIGMA_HPP

#include <vector>

#include "letter.hpp"
#include "components/plugboard.hpp"
#include "components/rotor.hpp"
#include "components/scrambler.hpp"
#include "components/reflector.hpp"

/******************************************************************************\
|* CLASS : Enigma																															*|
|*																																						*|
|* encode: R <-- I																														*|
|* decode: R --> O																														*|
\******************************************************************************/
class Enigma {
private:
/* --  ARGUMENTS  ----------------------------------------------------------- */
	Plugboard   _plugboard;  // !< plugboard
	Scrambler   _rotors;     // !< rotor container
	Reflector   _reflector;  // !< reflector

public:
/* --  CONSTRUCTOR  --------------------------------------------------------- */
	/*\
	 *  /brief constructor
	\*/
	Enigma(): _plugboard(), _rotors(), _reflector() {}

/* --  SETTERS  ------------------------------------------------------------- */
	void set_plugboard(const Plugboard&);
	bool set_plugboard(Letter l1, Letter l2);
	void add_rotor(const Rotor&);
	void add_rotor(const std::string& str, int notch, Letter rs = 0, Letter ground = 'A');
	void set_reflector(const Reflector&);

	unsigned size() { return _rotors.size(); }

/* --  ENIGMA UI  ----------------------------------------------------------- */
	Letter encode(Letter);
	std::vector<Letter> encode(const std::vector<Letter>&);
	std::string encode(const std::string&);
	void reset();
};

#endif
