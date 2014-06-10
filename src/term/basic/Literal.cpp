/**
 * @file
 * TODO: Describe purpose of file.
 *
 * @author sprowell@gmail.com
 *
 * @section LICENSE
 * @verbatim
 *       _ _     _
 *   ___| (_)___(_) ___  _ __
 *  / _ \ | / __| |/ _ \| '_ \
 * |  __/ | \__ \ | (_) | | | |
 *  \___|_|_|___/_|\___/|_| |_|
 * The Elision Term Rewriter
 *
 * Copyright (c) 2014 by Stacy Prowell (sprowell@gmail.com)
 * All rights reserved.
 * @endverbatim
 */

#include "Literal.h"
#include <boost/lexical_cast.hpp>

namespace elision {
namespace term {
namespace basic {

//======================================================================
// Symbol literal.
//======================================================================

SymbolLiteral::SymbolLiteral(EPTR(Loc) the_loc, std::string the_name,
		EPTR(ITerm) the_type) : Term(the_loc, the_type), name_(the_name) {
}

SymbolLiteral::operator std::string() const {
	return elision::escape(name_, true);
}

//======================================================================
// String literal.
//======================================================================

StringLiteral::StringLiteral(EPTR(Loc) the_loc, std::string the_value,
		EPTR(ITerm) the_type) : Term(the_loc, the_type), value_(the_value) {
}

StringLiteral::operator std::string() const {
	return elision::escape(value_, false);
}

//======================================================================
// Integer literal.
//======================================================================

IntegerLiteral::IntegerLiteral(EPTR(Loc) the_loc, eint_t the_value,
		EPTR(ITerm) the_type) : Term(the_loc, the_type), value_(the_value) {
	NOTNULL(the_value);
}

IntegerLiteral::operator std::string() const {
	return elision::eint_to_string(value_,
			elision::preferred_radix, true);
}

//======================================================================
// Float literal.
//======================================================================

FloatLiteral::FloatLiteral(EPTR(Loc) the_loc, eint_t the_significand,
		eint_t the_exponent, uint8_t the_radix, EPTR(ITerm) the_type) :
				Term(the_loc, the_type), significand_(the_significand),
				exponent_(the_exponent), radix_(the_radix) {
	NOTNULL(the_significand);
	NOTNULL(the_exponent);
	if (the_radix != 2 &&
			the_radix != 8 &&
			the_radix != 10 &&
			the_radix != 16) {
		throw new std::invalid_argument(
				"The radix is not an allowed value: " +
				boost::lexical_cast<std::string>(the_radix));
	}
}

FloatLiteral::operator std::string() const {
	return elision::eint_to_string(significand_, radix_, true) +
			(radix_ == 16 ? "p" : "e") +
			elision::eint_to_string(exponent_, radix_, true);
}

//======================================================================
// Bit string literal.
//======================================================================

BitStringLiteral::BitStringLiteral(EPTR(Loc) the_loc, eint_t the_bits,
		eint_t the_length, EPTR(ITerm) the_type) : Term(the_loc, the_type),
				bits_(the_bits), length_(the_length) {
	NOTNULL(the_bits);
	NOTNULL(the_length);
}

BitStringLiteral::operator std::string() const {
	return elision::eint_to_string(bits_, 16, true) + "L" +
			elision::eint_to_string(length_, 10, true);
}

//======================================================================
// Boolean literal.
//======================================================================

BooleanLiteral::BooleanLiteral(EPTR(Loc) the_loc, bool the_value,
		EPTR(ITerm) the_type) : Term(the_loc, the_type), value_(the_value) {
	// Nothing to do.
}

BooleanLiteral::operator std::string() const {
	return value_ ? "true" : "false";
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
