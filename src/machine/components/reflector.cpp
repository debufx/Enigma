#include "reflector.hpp"

/* --  INSTANCES  ----------------------------------------------------------- */
const Reflector Reflector::_A = Reflector("EJMZALYXVBWFCRQUONTSPIKHGD");
const Reflector Reflector::_B = Reflector("YRUHQSLDPXNGOKMIEBFZCWVJAT");
const Reflector Reflector::_C = Reflector("FVPJIAOYEDRZXWGCTKUQSBNMHL");

/* --  CONSTRUCTOR  --------------------------------------------------------- */
Reflector::Reflector(const std::string& str):
_seq(to_sequence(str)) {
	if (!check(str)) std::cerr << "attention: Reflector: sequence incorrecte" << std::endl;
}

/* --  SETTERS  ------------------------------------------------------------- */
bool Reflector::set(Letter l1, Letter l2) {
	bool res = true;
	// if the letters weren't already swapped
	if (_seq[l1.value()] == l1 && _seq[l2.value()] == l2) {
		// swap them
		_seq[l1.value()] = l2;
		_seq[l2.value()] = l1;

		res = false;
	}

	return res;
}

/* --  ENIGMA UI  ----------------------------------------------------------- */
Letter Reflector::encode(Letter l) {
	return _seq[l.value()];
}

/* --  OTHERS  -------------------------------------------------------------- */
void Reflector::display(std::ostream& os) const {
	os << from_sequence(_seq);
}

/* --  OPERATORS  ----------------------------------------------------------- */
Reflector& Reflector::operator=(const Reflector& r) {
	if (&r != this) {
		_seq = r._seq;
	}

	return *this;
}

/* --  PRIVATE METHODS  ----------------------------------------------------- */
bool Reflector::check(const std::string& str) const {
	bool test = Letter::check_unicity(str);
	unsigned n = _seq.size();

	// test reflection
	n /= 2;
	for (unsigned i = 0; test && i < n; ++i) {
		// test = str[str[i] - 'A'] == 'A' + i; // TODO: corriger le warning
	}

	return test;
}
