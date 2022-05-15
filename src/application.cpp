#include <iterator>
#include <sstream>
#include "application.hpp"
#include "machine/letter.hpp"

/* --  CONSTRUCTORS  -------------------------------------------------------- */
// Application::Application()

/* --  GETTERS  ------------------------------------------------------------- */
// const std::string& in_text() const
// const std::string& out_text() const
// const std::ostream& os() const

/* --  PARSER  -------------------------------------------------------------- */
bool Application::parse(const std::string& str) {
	std::istringstream iss(str);
	std::vector<std::string> args(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

	if (args.size() != 0) {
		if (args[0] == "create") {
			create(args);
		} else if (args[0] == "add") {
			add(args);
		} else if (args[0] == "set") {
			set(args);
		} else if (args[0] == "encode") {
			encode(args);
		} else if (args[0] == "reset") {
			reset(args);
		} else if (args[0] == "q" || args[0] == "quit") {
			if (args.size() == 1) {
				return true;
			} else {
				std::cerr << "unknown arguments" << std::endl;
			}
		} else {
			std::cerr << "incorrect arguments" << std::endl;
		}
	}

	return false;
}

/* --  RUN  ----------------------------------------------------------------- */
void Application::run() {
	init();

	bool quit = false;
	std::string input;

	while (!quit) {
		std::cout << (_index != UNDEF ? _names[_index] : "") << _prompt;
		std::getline(std::cin, input);

		quit = parse(input);
	}
}

void Application::init() {
	system("clear");

	std::cout << "* Enigma Simulator" << std::endl;
	std::cout << "* Projet ZZ2" << std::endl;
	std::cout << std::endl;
}

/* --  METHODS  ------------------------------------------------------------- */
void Application::create(const std::vector<std::string>& args) {
	if (args.size() == 2) {
		_machines.emplace_back();
		_names.push_back(args[1]);
		_index = _machines.size() - 1;
	} else {
		std::cerr << "2 arguments required: create \"name\"" << std::endl;
	}
}

void Application::add(const std::vector<std::string>& args) {
	if (args.size() >= 2) {
		if (_index != UNDEF) {
			if (args[1] == "rotor") {
				add_rotor(args);
			} else if (args[1] == "reflector") {
				add_reflector(args);
			} else {
				std::cerr << "unknown component: " << args[1] << std::endl;
			}
		} else {
			std::cerr << "no machine created or assigned" << std::endl;
		}
	} else {
		std::cerr << "2 or more arguments required: add \"component name\" \"component arguments\"" << std::endl;
	}
}

void Application::add_rotor(const std::vector<std::string>& args) {
	Letter rs('A');
	Letter ground('A');

	if (_machines[_index].size() < 3) {
		if (args.size() >= 3) { // add rotor truc
			if (args.size() >= 4) { // add rotor truc A
				if (args[3].size() == 1) {
					rs = Letter(args[3][0]);

					if (args.size() == 5) { // add rotor truc A B
						if (args[4].size() == 1) {
							rs = Letter(args[4][0]);
						} else {
							std::cerr << "single letter required: " << args[4] << std::endl;
						}
					}
				} else {
					std::cerr << "single letter required: " << args[3] << std::endl;
				}
			}

			/* -------------------------------------------- */
			if (args[2] == "DUMMY") {
				_machines[_index].add_rotor(Rotor::DUMMY(rs, ground));
			} else if (args[2] == "I") {
				_machines[_index].add_rotor(Rotor::I(rs, ground));
			} else if (args[2] == "II") {
				_machines[_index].add_rotor(Rotor::II(rs, ground));
			} else if (args[2] == "III") {
				_machines[_index].add_rotor(Rotor::II(rs, ground));
			} else if (args[2] == "IV") {
				_machines[_index].add_rotor(Rotor::II(rs, ground));
			} else if (args[2] == "V") {
				_machines[_index].add_rotor(Rotor::II(rs, ground));
			} else if (args[2] == "VI") {
				_machines[_index].add_rotor(Rotor::II(rs, ground));
			} else if (args[2] == "VII") {
				_machines[_index].add_rotor(Rotor::II(rs, ground));
			} else if (args[2] == "VIII") {
				_machines[_index].add_rotor(Rotor::II(rs, ground));
			} else {
				std::cerr << "unknown rotor: " << args[2] << std::endl;
			}
			/* -------------------------------------------- */
		} else {
			std::cerr << "3 or more arguments required: add rotor \"rotor ID\" \"ring setting\" \"ground\"" << std::endl;
		}
	} else {
		std::cerr << "only 3 rotors can be added" << std::endl;
	}
}

void Application::add_reflector(const std::vector<std::string>& args) {
	if (args.size() == 3) { // add reflector truc
		if (args[2] == "A") {
			_machines[_index].set_reflector(Reflector::A());
		} else if (args[2] == "B") {
			_machines[_index].set_reflector(Reflector::B());
		} else if (args[2] == "C") {
			_machines[_index].set_reflector(Reflector::C());
		} else {
			std::cerr << "unknown reflector: " << args[2] << std::endl;
		}
	} else {
		std::cerr << "3 arguments required: add reflector \"rotor ID\"" << std::endl;
	}
}

void Application::set(const std::vector<std::string>& args) {
	if (args.size() >= 2) {
		if (_index != UNDEF) {
			if (args[1] == "plugboard") {
				set_plugboard(args);
			} else {
				std::cerr << "unknown component: " << args[1] << std::endl;
			}
		} else {
			std::cerr << "no machine created or assigned" << std::endl;
		}
	} else {
		std::cerr << "2 or more arguments required: set \"component name\" \"component arguments\"" << std::endl;
	}
}

void Application::set_plugboard(const std::vector<std::string>& args) {
	if (args.size() >= 3) { // set plugboard AB CD EF
		for (unsigned i = 2; i < args.size(); ++i) {
			if (args[i].size() == 2) {
				if (_machines[_index].set_plugboard(Letter(args[i][0]), Letter(args[i][1]))) {
					std::cerr << "rejected pairing: " << args[i] << std::endl;
				}
			} else {
				std::cerr << "not a pairing: " << args[i] << std::endl;
			}
		}
	} else {
		std::cerr << "3 of more arguments required: set plugboard \"l1l2\" ..." << std::endl;
	}
}

void Application::encode(const std::vector<std::string>& args) {
	if (args.size() == 2) {
		if (_index != UNDEF) {
			if (_machines[_index].size() == 3) {
				std::string res = _machines[_index].encode(args[1]);
				std::cout << "\t" << args[1] << " --> " << res << std::endl;
			} else {
				std::cerr << "3 rotors needed, current number of rotors: " << _machines[_index].size() << std::endl;
			}
		} else {
			std::cerr << "no machine created or assigned" << std::endl;
		}
	} else {
		std::cerr << "2 arguments required: encode \"text\"" << std::endl;
	}
}

void Application::reset(const std::vector<std::string>& args) {
	if (args.size() == 1) {
		if (_index != UNDEF) {
			_machines[_index].reset();
		} else {
			std::cerr << "no machine created or assigned" << std::endl;
		}
	} else {
		std::cerr << "1 arguments required: reset" << std::endl;
	}
}
