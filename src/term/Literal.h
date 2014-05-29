#ifndef LITERAL_H_
#define LITERAL_H_

/**
 * @file
 * Define the basic literals.
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

#include "Term.h"
#include <stdint.h>


namespace elision {
namespace term {

/**
 * The common base class for all literals.
 */
class Literal : public Term {
	// Nothing to see.
};


/// A symbol literal.
class SymbolLiteral : public Literal {
public:
	/**
	 * Get the name of this symbol.
	 * @return	The name of this symbol.
	 */
	virtual std::string const& get_name() const = 0;
};


/// A string literal.
class StringLiteral : public Literal {
public:
	/**
	 * Get the string value of this literal.
	 * @return	The string value of this literal.
	 */
	virtual std::string const& get_value() const = 0;
};


/// An integer literal.
class IntegerLiteral : public Literal {
public:
	/**
	 * Get the integer value of this literal.
	 * @return	The integer value of this literal.
	 */
	virtual elision::eint_t const& get_value() const = 0;
};


/**
 * A float literal.  These are composed of three elements: the
 * @b significand @f$s$, the @b exponent @f$e$, and the @b radix @f$r$.
 * These yield the float value:
 * @f[
 *     v = s \times {r^e}
 * @f]
 */
class FloatLiteral : public Literal {
public:
	/**
	 * Get the significand of this literal.
	 * @return	The significand.
	 */
	virtual elision::eint_t const& get_significand() const = 0;

	/**
	 * Get the exponent of this literal.
	 * @return	The exponent.
	 */
	virtual elision::eint_t const& get_exponent() const = 0;

	/**
	 * Get the radix, which determines how the exponent is interpreted.
	 * @return	The radix.
	 */
	virtual uint16_t get_radix() const = 0;

	/**
	 * Get the float value as a @c double.
	 * @return	This value as a double.
	 */
	virtual operator double() const = 0;
};


/// A bit string literal.
class BitStringLiteral : public Literal {
public:
	/**
	 * Get the bit value of this bit string.
	 * @return	The bit value part of the bit string.
	 */
	virtual elision::eint_t const get_bits() const = 0;

	/**
	 * Get the length of this bit string.
	 * @return	The length (number of bits) in this bit string.
	 */
	virtual uint16_t get_length() const = 0;
};


/// A Boolean literal.
class BooleanLiteral : public Literal {
public:
	/**
	 * Get this literal as a @c bool value.
	 * @return	The value of this literal.
	 */
	virtual operator bool() const = 0;
};


/// A term literal.
class TermLiteral : public Literal {
public:
	/**
	 * Get the underlying term value.
	 * @return	The underlying term.
	 */
	virtual Term const& get_term() const = 0;
};

} /* namespace term */
} /* namespace elision */


#endif /* LITERAL_H_ */
