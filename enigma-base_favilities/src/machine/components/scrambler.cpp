#include "scrambler.hpp"

/* --  CONSTRUCTOR  --------------------------------------------------------- */
// Scrambler::Scrambler()

/* --  GETTERS  ------------------------------------------------------------- */
// unsigned Scrambler::size()

/* --  CONFIG  -------------------------------------------------------------- */
void Scrambler::add_rotor(const Rotor& r) {
	_rotors.push_back(r);
}

void Scrambler::add_rotor(const std::string& str, int notch, Letter rs, Letter ground) {
	_rotors.emplace_back(str, notch, rs, ground);
}

/* --  ENIGMA UI  ----------------------------------------------------------- */
Letter Scrambler::encode(Letter l) const {
	for (auto rotor = _rotors.rbegin(); rotor != _rotors.rend(); ++rotor) {
		l = rotor->encode(l);
	}

	return l;
}

Letter Scrambler::decode(Letter l) const {
	for (auto rotor = _rotors.begin(); rotor != _rotors.end(); ++rotor) {
		l = rotor->decode(l);
	}

	return l;
}

void Scrambler::rotate() {
	if (_rotors.size() != 3) {
		// generic rotation
		for (auto it = _rotors.rbegin(); it->rotate() && it != _rotors.rend(); ++it);
	} else {
		// double-stepping
		auto it = _rotors.rbegin();
		if (it->rotate()) {
			++it;
			if (it->rotate()) {
				it->rotate();
				++it;
				it->rotate();
			}
		}
	}
}

void Scrambler::reset() {
	for (auto rotor = _rotors.begin(); rotor != _rotors.end(); ++rotor) {
		rotor->reset();
	}
}

/* --  OTHERS  -------------------------------------------------------------- */
void Scrambler::display(std::ostream& os) const {
	for (auto i = _rotors.begin(); i != _rotors.end(); ++i) {
		i->display(os);
	}
}

/* --  OPERATORS  ----------------------------------------------------------- */
Rotor& Scrambler::operator[](unsigned i) {
	return _rotors[i];
}
