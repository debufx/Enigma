#include <algorithm>
#include "rotor.hpp"

/* --  CONSTRUCTOR  --------------------------------------------------------- */
Rotor::Rotor(const std::string& str, int notch, Letter rs, Letter ground):
_encoding_shift(), _decoding_shift(),                  // encoding data
_input_string(), _ring_setting(rs), _notch(notch+1),  // rotors parameters
_org_ground(ground), _ground(ground) {               // current state
	set_shifts(str);

	// set ring settings
	std::rotate(_encoding_shift.begin(), _encoding_shift.end()-rs.value(), _encoding_shift.end());
	std::rotate(_decoding_shift.begin(), _decoding_shift.end()-rs.value(), _decoding_shift.end());
}

/* --  GETTERS  ------------------------------------------------------------- */
// Letter Rotor::ground()

/* --  ENIGMA UI  ----------------------------------------------------------- */
Letter Rotor::encode(Letter l) const {
	Letter res = l + _ground.value();

	return l + _encoding_shift[res.value()];
}

Letter Rotor::decode(Letter l) const {
	Letter res = l + _ground.value();

	return l + _decoding_shift[res.value()];
}

bool Rotor::rotate() {
	return (++_ground == _notch);
}

void Rotor::reset() {
	_ground = _org_ground;
}

/* --  OTHERS  -------------------------------------------------------------- */
void Rotor::display(std::ostream& os) const {

	// print encoding data
	os << "encoding data:" << std::endl;
		// print encoding shift
		os << "  encode: [ ";
		for (unsigned i = 0; i < _encoding_shift.size(); ++i) {
			os << _encoding_shift[i] << ", ";
		}
		os << "]" << std::endl;

		// print decoding shift
		os << "  decode: [ ";
		for (unsigned i = 0; i < _decoding_shift.size(); ++i) {
			os << _decoding_shift[i] << ", ";
		}
		os << "]" << std::endl;
	os << std::endl;

	// print rotors parameters
	os << "rotor parameters:" << std::endl;
		os << "  ring setting: " << _ring_setting << std::endl;
		os << "  notch:        " << _notch << std::endl;
	os << std::endl;

	// print state
	os << "state:" << std::endl;
		os << "  initial: " << _org_ground << std::endl;
		os << "  current: " << _ground << std::endl;
	os << std::endl;
}

bool Rotor::equals(const Rotor& r) const {
	return (this == &r) ||
		(_encoding_shift == r._encoding_shift &&
		_ring_setting == r._ring_setting &&
		_notch == r._notch);
}

/* --  PRIVATE METHODS  ----------------------------------------------------- */
bool Rotor::check(const std::string& str) const {
	return Letter::check_unicity(str);
}

void Rotor::set_shifts(const std::string& str) {
	_input_string = to_sequence(str);

	if (check(str)) {
		_encoding_shift.resize(str.size());
		_decoding_shift.resize(str.size());

		// compute shifts
		for (unsigned i = 0; i < str.size(); ++i) {
			// encoding shifts
			_encoding_shift[i] = _input_string[i].value() - i;

			// decoding shifts
			_decoding_shift[_input_string[i].value()] = -_encoding_shift[i];
		}
	}
}

/* --  EXISTING ROTORS  ----------------------------------------------------- */
Rotor Rotor::DUMMY(Letter rs, Letter ground) {
	return Rotor("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 25, rs, ground);
}

Rotor Rotor::I(Letter rs, Letter ground) {
	return Rotor("EKMFLGDQVZNTOWYHXUSPAIBRCJ", 16, rs, ground);
}

Rotor Rotor::II(Letter rs, Letter ground) {
	return Rotor("AJDKSIRUXBLHWTMCQGZNPYFVOE",  4, rs, ground);
}

Rotor Rotor::III(Letter rs, Letter ground) {
	return Rotor("BDFHJLCPRTXVZNYEIWGAKMUSQO", 21, rs, ground);
}

Rotor Rotor::IV(Letter rs, Letter ground) {
	return Rotor("ESOVPZJAYQUIRHXLNFTGKDCMWB",  9, rs, ground);
}

Rotor Rotor::V(Letter rs, Letter ground) {
	return Rotor("VZBRGITYUPSDNHLXAWMJQOFECK", 25, rs, ground);
}

Rotor Rotor::VI(Letter rs, Letter ground) {
	return Rotor("JPGVOUMFYQBENHZRDKASXLICTW", 25, rs, ground);
}

Rotor Rotor::VII(Letter rs, Letter ground) {
	return Rotor("NZJHGRCXMYSWBOUFAIVLPEKQDT", 25, rs, ground);
}

Rotor Rotor::VIII(Letter rs, Letter ground) {
	return Rotor("FKQHTLXOCBJSPDZRAMEWNIUYGV", 25, rs, ground);
}
