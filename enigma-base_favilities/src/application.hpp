#ifndef __CONSOLE_APP_HPP__
#define __CONSOLE_APP_HPP__

#include <climits>
#include <iostream>
#include <string>
#include <vector>

#include "machine/enigma.hpp"

#define UNDEF UINT_MAX

/******************************************************************************\
|* CLASS : Application                                                        *|
|*                                                                            *|
\******************************************************************************/
class Application {
private:
/* --  ATTRIBUTES  ---------------------------------------------------------- */
	// Display
	std::string        _prompt = " > ";
	// const std::ostream _os;

	// Machines
	std::vector<Enigma>      _machines;
	std::vector<std::string> _names;
	unsigned                 _index = UNDEF;

	// Data
	std::string _in_text = "";
	std::string _out_text = "";

public:
/* --  CONSTRUCTORS  -------------------------------------------------------- */
	Application() {}

/* --  GETTERS  ------------------------------------------------------------- */
	const std::string& in_text() const { return _in_text; }
	const std::string& out_text() const { return _out_text; }
	// const std::ostream& os() const { return _os; }

/* --  PARSER  -------------------------------------------------------------- */
	bool parse(const std::string& str);

/* --  RUN  ----------------------------------------------------------------- */
	void run();
	void init();

/* --  METHODS  ------------------------------------------------------------- */
	void create(const std::vector<std::string>& args);

	void add(const std::vector<std::string>& args);
	void add_rotor(const std::vector<std::string>& args);
	void add_reflector(const std::vector<std::string>& args);

	void set(const std::vector<std::string>& args);
	void set_plugboard(const std::vector<std::string>& args);

	void encode(const std::vector<std::string>& args);
	void reset(const std::vector<std::string>& args);
};

#endif
