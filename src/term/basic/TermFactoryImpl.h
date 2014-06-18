#ifndef TERMFACTORY_H_
#define TERMFACTORY_H_

/**
 * @file
 * Define a basic term factory.
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

#include "term/TermFactory.h"
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

	inline virtual pTerm get_root() const {
		return root_;
	}

	virtual pSymbolLiteral get_root_term(std::string const name) const;

	virtual pSymbolLiteral get_symbol_literal(
			Locus loc, std::string const& name, pTerm type) const;
	virtual pStringLiteral get_string_literal(
			Locus loc, std::string const& value, pTerm type) const;
	virtual pIntegerLiteral get_integer_literal(
			Locus loc, eint_t value, pTerm type) const;
	virtual pFloatLiteral get_float_literal(
			Locus loc, eint_t significand, eint_t exponent, uint16_t radix,
			pTerm type) const;
	virtual pBitStringLiteral get_bit_string_literal(
			Locus loc, eint_t bits, eint_t length, pTerm type) const;
	virtual pBooleanLiteral get_boolean_literal(
			Locus loc, bool value, pTerm type) const;

	virtual pVariable get_variable(Locus loc, std::string name, pTerm guard,
			pTerm type) const;
	virtual pTermVariable get_term_variable(Locus loc, std::string name,
			pTerm type) const;

	virtual pStaticMap get_static_map(Locus loc, pTerm domain,
			pTerm codomain) const;

	virtual pMapPair get_map_pair(Locus loc, pTerm lhs, pTerm rhs,
			pTerm guard) const;

	virtual pLambda get_lambda(Locus loc, pVariable parameter,
			pTerm body) const;

	virtual pTerm apply(Locus loc, pTerm op, pTerm arg) const;

private:
	pTerm root_;
	mutable std::unordered_map<std::string, pSymbolLiteral> known_roots_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* TERMFACTORY_H_ */
