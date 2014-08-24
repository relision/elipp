/**
 * @file
 * TODO: Describe purpose of file.
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

#include "ApplyImpl.h"
#include "BindingImpl.h"
#include "LambdaImpl.h"
#include "ListImpl.h"
#include "LiteralImpl.h"
#include "LambdaImpl.h"
#include "PropertySpecificationImpl.h"
#include "PropertySpecificationBuilderImpl.h"
#include "SpecialFormImpl.h"
#include "StaticMapImpl.h"
#include "VariableImpl.h"
#include "TermFactoryImpl.h"
#include <memory>

namespace elision {
namespace term {
namespace basic {

class RootTerm;
typedef std::shared_ptr<RootTerm const> Root;

/**
 * Provide a private implementation of the root term.
 */
class RootTerm : public virtual ITerm {
public:
	/**
	 * Get the unique instance of the root term.
	 * @return The root term.
	 */
	static pTerm fetch() {
		// Make a new instance of myself.  This is static so we really, really
		// only ever get one.  Just one.  Only one.  Note that we cannot use
		// make_shared because the constructor is private.
		static Root self = std::shared_ptr<RootTerm>(new RootTerm());
		// Make this instance its own type.
		self.get()->me_ = self;
		return self;
	}

	/// Clean up this instance.
	~RootTerm() {};

	inline bool is_constant() const { return true; }
	inline std::string to_string() const { return "^ROOT"; }
	inline pTerm get_type() const { return me_; }
	inline unsigned int get_de_bruijn_index() const { return 0; }
	inline unsigned int get_depth() const { return 0; }
	inline bool is_meta_term() const { return false; }
	inline Locus get_loc() const { return loc_; }
	inline bool is_root() const { return true; }
	inline bool is_true() const { return false; }
	inline bool is_false() const { return false; }
	inline TermKind get_kind() const { return ROOT_KIND; }
	inline size_t get_hash() const { return 1; }
	inline size_t get_other_hash() const { return 0xcafebabe; }

protected:
	inline bool is_equal(ITerm const& other) const {
		// If we get here then we match.  What's the logic for this?  Well,
		// we've already matched on the term kind (in the == method), so
		// we known the other term is also a root.
		(void)other; // Avoid warnings about unused parameter.
		return true;
	}

private:
	/**
	 * Construct a new instance.  This is private because it must only be
	 * called from `fetch`, which explicitly "fixes up" the `me_` field.
	 */
	RootTerm() {}

	/// Our type, which is ourself.
	mutable Root me_;

	/// Hold the internal loc for fast reference.
	Locus loc_ = Loc::get_internal();
};

// Little macro to initialize the root types.
#define INIT(m_name) m_name = get_root_term(#m_name);

TermFactoryImpl::TermFactoryImpl() : root_(RootTerm::fetch()) {
	// Initialize the well-known root terms.
	ROOT = root_;
	INIT(SYMBOL);
	INIT(STRING);
	INIT(INTEGER);
	INIT(FLOAT);
	INIT(BITSTRING);
	INIT(BOOLEAN);
	INIT(ANY);
	INIT(NONE);
	INIT(MAP);
	INIT(SPECIAL_FORM);
	INIT(PROPERTIES);
	TERM = get_symbol_literal(Loc::get_internal(), "TERM", SYMBOL);
	TRUE = get_boolean_literal(Loc::get_internal(), true, BOOLEAN);
	FALSE = get_boolean_literal(Loc::get_internal(), false, BOOLEAN);

	// Build a term modifier we can use later.
//	auto self = std::shared_ptr<TermFactory>(this);
//	modifier_ = std::unique_ptr<TermModifier>(new TermModifier(self));
}

pSymbolLiteral
TermFactoryImpl::get_root_term(std::string const name) const {
	// Go and get a pointer from the map.
	pSymbolLiteral rt = known_roots_[name];
	if (!rt) {
		// First time through.  Make a new symbol and store it.
		pSymbolLiteral nrt =
				get_symbol_literal(Loc::get_internal(), name, root_);
		known_roots_[name] = nrt;
		return nrt;
	}
	return rt;
}

// Shorthand to make a shared pointer of the correct type with the provided
// arguments.  Depends on names being the "usual" names.
#define MAKE(m_kind, ...) \
	std::shared_ptr<I ## m_kind const>(new m_kind ## Impl(loc, __VA_ARGS__))

pSymbolLiteral
TermFactoryImpl::get_symbol_literal(
		Locus loc, std::string const& name, pTerm type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(SymbolLiteral, name, type);
}

pStringLiteral
TermFactoryImpl::get_string_literal(
		Locus loc, std::string const& value, pTerm type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(StringLiteral, value, type);
}

pIntegerLiteral
TermFactoryImpl::get_integer_literal(
		Locus loc, eint_t value, pTerm type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(IntegerLiteral, value, type);
}

pFloatLiteral
TermFactoryImpl::get_float_literal(
		Locus loc, eint_t significand, eint_t exponent, uint16_t radix,
		pTerm type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(FloatLiteral, significand, exponent, radix, type);
}

pBitStringLiteral
TermFactoryImpl::get_bit_string_literal(
		Locus loc, eint_t bits, eint_t length, pTerm type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(BitStringLiteral, bits, length, type);
}

pBooleanLiteral
TermFactoryImpl::get_boolean_literal(
		Locus loc, bool value, pTerm type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(BooleanLiteral, value, type);
}

pTermLiteral
TermFactoryImpl::get_term_literal(
		Locus loc, pTerm term) const {
	NOTNULL(loc);
	NOTNULL(term);
	return MAKE(TermLiteral, term,
			get_special_form(Loc::get_internal(), TERM, term->get_type()));
}

