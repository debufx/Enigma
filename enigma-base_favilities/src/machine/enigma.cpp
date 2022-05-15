#include "enigma.hpp"
#include <fstream>

/* --  CONSTRUCTOR  --------------------------------------------------------- */
// Enigma::Enigma()

/* --  SETTERS  ------------------------------------------------------------- */
void Enigma::set_plugboard(const Plugboard& p) {
	_plugboard = p;
}

bool Enigma::set_plugboard(Letter l1, Letter l2) {
	return _plugboard.set(l1, l2);
}

void Enigma::add_rotor(const Rotor& r) {
	_rotors.add_rotor(r);
}

void Enigma::add_rotor(const std::string& str, int notch, Letter rs, Letter ground) {
	_rotors.add_rotor(str, notch, rs, ground);
}

void Enigma::set_reflector(const Reflector& r) {
	_reflector = r;
}

/* --  ENIGMA UI  ----------------------------------------------------------- */
Letter Enigma::encode(Letter c) {
	// _rotors.rotate();

	c = _plugboard.encode(c);
	c = _rotors.encode(c);
	c = _reflector.encode(c);
	c = _rotors.decode(c);
	c = _plugboard.encode(c);

	_rotors.rotate();

	return c;
}

std::vector<Letter> Enigma::encode(const std::vector<Letter>& v) {
	std::vector<Letter> res = v;

	for (unsigned i = 0; i < v.size(); ++i) {
		res[i] = encode(v[i]);
	}

	return res;
}

std::string Enigma::encode(const std::string& str) {
	// return from_sequence(encode(to_sequence(str)));
	std::string res(str);

	for (unsigned i = 0; i < str.size(); ++i) {
		res[i] = encode(Letter(str[i])).character();
	}

	return res;
}

void Enigma::reset() {
	_rotors.reset();
}
