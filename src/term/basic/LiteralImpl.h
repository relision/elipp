#ifndef LITERAL_H_
#define LITERAL_H_

/**
 * @file
 * Provide a basic implementation of literals.
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

#include "TermImpl.h"
#include "term/ILiteral.h"
#include <Lazy.h>

namespace elision {
namespace term {
namespace basic {

using namespace elision;
using namespace elision::term;


class SymbolLiteralImpl : public ISymbolLiteral, public TermImpl {
public:
	inline std::string const get_name() const {
		return name_;
	}

	inline bool is_constant() const {
		return true;
	}

	inline std::string to_string() const {
		return strval_;
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<SymbolLiteralImpl const&>(other);
		return get_name() == oth.get_name();
	}

	inline TermKind get_kind() const {
		return SYMBOL_LITERAL_KIND;
	}

	inline unsigned int get_depth() const {
		return get_type()->get_depth();
	}

private:
	friend class TermFactoryImpl;
	SymbolLiteralImpl(Locus the_loc, std::string the_name, pTerm the_type);
	std::string const name_;
	Lazy<std::string> strval_;
};


class StringLiteralImpl : public IStringLiteral, public TermImpl {
public:
	inline std::string const get_value() const {
		return value_;
	}

	inline bool is_constant() const {
		return true;
	}

	inline std::string to_string() const {
		return strval_;
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<StringLiteralImpl const&>(other);
		return get_value() == oth.get_value();
	}

	inline TermKind get_kind() const {
		return STRING_LITERAL_KIND;
	}

	inline unsigned int get_depth() const {
		return get_type()->get_depth();
	}

private:
	friend class TermFactoryImpl;
	StringLiteralImpl(Locus the_loc, std::string the_value, pTerm the_type);
	std::string const value_;
	Lazy<std::string> strval_;
};


class IntegerLiteralImpl : public IIntegerLiteral, public TermImpl {
public:
	inline eint_t get_value() const {
		return value_;
	}

	inline bool is_constant() const {
		return true;
	}

	inline std::string to_string() const {
		return strval_;
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<IntegerLiteralImpl const&>(other);
		return get_value() == oth.get_value();
	}

	inline TermKind get_kind() const {
		return INTEGER_LITERAL_KIND;
	}

	inline unsigned int get_depth() const {
		return get_type()->get_depth();
	}

private:
	friend class TermFactoryImpl;
	IntegerLiteralImpl(Locus the_loc, eint_t the_value, pTerm the_type);
	eint_t const value_;
	Lazy<std::string> strval_;
};


class FloatLiteralImpl : public IFloatLiteral, public TermImpl {
public:
	inline eint_t get_significand() const {
		return significand_;
	}

	inline eint_t get_exponent() const {
		return exponent_;
	}

	inline uint8_t get_radix() const {
		return radix_;
	}

	inline bool is_constant() const {
		return true;
	}

	inline std::string to_string() const {
		return strval_;
	}

	inline bool is_equal(ITerm const& other) const {
		// TODO Really should check the computed values somehow.
		auto oth = dynamic_cast<FloatLiteralImpl const&>(other);
		return (get_significand() == oth.get_significand()) &&
				(get_exponent() == oth.get_exponent()) &&
				(get_radix() == oth.get_radix());
	}

	inline TermKind get_kind() const {
		return FLOAT_LITERAL_KIND;
	}

	inline unsigned int get_depth() const {
		return get_type()->get_depth();
	}

private:
	friend class TermFactoryImpl;
	FloatLiteralImpl(Locus the_loc, eint_t the_significand, eint_t the_exponent,
			uint8_t the_radix, pTerm the_type);
	eint_t const significand_;
	eint_t const exponent_;
	uint8_t const radix_;
	Lazy<std::string> strval_;
};


class BitStringLiteralImpl : public IBitStringLiteral, public TermImpl {
public:
	inline eint_t get_bits() const {
		return bits_;
	}

	inline eint_t get_length() const {
		return length_;
	}

	inline bool is_constant() const {
		return true;
	}

	inline std::string to_string() const {
		return strval_;
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<BitStringLiteralImpl const&>(other);
		return (get_bits() == oth.get_bits()) &&
				(get_length() == oth.get_length());
	}

	inline TermKind get_kind() const {
		return BIT_STRING_LITERAL_KIND;
	}

	inline unsigned int get_depth() const {
		return get_type()->get_depth();
	}

private:
	friend class TermFactoryImpl;
	BitStringLiteralImpl(Locus the_loc, eint_t the_bits, eint_t the_length,
			pTerm the_type);
	eint_t const bits_;
	eint_t const length_;
	Lazy<std::string> strval_;
};


class BooleanLiteralImpl : public IBooleanLiteral, public TermImpl {
public:
	inline bool get_value() const {
		return value_;
	}

	inline bool is_constant() const {
		return true;
	}

	inline std::string to_string() const {
		return strval_;
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<BooleanLiteralImpl const&>(other);
		return get_value() == oth.get_value();
	}

	inline TermKind get_kind() const {
		return BOOLEAN_LITERAL_KIND;
	}

	inline bool is_true() const {
		return value_;
	}

	inline bool is_false() const {
		return !value_;
	}

	inline unsigned int get_depth() const {
		return get_type()->get_depth();
	}

private:
	friend class TermFactoryImpl;
	BooleanLiteralImpl(Locus the_loc, bool value, pTerm the_type);
	bool const value_;
	Lazy<std::string> strval_;
};


class TermLiteralImpl : public ITermLiteral, public TermImpl {
public:
	inline pTerm get_term() const {
		return term_;
	}

	inline bool is_constant() const {
		return true;
	}

	inline std::string to_string() const {
		return strval_;
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<TermLiteralImpl const&>(other);
		return get_term() == oth.get_term();
	}

	inline TermKind get_kind() const {
		return TERM_LITERAL_KIND;
	}

	inline unsigned int get_depth() const {
		return std::max(get_type()->get_depth(), get_term()->get_depth());
	}

private:
	friend class TermFactoryImpl;
	TermLiteralImpl(Locus the_loc, pTerm the_term, pTerm the_type);
	pTerm term_;
	Lazy<std::string> strval_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* LITERAL_H_ */