pVariable
TermFactoryImpl::get_variable(
		Locus loc, std::string name, pTerm guard, pTerm type) const {
	NOTNULL(loc);
	NOTNULL(guard);
	NOTNULL(type);
	return MAKE(Variable, name, guard, type);
}

pTermVariable
TermFactoryImpl::get_term_variable(
		Locus loc, std::string name, pTerm term_type) const {
	NOTNULL(loc);
	NOTNULL(term_type);
	return MAKE(TermVariable, name, term_type,
			get_special_form(Loc::get_internal(), TERM, term_type));
}

pStaticMap
TermFactoryImpl::get_static_map(
		Locus loc, pTerm domain, pTerm codomain) const {
	NOTNULL(loc);
	NOTNULL(domain);
	NOTNULL(codomain);
	return MAKE(StaticMap, domain, codomain, MAP);
}

pLambda
TermFactoryImpl::get_lambda(
		Locus loc, pTerm lhs, pTerm rhs, pTerm guard) const {
	NOTNULL(loc);
	NOTNULL(lhs);
	NOTNULL(rhs);
	NOTNULL(guard);

	// The type for a lambda has to be computed.  We do that here, and then we
	// pass it to the constructor.  The type of the lambda is a static map from
	// the type of the lhs to the type of the rhs.
	pTerm type = get_static_map(loc, lhs->get_type(), rhs->get_type());
	return MAKE(Lambda, lhs, rhs, guard, type);
}

pSpecialForm
TermFactoryImpl::get_special_form(Locus loc, pTerm tag, pTerm content) const {
	NOTNULL(loc);
	NOTNULL(tag);
	NOTNULL(content);
	return MAKE(SpecialForm, tag, content, SPECIAL_FORM);
}

pList
TermFactoryImpl::get_list(Locus loc, pPropertySpecification spec,
		std::vector<pTerm>& elements) const {
	NOTNULL(loc);
	NOTNULL(spec);

	// Keep this around.
	static pSymbolLiteral LIST =
			get_symbol_literal(Loc::get_internal(), "LIST", SYMBOL);

	// The real type for the list is deduced from the element specification in
	// the property specification.
	boost::optional<pTerm> membership = spec->get_membership();
	// The method get_value_or causes pain right now, so we avoid it.
	pTerm element_type = membership ? membership.get() : ANY;
	pTerm the_type = get_special_form(loc, LIST, element_type);
	return MAKE(List, spec, elements, the_type);
}

pTerm
TermFactoryImpl::apply(Locus loc, pTerm op, pTerm arg) const {
	NOTNULL(loc);
	NOTNULL(op);
	NOTNULL(arg);

	// Decide what to do based on the operator's kind.
	switch (op->get_kind()) {
	case BINDING_KIND: {
		// Applying a binding replaces bound variables with their bound terms.
		auto binding = std::dynamic_pointer_cast<IBinding const>(op);
		auto map = binding->get_map().get();
		return modifier_->substitute(*map, arg);
		break;
	}

	case LAMBDA_KIND: {
		// Applying a map pair matches the pattern, checks the guard, and then
		// yields any replacement.
//		auto map_pair = std::dynamic_pointer_cast<IMapPair const>(op);
//		auto result = Matcher::match(map_pair->get_lhs(), argument);
//		if (result) {
//			// The match succeeded.  Check the guard.
//			auto raw = result->next_raw_bindings();
//			if (map_pair->get_guard()->rewrite(raw) == TRUE) {
//				// The guard succeeded.  Rewrite the replacement and return it.
//				return map_pair->get_rhs()->rewrite(raw);
//			}
//		}
//		// If we come here, then either the LHS did not match or the guard
//		// did not evaluate to true.  In either case, no rewrite happens.
//		return argument;
		break;
	}

	case LIST_KIND: {
		// Applying a list concatenates lists.
		if (arg->get_kind() == LIST_KIND) {
			auto first = std::dynamic_pointer_cast<IList const>(op);
			auto second = std::dynamic_pointer_cast<IList const>(arg);
//			return first->catenate(second);
		}
		break;
	}

	case PROPERTY_SPECIFICATION_KIND: {
		// Applying a property specification merges property specifications
		// and modifies lists.
		switch (arg->get_kind()) {
		case LIST_KIND: {
			auto list = std::dynamic_pointer_cast<IList const>(arg);
			auto ps = std::dynamic_pointer_cast<IPropertySpecification const>(op);
			auto psb = get_property_specification_builder();
			auto newps = psb->override(list->get_property_specification())
					->override(ps)->get();
			std::vector<pTerm> elts = list->get_elements();
			return get_list(op->get_loc(), newps, elts);
			break;
		}

		case PROPERTY_SPECIFICATION_KIND: {
			auto opspec = std::dynamic_pointer_cast<IPropertySpecification const>(op);
			auto argspec = std::dynamic_pointer_cast<IPropertySpecification const>(arg);
			auto psb = get_property_specification_builder();
			return psb->override(argspec)->override(opspec)->get();
			break;
		}

		default:
			break;
		}
		break;
	}

	case SPECIAL_FORM_KIND: {
		// Applying a special form may do several things, depending on the tag.
		break;
	}

	default: {
		break;
	}
	} // End of switch.

	// No special handling.
	return MAKE(Apply, op, arg, MAP);
}

std::unique_ptr<PropertySpecificationBuilder>
TermFactoryImpl::get_property_specification_builder() const {
	// Make a new instance and return it.
	return std::unique_ptr<PropertySpecificationBuilder>(
			new PropertySpecificationBuilderImpl(TRUE, FALSE, PROPERTIES));
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
