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

#include "LiteralImpl.h"
#include <boost/lexical_cast.hpp>

namespace elision {
namespace term {
namespace basic {

//======================================================================
// Symbol literal.
//======================================================================

SymbolLiteralImpl::SymbolLiteralImpl(Locus the_loc, std::string the_name,
		pTerm the_type) : TermImpl(the_loc, the_type), name_(the_name) {
}

std::string
SymbolLiteralImpl::to_string() const {
	return elision::escape(name_, true) + WITH_TYPE(type_);
}

//======================================================================
// String literal.
//======================================================================

StringLiteralImpl::StringLiteralImpl(Locus the_loc, std::string the_value,
		pTerm the_type) : TermImpl(the_loc, the_type), value_(the_value) {
}

std::string
StringLiteralImpl::to_string() const {
	return elision::escape(value_, false) + WITH_TYPE(type_);
}

//======================================================================
// Integer literal.
//======================================================================

IntegerLiteralImpl::IntegerLiteralImpl(Locus the_loc, eint_t the_value,
		pTerm the_type) : TermImpl(the_loc, the_type), value_(the_value) {
}

std::string
IntegerLiteralImpl::to_string() const {
	return elision::eint_to_string(value_,
			elision::preferred_radix, true) + WITH_TYPE(type_);
}

//======================================================================
// Float literal.
//======================================================================

FloatLiteralImpl::FloatLiteralImpl(Locus the_loc, eint_t the_significand,
		eint_t the_exponent, uint8_t the_radix, pTerm the_type) :
				TermImpl(the_loc, the_type), significand_(the_significand),
				exponent_(the_exponent), radix_(the_radix) {
	if (the_radix != 2 &&
			the_radix != 8 &&
			the_radix != 10 &&
			the_radix != 16) {
		throw new std::invalid_argument(
				"The radix is not an allowed value: " +
				boost::lexical_cast<std::string>(the_radix));
	}
}

std::string
FloatLiteralImpl::to_string() const {
	return elision::eint_to_string(significand_, radix_, true) +
			(radix_ == 16 ? "p" : "e") +
			elision::eint_to_string(exponent_, radix_, true) +
			WITH_TYPE(type_);
}

//======================================================================
// Bit string literal.
//======================================================================

BitStringLiteralImpl::BitStringLiteralImpl(Locus the_loc, eint_t the_bits,
		eint_t the_length, pTerm the_type) : TermImpl(the_loc, the_type),
				bits_(the_bits), length_(the_length) {
}

std::string
BitStringLiteralImpl::to_string() const {
	return elision::eint_to_string(bits_, 16, true) + "L" +
			elision::eint_to_string(length_, 10, true) +
			WITH_TYPE(type_);
}

//======================================================================
// Boolean literal.
//======================================================================

BooleanLiteralImpl::BooleanLiteralImpl(Locus the_loc, bool the_value,
		pTerm the_type) : TermImpl(the_loc, the_type), value_(the_value) {
}

std::string
BooleanLiteralImpl::to_string() const {
	return std::string(value_ ? "true" : "false") + WITH_TYPE(type_);
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
