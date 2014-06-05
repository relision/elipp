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

#include "BasicLiteral.h"
#include "boost/lexical_cast.hpp"

using elision::eint_t;

namespace elision {
namespace term {
namespace basic {

BasicSymbolLiteral::BasicSymbolLiteral(Loc const& loc, std::string const& name,
		Term const& type) : BasicTerm(loc, type), name_(name) {}

BasicSymbolLiteral::operator
std::string() const {
	// We need to determine if the name should be quoted or not.
	static auto ret = escape(name_, true);
	return ret;
}

BasicStringLiteral::BasicStringLiteral(Loc const& loc, std::string const& value,
		Term const& type) : BasicTerm(loc, type), value_(value) {}

BasicStringLiteral::operator
std::string() const {
	// Escape special characters and quote the string.
	static auto ret = escape(value_, false);
	return ret;
}

BasicIntegerLiteral::BasicIntegerLiteral(Loc const& loc, eint_t const& value,
		Term const& type) : BasicTerm(loc, type), value_(value) {}

BasicIntegerLiteral::operator
std::string() const {
	static std::string ret = boost::lexical_cast<std::string>(value_);
	return ret;
}

BasicFloatLiteral::BasicFloatLiteral(Loc const& loc, eint_t const& significand,
		eint_t const& exponent, uint16_t radix, Term const& type) :
				BasicTerm(loc, type), significand_(significand),
				exponent_(exponent), radix_(radix) {}

BasicFloatLiteral::operator
std::string() const {
	// Convert the parts into a nifty whole.  To do this we have to express
	// both the significand and the exponent in the correct radix.
	return "unimplemented";
}

BasicBitStringLiteral::BasicBitStringLiteral(Loc const& loc, eint_t const& bits,
		uint16_t length, Term const& type) : BasicTerm(loc, type), bits_(bits),
				length_(length) {}

BasicBitStringLiteral::operator
std::string() const {
	// Convert the bit string into a nice string.
	return "unimplemented";
}

BasicBooleanLiteral::BasicBooleanLiteral(Loc const& loc, bool value,
		Term const& type) : BasicTerm(loc, type), value_(value) {}

BasicBooleanLiteral::operator
std::string() const {
	return value_ ? "true" : "false";
}

BasicTermLiteral::BasicTermLiteral(Loc const& loc, Term const& value,
		Term const& type) : BasicTerm(loc, type), term_(value) {}

BasicTermLiteral::operator
std::string() const {
	return "unimplemented";
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
