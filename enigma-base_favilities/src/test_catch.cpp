// #include <string>
// #include "catch.hpp"
//
// #include "machine/letter.hpp"
// #include "machine/components/rotor.hpp"
// #include "machine/components/reflector.hpp"
// #include "machine/components/plugboard.hpp"
// #include "machine/enigma.hpp"
//
// /* Behavior Driven Development
//  *
//  * > Scenario/Story
//  * # Given
//  * # When
//  * # Then
//  *
//  * cf cucumber
//  */
//
// //                       ABCDEFGHIJKLMNOPQRSTUVWXYZ
// std::string s_ref_B   = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
// std::string s_rot_I   = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
// std::string s_rot_II  = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
// std::string s_rot_III = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
//
// /*
// 			yruhqsldpxngokmiebfzcwvjat
//
// 			abcdefghijklmnopqrstuvwxyz
// 		  uwygadfpvzbeckmthxslrinqoj
// 		- ekmflgdqvzntowyhxuspaibrcj
// 			abcdefghijklmnopqrstuvwxyz
//
// 			abcdefghijklmnopqrstuvwxyz
// 		  ajpczwrlfbdkotyuqgenhxmivs
// 		- ajdksiruxblhwtmcqgznpyfvoe
// 			abcdefghijklmnopqrstuvwxyz
//
// 			abcdefghijklmnopqrstuvwxyz
// 			tagbpcsdqeufvnzhyixjwlrkom
// 		- bdfhjlcprtxvznyeiwgakmusqo
// 			abcdefghijklmnopqrstuvwxyz
// */
//
// TEST_CASE("Letter") {
// 	Rotor r1 = Rotor::I();
//
// 	r1.display();
//
// 	SECTION("construct") {
// 		REQUIRE( Letter('B') == 'B' );
// 		REQUIRE( Letter('C') == 2 );
// 		REQUIRE( Letter('D') == 3 );
// 	}
//
// 	SECTION("setter") {
// 		Letter c;
//
// 		c.character('E');
// 		REQUIRE( c == 'E' );
//
// 		c.value(5);
// 		REQUIRE( c == 'F' );
//
// 		c = 'G';
// 		REQUIRE( c == 'G' );
//
// 		c = 7;
// 		REQUIRE( c == 'H' );
// 	}
//
// 	SECTION("operators") {
// 		Letter c = 'I';
//
// 		REQUIRE( ++c == 'J' );
// 		REQUIRE( --c == 'I' );
// 		REQUIRE( c+2 == 'K' );
// 		REQUIRE( c-2 == 'G' );
//
// 		c += 2;
// 		REQUIRE( c == 'K' );
//
// 		c -= 2;
// 		REQUIRE( c == 'I' );
// 	}
//
// 	SECTION("fit") {
// 		Letter c = 'Z';
// 		REQUIRE( c+1 == 'A' );
// 		REQUIRE( ++c == 'A' );
// 		REQUIRE( c-1 == 'Z' );
// 		REQUIRE( --c == 'Z' );
// 	}
//
// 	SECTION("to_sequence") {
// 		std::vector<Letter> seq = to_sequence("ABCDEFG");
//
// 		for (unsigned i = 0; i < seq.size(); ++i) {
// 			REQUIRE( seq[i].character() == 'A'+i );
// 		}
// 		std::cout << std::endl;
// 	}
// }
//
// TEST_CASE("Rotor") {
// 	Rotor rot_I = Rotor::I();
// 	Rotor rot_II = Rotor::II();
// 	Rotor rot_III = Rotor::III();
//
// 	SECTION("encode") {
// 		REQUIRE( rot_I.encode('A') == 'E' );
// 		REQUIRE( rot_I.encode('D') == 'F' );
// 		REQUIRE( rot_I.encode('Y') == 'C' );
// 	}
//
// 	SECTION("decode") {
// 		REQUIRE( rot_I.decode('Q') == 'H' );
// 		REQUIRE( rot_I.decode('S') == 'S' );
// 		REQUIRE( rot_I.decode('W') == 'N' );
// 		REQUIRE( rot_I.decode('H') == 'P' );
// 	}
//
// 	SECTION("encode/decode all") {
// 		for (unsigned i = 0; i < 26; ++i) {
// 			Letter c_in  = i;
// 			Letter c_out = rot_I.encode(c_in);
// 			REQUIRE( c_in == rot_I.decode(c_out) );
// 		}
// 	}
//
// 	SECTION("rotate: single letter") {
// 		for (unsigned i = 0; i < 28; ++i) {
// 			Letter c_in  = 'A';
// 			Letter c_out = rot_I.encode(c_in);
// 			REQUIRE( c_in == rot_I.decode(c_out) );
// 			rot_I.rotate();
// 		}
// 	}
//
// 	SECTION("rotate: all letters") {
// 		for (unsigned i = 0; i < 26; ++i) {
// 			Letter c_in  = 'A';
// 			Letter c_out = rot_I.encode(c_in);
// 			REQUIRE( c_in == rot_I.decode(c_out) );
// 			rot_I.rotate();
// 		}
// 	}
//
// 	SECTION("ring settings") {
// 		Rotor dumb_0 = Rotor::DUMMY(0);
// 		Rotor dumb_4 = Rotor::DUMMY(4);
// 		Rotor dumb_AC_FVL_0 = Rotor("CBADEVGHIJKFMNOPQRSTULWXYZ", 25, 0);
// 		Rotor dumb_AC_FVL_4 = Rotor("CBADEVGHIJKFMNOPQRSTULWXYZ", 25, 4);
//
// 		REQUIRE( dumb_0.encode('A') == 'A' );
// 		REQUIRE( dumb_0.decode('A') == 'A' );
// 		REQUIRE( dumb_0.encode('C') == 'C' );
// 		REQUIRE( dumb_0.decode('C') == 'C' );
// 		REQUIRE( dumb_0.encode('V') == 'V' );
// 		REQUIRE( dumb_0.decode('V') == 'V' );
//
// 		REQUIRE( dumb_4.encode('A') == 'A' );
// 		REQUIRE( dumb_4.decode('A') == 'A' );
// 		REQUIRE( dumb_4.encode('C') == 'C' );
// 		REQUIRE( dumb_4.decode('C') == 'C' );
// 		REQUIRE( dumb_4.encode('V') == 'V' );
// 		REQUIRE( dumb_4.decode('V') == 'V' );
//
// 		REQUIRE( dumb_AC_FVL_0.encode('A') == 'C' );
// 		REQUIRE( dumb_AC_FVL_0.decode('C') == 'A' );
// 		REQUIRE( dumb_AC_FVL_0.encode('C') == 'A' );
// 		REQUIRE( dumb_AC_FVL_0.decode('A') == 'C' );
// 		REQUIRE( dumb_AC_FVL_0.encode('F') == 'V' );
// 		REQUIRE( dumb_AC_FVL_0.decode('V') == 'F' );
// 		REQUIRE( dumb_AC_FVL_0.encode('V') == 'L' );
// 		REQUIRE( dumb_AC_FVL_0.decode('L') == 'V' );
// 		REQUIRE( dumb_AC_FVL_0.encode('L') == 'F' );
// 		REQUIRE( dumb_AC_FVL_0.decode('F') == 'L' );
//
// 		REQUIRE( dumb_AC_FVL_4.encode('G') == 'E' );
// 		REQUIRE( dumb_AC_FVL_4.decode('E') == 'G' );
// 		REQUIRE( dumb_AC_FVL_4.encode('E') == 'G' );
// 		REQUIRE( dumb_AC_FVL_4.decode('G') == 'E' );
// 		REQUIRE( dumb_AC_FVL_4.encode('F') == 'F' );
// 		REQUIRE( dumb_AC_FVL_4.decode('F') == 'F' );
// 		REQUIRE( dumb_AC_FVL_4.encode('V') == 'V' );
// 		REQUIRE( dumb_AC_FVL_4.decode('V') == 'V' );
// 		REQUIRE( dumb_AC_FVL_4.encode('L') == 'L' );
// 		REQUIRE( dumb_AC_FVL_4.decode('L') == 'L' );
// 	}
//
// 	SECTION("ground") {
// 		Rotor dumb_A = Rotor::DUMMY(0, 'A');
// 		Rotor dumb_E = Rotor::DUMMY(0, 'E');
// 		Rotor dumb_AC_FVL_A = Rotor("CBADEVGHIJKFMNOPQRSTULWXYZ", 25, 0, 'A');
// 		Rotor dumb_AC_FVL_E = Rotor("CBADEVGHIJKFMNOPQRSTULWXYZ", 25, 0, 'E');
//
// 		REQUIRE( dumb_A.encode('A') == 'A' );
// 		REQUIRE( dumb_A.encode('C') == 'C' );
// 		REQUIRE( dumb_A.encode('V') == 'V' );
//
// 		REQUIRE( dumb_E.encode('A') == 'A' );
// 		REQUIRE( dumb_E.encode('C') == 'C' );
// 		REQUIRE( dumb_E.encode('V') == 'V' );
//
// 		REQUIRE( dumb_AC_FVL_A.encode('A') == 'C' );
// 		REQUIRE( dumb_AC_FVL_A.encode('B') == 'B' );
// 		REQUIRE( dumb_AC_FVL_A.encode('C') == 'A' );
// 		REQUIRE( dumb_AC_FVL_A.encode('F') == 'V' );
//
// 		REQUIRE( dumb_AC_FVL_E.encode('A') == 'A' );
// 		REQUIRE( dumb_AC_FVL_E.encode('B') == 'R' );
// 		REQUIRE( dumb_AC_FVL_E.encode('C') == 'C' );
// 		REQUIRE( dumb_AC_FVL_E.encode('D') == 'D' );
// 		REQUIRE( dumb_AC_FVL_E.encode('E') == 'E' );
// 		REQUIRE( dumb_AC_FVL_E.encode('F') == 'F' );
// 		REQUIRE( dumb_AC_FVL_E.encode('G') == 'G' );
// 		REQUIRE( dumb_AC_FVL_E.encode('H') == 'B' );
// 	}
// }
//
// TEST_CASE("Scrambler") {
// 	SECTION("zone 1") {
// 		Scrambler sc;
//
// 		sc.add_rotor(Rotor::I());
// 		sc.add_rotor(Rotor::II());
// 		sc.add_rotor(Rotor::III());
//
// 		REQUIRE( sc.encode('A') == 'Z' );
// 		REQUIRE( sc.encode('B') == 'N' );
// 		REQUIRE( sc.encode('C') == 'V' );
//
// 		REQUIRE( sc.decode('Z') == 'A' );
// 		REQUIRE( sc.decode('N') == 'B' );
// 		REQUIRE( sc.decode('V') == 'C' );
// 	}
//
// 	SECTION("zone 2") {
// 		Scrambler sc;
//
// 	// ACBDEFGHIJKLMNOPQRSTUVWXYZ
// 	// abcdefghijklmnopqrstuvwxyz
// 	// ABDCEFGHIJKLMNOPQRSTUVWXYZ
//
// 		sc.add_rotor(Rotor("ACBDEFGHIJKLMNOPQRSTUVWXYZ", 6));
// 		sc.add_rotor(Rotor("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 4));
//
// 		REQUIRE( sc.encode('A') == 'A' );
// 		REQUIRE( sc.encode('B') == 'C' );
// 		REQUIRE( sc.encode('C') == 'B' );
//
// 		sc.rotate();
// 		sc.rotate();
// 		sc.rotate();
// 		REQUIRE( sc.encode('A') == 'A' );
// 		REQUIRE( sc.encode('B') == 'C' );
// 		REQUIRE( sc.encode('C') == 'B' );
//
// 		sc.rotate();
// 		sc.rotate();
// 		REQUIRE( sc.encode('A') == 'B' );
// 		REQUIRE( sc.encode('B') == 'A' );
// 		REQUIRE( sc.encode('C') == 'C' );
//
// 	}
// }
//
// TEST_CASE("Reflector") {
// 	std::string str1 = "ABCWEFGHRJKOMNLPQISTUVDXYZ";
// 	Reflector r1(str1);
//
// 	SECTION("encode") {
// 		REQUIRE( 'A' == r1.encode('A') );
// 		REQUIRE( 'W' == r1.encode('D') );
//
// 		REQUIRE( 'I' == r1.encode('R') );
// 		REQUIRE( 'R' == r1.encode('I') );
// 	}
//
// 	SECTION("exemple") {
// 		Reflector ref_B(s_ref_B);
// 		REQUIRE( ref_B.encode('H') == 'D' );
// 		REQUIRE( ref_B.encode('D') == 'H' );
// 	}
// }
//
// TEST_CASE("Plugboard") {
// 	std::string str1 =  "YRUHQSLDPXNGOKMIEBFZCWVJAT";
// 	Plugboard r1(str1);//ABCDEFGHIJKLMNOPQRSTUVWXYZ
//
// 	SECTION("encode") {
// 		REQUIRE( 'Y' == r1.encode('A') );
// 		REQUIRE( 'H' == r1.encode('D') );
// 	}
// }
//
// TEST_CASE("Machine") {
//
// 	SECTION("base") {
// 		Enigma machine;
//
// 		machine.add_rotor(Rotor::I());
// 		machine.add_rotor(Rotor::II());
// 		machine.add_rotor(Rotor::III());
// 		machine.set_reflector(Reflector::B());
//
// 		REQUIRE( machine.encode("AAAAAAAAAAA") == "BDZGOWCXLTK" );
// 		REQUIRE( machine.encode("AAAAAAAAAAA") != "BDZGOWCXLTK" );
// 		machine.reset();
// 		REQUIRE( machine.encode("AAAAAAAAAAA") == "BDZGOWCXLTK" );
// 		machine.reset();
// 		REQUIRE( machine.decode("BDZGOWCXLTK") == "AAAAAAAAAAA" );
// 	}
//
// 	SECTION("ring settings 1") {
// 		Enigma machine;
// 		machine.add_rotor(Rotor::I(1));
// 		machine.add_rotor(Rotor::II(2));
// 		machine.add_rotor(Rotor::III(3));
// 		machine.set_reflector(Reflector::B());
//
// 		REQUIRE( machine.encode("AAAAAAAAAAA") == "HYUWQPXWHZG" );
// 		machine.reset();
// 		REQUIRE( machine.decode("HYUWQPXWHZG") == "AAAAAAAAAAA" );
// 	}
//
// 	SECTION("ring settings 2") {
// 		Enigma machine;
// 		machine.add_rotor(Rotor::I(12));
// 		machine.add_rotor(Rotor::II(23));
// 		machine.add_rotor(Rotor::III(3));
// 		machine.set_reflector(Reflector::B());
//
// 		REQUIRE( machine.encode("AAAAAAAAAAA") == "XMGFOQDLFHI" );
// 	}
//
// 	SECTION("grounds 1") {
// 		Enigma machine;
// 		machine.add_rotor(Rotor::I(0, 'R'));
// 		machine.add_rotor(Rotor::II(0, 'D'));
// 		machine.add_rotor(Rotor::III(0, 'F'));
// 		machine.set_reflector(Reflector::B());
//
// 		REQUIRE( machine.encode("AAAAAAAAAAA") == "TUTDXPWZBCZ" );
// 	}
//
// 	SECTION("grounds 2") {
// 		Enigma machine;
// 		machine.add_rotor(Rotor::I(0, 'B'));
// 		machine.add_rotor(Rotor::II(0, 'A'));
// 		machine.add_rotor(Rotor::III(0, 'G'));
// 		machine.set_reflector(Reflector::B());
//
// 		REQUIRE( machine.encode("AAAAAAAAAAA") == "GKWJCUFKLUI" );
// 	}
//
// 	SECTION("grounds 2") {
// 		Enigma machine;
// 		machine.add_rotor(Rotor::I(0, 'B'));
// 		machine.add_rotor(Rotor::II(0, 'R'));
// 		machine.add_rotor(Rotor::III(0, 'G'));
// 		machine.set_reflector(Reflector::B());
//
// 		REQUIRE( machine.encode("AAAAAAAAAAA") == "KPOXLWBWVBY" );
// 	}
//
// 	SECTION("grounds RAT") {
// 		Enigma machine;
// 		machine.add_rotor(Rotor::I(0, 'R'));
// 		machine.add_rotor(Rotor::II(0, 'A'));
// 		machine.add_rotor(Rotor::III(0, 'T'));
// 		machine.set_reflector(Reflector::B());
//
// 		REQUIRE( machine.encode("AAAAAAAAAAA") == "QZHIPJUHHDJ" );
// 	}
//
// 	SECTION("grounds RBT") {
// 		Enigma machine;
// 		machine.add_rotor(Rotor::I(0, 'R'));
// 		machine.add_rotor(Rotor::II(0, 'B'));
// 		machine.add_rotor(Rotor::III(0, 'T'));
// 		machine.set_reflector(Reflector::B());
//
// 		REQUIRE( machine.encode("AAAAAAAAAAA") == "XTHCSNJMKJT" );
// 	}
//
// 	SECTION("grounds RCT") {
// 		Enigma machine;
// 		machine.add_rotor(Rotor::I(0, 'R'));
// 		machine.add_rotor(Rotor::II(0, 'C'));
// 		machine.add_rotor(Rotor::III(0, 'T'));
// 		machine.set_reflector(Reflector::B());
//
// 		REQUIRE( machine.encode("AAAAAAAAAAA") == "JDLVXTIUPBE" );
// 	}
//
// 	SECTION("grounds RDT") {
// 		Enigma machine;
// 		machine.add_rotor(Rotor::I(0, 'R'));
// 		machine.add_rotor(Rotor::II(0, 'D'));
// 		machine.add_rotor(Rotor::III(0, 'T'));
// 		machine.set_reflector(Reflector::B());
//
// 		REQUIRE( machine.encode("AAAAAAAAAAA") == "VWKNEKOWFCD" );
// 	}
//
// 	SECTION("grounds RET") {
// 		Enigma machine;
// 		machine.add_rotor(Rotor::I(0, 'R'));
// 		machine.add_rotor(Rotor::II(0, 'E'));
// 		machine.add_rotor(Rotor::III(0, 'T'));
// 		machine.set_reflector(Reflector::B());
//
// 		REQUIRE( machine.encode("AAAAAAAAAAA") == "HPXWEKECIXW" );
// 	}
//
// 	SECTION("grounds RFT") {
// 		Enigma machine;
// 		machine.add_rotor(Rotor::I(0, 'R'));
// 		machine.add_rotor(Rotor::II(0, 'F'));
// 		machine.add_rotor(Rotor::III(0, 'T'));
// 		machine.set_reflector(Reflector::B());
//
// 		REQUIRE( machine.encode("AAAAAAAAAAA") == "IHRWFUHVIFW" );
// 	}
//
//
// 	SECTION("RS + ground") {
// 		Enigma machine;
// 		machine.add_rotor(Rotor::I(1, 'B'));
// 		machine.add_rotor(Rotor::II(2, 'A'));
// 		machine.add_rotor(Rotor::III(3, 'G'));
// 		machine.set_reflector(Reflector::B());
//
// 		REQUIRE( machine.encode("AAAAAAAAAAA") == "OGQKVVDUVXL" );
// 	}
// }
