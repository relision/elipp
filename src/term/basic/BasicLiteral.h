#ifndef BASICLITERAL_H_
#define BASICLITERAL_H_

/**
 * @file
 * Define a basic implementation of the literals.
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

namespace elision {
namespace term {
namespace basic {

/**
 * Provide a basic implementation of a symbol literal.
 */
class BasicSymbolLiteral : public elision::term::SymbolLiteral, public BasicTerm {
public:
	BasicSymbolLiteral(Loc const& loc, std::string const& name,
			Term const& type);
	virtual ~BasicSymbolLiteral() = default;
	virtual std::string const& get_name() const {
		return name_;
	}
private:
	std::string const& name_;
};


/**
 * Provide a basic implementation of a string literal.
 */
class BasicStringLiteral : public elision::term::StringLiteral, public BasicTerm {
public:
	BasicStringLiteral(Loc const& loc, std::string const& value,
			Term const& type);
	virtual ~BasicStringLiteral() = default;
	virtual std::string const& get_value() const {
		return value_;
	}
private:
	std::string const& value_;
};


/**
 * Provide a basic implementation of a integer literal.
 */
class BasicIntegerLiteral : public elision::term::IntegerLiteral, public BasicTerm {
public:
	BasicIntegerLiteral(Loc const& loc, eint_t const& value, Term const& type);
	virtual ~BasicIntegerLiteral() = default;
	virtual eint_t const& get_value() const {
		return value_;
	}
private:
	eint_t const& value_;
};


/**
 * Provide a basic implementation of a float literal.
 */
class BasicFloatLiteral : public elision::term::FloatLiteral, public BasicTerm {
public:
	BasicFloatLiteral(Loc const& loc, eint_t const& significand,
			eint_t const& exponent, uint16_t radix, Term const& type);
	virtual ~BasicFloatLiteral() = default;
	virtual eint_t const& get_significand() const {
		return significand_;
	}
	virtual eint_t const& get_exponent() const {
		return exponent_;
	}
	virtual uint16_t get_radix() const {
		return radix_;
	}
	virtual operator double() const {
		return significand_ * (exponent_ ** radix_);
	}
private:
	eint_t const& significand_;
	eint_t const& exponent_;
	uint16_t radix_;
};


/**
 * Provide a basic implementation of a bit string literal.
 */
class BasicBitStringLiteral : public elision::term::BitStringLiteral, public BasicTerm {
public:
	BasicBitStringLiteral(Loc const& loc, eint_t const& bits, uint16_t length,
			Term const& type);
	virtual ~BasicBitStringLiteral() = default;
	virtual eint_t const get_bits() const {
		return bits_;
	}
	virtual uint16_t get_length() const {
		return length_;
	}
private:
	eint_t const& bits_;
	uint16_t length_;
};


/**
 * Provide a basic implementation of a Boolean literal.
 */
class BasicBooleanLiteral : public elision::term::BooleanLiteral, public BasicTerm {
public:
	BasicBooleanLiteral(Loc const& loc, bool value, Term const& type);
	virtual ~BasicBooleanLiteral() = default;
	virtual operator bool() const {
		return value_;
	}
private:
	bool const value_;
};


/**
 * Provide a basic implementation of a term literal.
 */
class BasicTermLiteral : public elision::term::TermLiteral, public BasicTerm {
public:
	BasicTermLiteral(Loc const& loc, Term const& value, Term const& type);
	virtual ~BasicTermLiteral() = default;
	virtual Term const& get_term() const {
		return term_;
	}
private:
	Term const& term_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* BASICLITERAL_H_ */
