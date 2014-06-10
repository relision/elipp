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

#include "ITermFactory.h"
#include "Term.h"
#include <unordered_map>
#include <string>

namespace elision {
namespace term {
namespace basic {

using namespace elision::term;

/**
 * Provide a private implementation of the root term.
 */
class RootTerm : public virtual Term {
public:
	RootTerm() : Term(std::shared_ptr<ITerm const>(this)) {}
	~RootTerm() = default;
	inline bool is_constant() const { return true; }
	inline operator std::string() const { return "^ROOT"; }
};

/**
 * Implement a basic term factory that makes terms using the implementations in
 * the `elision::term::basic` namespace.
 */
class TermFactory: public ITermFactory {
public:
	/// Make a new instance.
	TermFactory();

	/// Deallocate this instance.
	virtual ~TermFactory() = default;

	inline virtual EPTR(ITerm) get_root() const {
		return root_;
	}

	virtual EPTR(ISymbolLiteral) get_root_term(std::string const name) const;

	virtual EPTR(ISymbolLiteral) get_symbol_literal(
			EPTR(Loc) loc, std::string const& name, EPTR(ITerm) type) const;
	virtual EPTR(IStringLiteral) get_string_literal(
			EPTR(Loc) loc, std::string const& value, EPTR(ITerm) type) const;
	virtual EPTR(IIntegerLiteral) get_integer_literal(
			EPTR(Loc) loc, eint_t value, EPTR(ITerm) type) const;
	virtual EPTR(IFloatLiteral) get_float_literal(
			EPTR(Loc) loc, eint_t significand, eint_t exponent, uint16_t radix,
			EPTR(ITerm) type) const;
	virtual EPTR(IBitStringLiteral) get_bit_string_literal(
			EPTR(Loc) loc, eint_t bits, eint_t length, EPTR(ITerm) type) const;
	virtual EPTR(IBooleanLiteral) get_boolean_literal(
			EPTR(Loc) loc, bool value, EPTR(ITerm) type) const;

private:
	EPTR(ITerm) root_ = std::shared_ptr<ITerm const>(new RootTerm());
	mutable std::unordered_map<std::string, EPTR(ISymbolLiteral)> known_roots_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* TERMFACTORY_H_ */
