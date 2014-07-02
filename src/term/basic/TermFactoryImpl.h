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
#include "term/TermModifier.h"
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
	virtual ~TermFactoryImpl() = default;

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
	virtual pTermLiteral get_term_literal(
			Locus loc, pTerm term) const;

	virtual pVariable get_variable(Locus loc, std::string name, pTerm guard,
			pTerm type) const;
	virtual pTermVariable get_term_variable(Locus loc, std::string name,
			pTerm term_type) const;

	virtual pStaticMap get_static_map(Locus loc, pTerm domain,
			pTerm codomain) const;

	virtual pLambda get_lambda(Locus loc, pTerm lhs, pTerm rhs,
			pTerm guard) const;

	virtual pSpecialForm get_special_form(Locus loc, pTerm tag,
			pTerm content) const;

	virtual pList get_list(Locus loc, pPropertySpecification spec,
			std::vector<pTerm>& elements) const;

	virtual pTerm apply(Locus loc, pTerm op, pTerm arg) const;

	virtual std::unique_ptr<PropertySpecificationBuilder>
	get_property_specification_builder() const;

private:
	pTerm root_;
	mutable std::unordered_map<std::string, pSymbolLiteral> known_roots_;
	std::unique_ptr<TermModifier> modifier_{new TermModifier(*this)};
	static pTerm TERM =
			get_symbol_literal(Loc::get_internal(), "TERM", SYMBOL);

};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* TERMFACTORY_H_ */
