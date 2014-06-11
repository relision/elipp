#ifndef TERMFACTORY_H_
#define TERMFACTORY_H_

/**
 * @file
 * Define a basic term factory.
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
#include "TermImpl.h"
#include <unordered_map>
#include <string>

namespace elision {
namespace term {
namespace basic {

using namespace elision::term;

/**
 * Implement a basic term factory that makes terms using the implementations in
 * the `elision::term::basic` namespace.
 */
class TermFactoryImpl: public TermFactory {
public:
	/// Make a new instance.
	TermFactoryImpl();

	/// Deallocate this instance.
	virtual ~TermFactoryImpl() {};

	inline virtual Term get_root() const {
		return root_;
	}

	virtual SymbolLiteral get_root_term(std::string const name) const;

	virtual SymbolLiteral get_symbol_literal(
			Locus loc, std::string const& name, Term type) const;
	virtual StringLiteral get_string_literal(
			Locus loc, std::string const& value, Term type) const;
	virtual IntegerLiteral get_integer_literal(
			Locus loc, eint_t value, Term type) const;
	virtual FloatLiteral get_float_literal(
			Locus loc, eint_t significand, eint_t exponent, uint16_t radix,
			Term type) const;
	virtual BitStringLiteral get_bit_string_literal(
			Locus loc, eint_t bits, eint_t length, Term type) const;
	virtual BooleanLiteral get_boolean_literal(
			Locus loc, bool value, Term type) const;

private:
	Term root_;
	mutable std::unordered_map<std::string, SymbolLiteral> known_roots_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* TERMFACTORY_H_ */
