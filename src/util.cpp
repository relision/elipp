/**
 * @file
 * Utilities and common functions for the Elision project.
 *
 * @author sprowell@gmail.com
 *
 * @section LICENSE
 * This program is Copyright (C) by UT-Battelle, LLC.
 * All rights reserved.
 */

#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include "elision.h"

using std::string;
using std::ios;
using std::ostringstream;

namespace elision {

using boost::multiprecision::cpp_int;

std::string eint_to_string(eint_t value, uint16_t base) {
	std::ostringstream oss;
	eint_t useval = value;
	if (value < 0) {
		oss << "-";
		useval = -value;
	}
	switch (base) {
	case 2: {
		// We don't know the length of the bit string, so we are left to
		// do the conversion iteratively.  So just do that.  In the ideal
		// we would convert to a sequence of bytes and then write each byte
		// as binary, but this is complicated by parts of the definition being
		// undocumented.  If you find a better way to do this, or if the
		// library changes (say, we add a binary stream manipulator) then
		// please change this accordingly.
		oss << "0b"; // The binary prefix.
		std::string binary;

		// Go and get the value as hexadecimal.
		std::stringstream hex;
		hex << std::hex << useval;

		// Get the string and iterate over the digits.  Convert each digit
		// into binary.
		for (char digit : hex.str()) {
			switch (digit) {
			case '0': binary += "0000"; break;
			case '1': binary += "0001"; break;
			case '2': binary += "0010"; break;
			case '3': binary += "0011"; break;
			case '4': binary += "0100"; break;
			case '5': binary += "0101"; break;
			case '6': binary += "0110"; break;
			case '7': binary += "0111"; break;
			case '8': binary += "1000"; break;
			case '9': binary += "1001"; break;
			case 'A': binary += "1010"; break;
			case 'B': binary += "1011"; break;
			case 'C': binary += "1100"; break;
			case 'D': binary += "1101"; break;
			case 'E': binary += "1110"; break;
			case 'F': binary += "1111"; break;
			default:
				throw std::logic_error("Unexpected hex digit.");
			}
		} // Iterate over the digits.

		// Trim leading zeros.  There can be at most three.
		std::string::size_type pos = 0;
		if (binary[pos] == '0') {
			++pos;
			if (binary[pos] == '0') {
				++pos;
				if (binary[pos] == '0') {
					++pos;
				}
			}
			binary = binary.substr(pos);
		}
		oss << binary;
		break;
	}
	case 8:
		oss << "0o" << std::oct << useval;
		break;
	case 10:
		oss << std::dec << useval;
		break;
	case 16:
		oss << "0x" << std::hex << useval;
		break;
	default:
		throw std::invalid_argument("Base "+
				boost::lexical_cast<std::string>(base)+" is not allowed.");
	}
	return oss.str();
}

std::ostream&
timestamp(std::ostream& out)
{
	time_t ticks;
	time(&ticks);
	return (out << ctime(&ticks));
}

}
