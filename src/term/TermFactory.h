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
class TermFactory {
public:
	/// Deallocate this instance.
	virtual ~TermFactory() {};

	//======================================================================
	// Access to root types.
	//======================================================================

	/**
	 * Get the unique root.
	 * @return	The unique root type.
	 */
	virtual Term get_root() const = 0;

	/**
	 * Get a root term specified by name.  This keeps a registry of known
	 * root terms.  Requesting one via this method creates it and adds it
	 * to the registry.
	 * @param	name	The name of the root term.
	 * @return	The requested root term.
	 */
	virtual SymbolLiteral get_root_term(std::string const name) const = 0;

	//======================================================================
	// Well-known root types (and ^ROOT, itself).  Subclasses must initialize
	// these!
	//======================================================================

	Term ROOT;					//< Simple access to the root.
	SymbolLiteral SYMBOL;		//< Simple access to the symbol type.
	SymbolLiteral STRING;		//< Simple access to the string type.
	SymbolLiteral INTEGER;		//< Simple access to the integer type.
	SymbolLiteral FLOAT;		//< Simple access to the float type.
	SymbolLiteral BITSTRING;	//< Simple access to the bit string type.
	SymbolLiteral BOOLEAN;		//< Simple access to the Boolean type.

	//======================================================================
	// Make literals.
	//======================================================================

	virtual SymbolLiteral get_symbol_literal(
			Locus loc, std::string const& name, Term type) const = 0;
	virtual StringLiteral get_string_literal(
			Locus loc, std::string const& value, Term type) const = 0;
	virtual IntegerLiteral get_integer_literal(
			Locus loc, eint_t value, Term type) const = 0;
	virtual FloatLiteral get_float_literal(
			Locus loc, eint_t significand, eint_t exponent, uint16_t radix,
			Term type) const = 0;
	virtual BitStringLiteral get_bit_string_literal(
			Locus loc, eint_t bits, eint_t length, Term type) const = 0;
	virtual BooleanLiteral get_boolean_literal(
			Locus loc, bool value, Term type) const = 0;

	//======================================================================
	// Make literals with the default type.
	//======================================================================

	SymbolLiteral get_symbol_literal(Locus loc,
			std::string const& name) const {
		return get_symbol_literal(loc, name, SYMBOL);
	}
	StringLiteral get_string_literal(Locus loc,
			std::string const& value) const {
		return get_string_literal(loc, value, STRING);
	}
	IntegerLiteral get_integer_literal(Locus loc,
			eint_t value) const {
		return get_integer_literal(loc, value, INTEGER);
	}
	FloatLiteral get_float_literal(Locus loc, eint_t significand,
			eint_t exponent, uint16_t radix) const {
		return get_float_literal(loc, significand, exponent, radix, FLOAT);
	}
	BitStringLiteral get_bit_string_literal(Locus loc, eint_t bits,
			eint_t length) const {
		return get_bit_string_literal(loc, bits, length, BITSTRING);
	}
	BooleanLiteral get_boolean_literal(Locus loc, bool value) const {
		return get_boolean_literal(loc, value, BOOLEAN);
	}

	//======================================================================
	// Make literals with default type and internal location.
	//======================================================================

	SymbolLiteral get_symbol_literal(std::string const& name) const {
		return get_symbol_literal(Loc::get_internal(), name);
	}
	StringLiteral get_string_literal(std::string const& value) const {
		return get_string_literal(Loc::get_internal(), value);
	}
	IntegerLiteral get_integer_literal(eint_t value) const {
		return get_integer_literal(Loc::get_internal(), value);
	}
	FloatLiteral get_float_literal(eint_t significand, eint_t exponent,
			uint16_t radix) const {
		return get_float_literal(Loc::get_internal(), significand, exponent,
				radix);
	}
	BitStringLiteral get_bit_string_literal(eint_t bits,
			eint_t length) const {
		return get_bit_string_literal(Loc::get_internal(), bits, length);
	}
	BooleanLiteral get_boolean_literal(bool value) const {
		return get_boolean_literal(Loc::get_internal(), value);
	}
};

} /* namespace term */
} /* namespace elision */

#endif /* ITERMFACTORY_H_ */
