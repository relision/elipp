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

#include "TermFactory.h"
#include "Literal.h"

namespace elision {
namespace term {
namespace basic {

// Little macro to initialize the root types.
#define INIT(m_name) m_name = get_root_term(" ## m_name ## ");

TermFactory::TermFactory() : root_(new RootTerm()){
	INIT(SYMBOL);
	INIT(STRING);
	INIT(INTEGER);
	INIT(FLOAT);
	INIT(BITSTRING);
	INIT(BOOLEAN);
}

EPTR(ISymbolLiteral)
TermFactory::get_root_term(std::string const name) const {
	// Go and get a pointer from the map.
	EPTR(ISymbolLiteral) rt = known_roots_[name];
	if (!rt) {
		// First time through.  Make a new symbol and store it.
		EPTR(ISymbolLiteral) nrt =
				get_symbol_literal(Loc::get_internal(), name, root_);
		known_roots_[name] = nrt;
		return nrt;
	}
	return rt;
}

// Shorthand to make a shared pointer of the correct type with the provided
// arguments.  Depends on names being the "usual" names.
#define MAKE(m_kind, ...) \
	std::shared_ptr<I ## m_kind const>(new m_kind(loc, __VA_ARGS__, type))

EPTR(ISymbolLiteral)
TermFactory::get_symbol_literal(
		EPTR(Loc) loc, std::string const& name, EPTR(ITerm) type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(SymbolLiteral, name);
}

EPTR(IStringLiteral)
TermFactory::get_string_literal(
		EPTR(Loc) loc, std::string const& value, EPTR(ITerm) type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(StringLiteral, value);
}

EPTR(IIntegerLiteral)
TermFactory::get_integer_literal(
		EPTR(Loc) loc, eint_t value, EPTR(ITerm) type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(IntegerLiteral, value);
}

EPTR(IFloatLiteral)
TermFactory::get_float_literal(
		EPTR(Loc) loc, eint_t significand, eint_t exponent, uint16_t radix,
		EPTR(ITerm) type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(FloatLiteral, significand, exponent, radix);
}

EPTR(IBitStringLiteral)
TermFactory::get_bit_string_literal(
		EPTR(Loc) loc, eint_t bits, eint_t length, EPTR(ITerm) type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(BitStringLiteral, bits, length);
}

EPTR(IBooleanLiteral)
TermFactory::get_boolean_literal(
		EPTR(Loc) loc, bool value, EPTR(ITerm) type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(BooleanLiteral, value);
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
