#ifndef ITERMFACTORY_H_
#define ITERMFACTORY_H_

/**
 * @file
 * Define the interface to the term factory.
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

#include "ITerm.h"
#include "ILiteral.h"

namespace elision {
namespace term {

/**
 * A term factory is required to make instances of terms.  To use this get an
 * instance and then stash it somewhere.  Then invoke instance methods to
 * create terms.
 * 
 * It should be the case that terms from multiple term factories can be
 * combined interchangeably, and care should be taken to ensure this is so.
 */
class ITermFactory {
public:
	/// Deallocate this instance.
	virtual ~ITermFactory() = default;

	//======================================================================
	// Access to root types.
	//======================================================================

	virtual EPTR(ITerm) get_root() const = 0;
	virtual EPTR(ISymbolLiteral) get_root_term(std::string const name) const = 0;

	//======================================================================
	// Well-known root types (and ^ROOT, itself).  Subclasses must initialize
	// these!
	//======================================================================

	EPTR(ITerm) ROOT;
	EPTR(ISymbolLiteral) SYMBOL;
	EPTR(ISymbolLiteral) STRING;
	EPTR(ISymbolLiteral) INTEGER;
	EPTR(ISymbolLiteral) FLOAT;
	EPTR(ISymbolLiteral) BOOLEAN;
	EPTR(ISymbolLiteral) BITSTRING;
	EPTR(ISymbolLiteral) PMAP;

	//======================================================================
	// Make literals.
	//======================================================================

	virtual EPTR(ISymbolLiteral) get_symbol_literal(
			EPTR(Loc) loc, std::string const& name, EPTR(ITerm) type) const = 0;
	virtual EPTR(IStringLiteral) get_string_literal(
			EPTR(Loc) loc, std::string const& value, EPTR(ITerm) type) const = 0;
	virtual EPTR(IIntegerLiteral) get_integer_literal(
			EPTR(Loc) loc, eint_t value, EPTR(ITerm) type) const = 0;
	virtual EPTR(IFloatLiteral) get_float_literal(
			EPTR(Loc) loc, eint_t significand, eint_t exponent, uint16_t radix,
			EPTR(ITerm) type) const = 0;
	virtual EPTR(IBitStringLiteral) get_bit_string_literal(
			EPTR(Loc) loc, eint_t bits, eint_t length, EPTR(ITerm) type) const = 0;
	virtual EPTR(IBooleanLiteral) get_boolean_literal(
			EPTR(Loc) loc, bool value, EPTR(ITerm) type) const = 0;

	//======================================================================
	// Make literals with the default type.
	//======================================================================

	EPTR(ISymbolLiteral) get_symbol_literal(EPTR(Loc) loc,
			std::string const& name) const {
		return get_symbol_literal(loc, name, SYMBOL);
	}
	EPTR(IStringLiteral) get_string_literal(EPTR(Loc) loc,
			std::string const& value) const {
		return get_string_literal(loc, value, STRING);
	}
	EPTR(IIntegerLiteral) get_integer_literal(EPTR(Loc) loc,
			eint_t value) const {
		return get_integer_literal(loc, value, INTEGER);
	}
	EPTR(IFloatLiteral) get_float_literal(EPTR(Loc) loc, eint_t significand,
			eint_t exponent, uint16_t radix) const {
		return get_float_literal(loc, significand, exponent, radix, FLOAT);
	}
	EPTR(IBitStringLiteral) get_bit_string_literal(EPTR(Loc) loc, eint_t bits,
			eint_t length) const {
		return get_bit_string_literal(loc, bits, length, BITSTRING);
	}
	EPTR(IBooleanLiteral) get_boolean_literal(EPTR(Loc) loc, bool value) const {
		return get_boolean_literal(loc, value, BOOLEAN);
	}

	//======================================================================
	// Make literals with default type and internal location.
	//======================================================================

	EPTR(ISymbolLiteral) get_symbol_literal(std::string const& name) const {
		return get_symbol_literal(Loc::get_internal(), name);
	}
	EPTR(IStringLiteral) get_string_literal(std::string const& value) const {
		return get_string_literal(Loc::get_internal(), value);
	}
	EPTR(IIntegerLiteral) get_integer_literal(eint_t value) const {
		return get_integer_literal(Loc::get_internal(), value);
	}
	EPTR(IFloatLiteral) get_float_literal(eint_t significand, eint_t exponent,
			uint16_t radix) const {
		return get_float_literal(Loc::get_internal(), significand, exponent,
				radix);
	}
	EPTR(IBitStringLiteral) get_bit_string_literal(eint_t bits,
			eint_t length) const {
		return get_bit_string_literal(Loc::get_internal(), bits, length);
	}
	EPTR(IBooleanLiteral) get_boolean_literal(bool value) const {
		return get_boolean_literal(Loc::get_internal(), value);
	}
};

} /* namespace term */
} /* namespace elision */

#endif /* ITERMFACTORY_H_ */
