#ifndef ILITERAL_H_
#define ILITERAL_H_

/**
 * @file
 * Specify the public interface to literals.
 *
 * @author sprowell@gmail.com
 *
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
#include <stdint.h>

namespace elision {
namespace term {

/**
 * The common public interface for all literals.  A literal represents a simple
 * constant term in Elision.  Other terms can also represent constants, as well,
 * but a literal is the "most primitive" form of constant manipulated by the
 * system.
 */
class ILiteral : public virtual ITerm {
public:
	// Nothing to see.
};

/// Shorthand for a pointer to a literal.
typedef std::shared_ptr<ILiteral const> pLiteral;


/**
 * Specify the public interface to a symbol literal.  Symbols are just simple
 * strings that are used for function names and well-known types.
 */
class ISymbolLiteral : public virtual ILiteral {
public:
	/**
	 * Get the name of this symbol.
	 * @return	The name of this symbol.
	 */
	virtual std::string const get_name() const = 0;
};

/// Shorthand for a symbol literal pointer.
typedef std::shared_ptr<ISymbolLiteral const> pSymbolLiteral;


/**
 * Specify the public interface to a string literal.  String literals are just
 * the usual string literals you find in most languages.
 */
class IStringLiteral : public virtual ILiteral {
public:
	/**
	 * Get the value of this string literal.
	 * @return	The value of this string literal.
	 */
	virtual std::string const get_value() const = 0;
};

/// Shorthand for a string literal pointer.
typedef std::shared_ptr<IStringLiteral const> pStringLiteral;


/**
 * Specify the public interface to an integer literal.  Elision integers are
 * (essentially) unbounded integers, similar to the "big integer" classes in
 * some languages.
 */
class IIntegerLiteral : public virtual ILiteral {
public:
	/**
	 * Get the value of this integer literal.
	 * @return	The value of this integer literal.
	 */
	virtual elision::eint_t get_value() const = 0;
};

/// Shorthand for a integer literal pointer.
typedef std::shared_ptr<IIntegerLiteral const> pIntegerLiteral;


/**
 * Specify the public interface to a floating point literal.  Elision floating
 * point literals are constructed from unbounded integers and are, essentially,
 * also unbounded.  A floating point literal is composed of three elements:
 *
 *   - a @b significand @f$s@f$,
 *   - an @b exponent @f$e@f$, and
 *   - the base, or @b radix @f$r@f$.
 *
 * These three values are combined to yield the value of the literal, which is
 * given by the equation:
 *
 * @f[
 *     v = s \times {r^e}
 * @f]
 *
 * This is actually pretty common.  For instance 5e2 (base 10) is 5 times 10
 * squared, or 500.  Here 5 is the significand, 2 is the exponent, and 10 is
 * the base.
 *
 * Elision @e normalizes floats so that they do not contain any fractional part.
 * For instance, given 2.5e3, this is modified to 25e2 (or 2500).
 */
class IFloatLiteral : public virtual ILiteral {
public:
	/**
	 * Get the significand for this float.
	 * @return	The significand.
	 */
	virtual elision::eint_t get_significand() const = 0;

	/**
	 * Get the exponent for this float.
	 * @return	The exponent.
	 */
	virtual elision::eint_t get_exponent() const = 0;

	/**
	 * Get the radix, or base, of this float.
	 * @return	The radix.
	 */
	virtual uint8_t get_radix() const = 0;
};

/// Shorthand for a float literal pointer.
typedef std::shared_ptr<IFloatLiteral const> pFloatLiteral;


/**
 * Specify the public interface to a bit string.
 *
 * Elision bit strings represent a fixed number of zero or more bits.  A length
 * zero bit string is acceptable.  Bit strings are written by giving the bit
 * value as an integer in some base, followed by an `L`, followed by the length.
 * Thus `0L0` is a length zero bit string, and `1L4` is the bit string `0001`.
 */
class IBitStringLiteral : public virtual ILiteral {
public:
	/**
	 * Get the bits of this bit string.
	 * @return	The bits of this bit string.
	 */
	virtual elision::eint_t get_bits() const = 0;

	/**
	 * Get the number of bits in this bit string.
	 * @return	The number of bits in this bit string.
	 */
	virtual elision::eint_t get_length() const = 0;
};

/// Shorthand for a bit string literal pointer.
typedef std::shared_ptr<IBitStringLiteral const> pBitStringLiteral;


/**
 * Specify the public interface to a Boolean literal.  This is a literal that
 * holds a Boolean truth value, and is either `true` or `false`.
 */
class IBooleanLiteral : public virtual ILiteral {
public:
	/**
	 * Get this Boolean literal as a platform `bool` value.
	 * @return	The Boolean value of this Boolean literal.
	 */
	virtual bool get_value() const = 0;
};

/// Shorthand for a boolean literal pointer.
typedef std::shared_ptr<IBooleanLiteral const> pBooleanLiteral;


/**
 * Specify the public interface to a term literal.  Term literals represent a
 * term, not a value, which distinguishes them from other literals and terms,
 * with the exception of term variables.
 */
class ITermLiteral : public virtual ILiteral {
public:
	/**
	 * Get the underlying term value.
	 * @return	The underlying term.
	 */
	virtual pTerm get_term() const = 0;
};

/// Shorthand for a term literal pointer.
typedef std::shared_ptr<ITermLiteral const> pTermLiteral;

} /* namespace term */
} /* namespace elision */

#endif /* ILITERAL_H_ */
