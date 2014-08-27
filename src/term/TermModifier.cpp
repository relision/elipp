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

#include "TermModifier.h"

namespace elision {
namespace term {
namespace basic {

TermModifier::TermModifier(TermFactory const& fact) : fact_(fact) {
	// Nothing to do.
}

pTerm
TermModifier::substitute(std::map<std::string, pTerm> const& map,
		pTerm target) const {
	NOTNULL(target);

	// Define the closure that instantiates variables as they are found.
	auto closure = [this, map](pTerm term) -> pTerm {
		switch (term->get_kind()) {
		case VARIABLE_KIND: {
			// See if this is a variable that can be replaced right now.  If so, we
			// are done.  We don't need to consider the type, because we are going
			// to get that from the replacement.
			pVariable var = TERM_CAST(IVariable, term);
			auto search = map.find(var->get_name());
			if (search != map.end()) {
				// Found this variable, so replace it now.
				return search->second;
			}
			break;
		}

		case TERM_VARIABLE_KIND: {
			// See if this term variable can be replaced right now.  If so,
			// then we have to construct a term literal, but in any case we
			// are done.
			pTermVariable tvar = TERM_CAST(ITermVariable, term);
			auto search = map.find(tvar->get_name());
			if (search != map.end()) {
				// Found the variable.  Build a term literal around the
				// replacement and return the result.
				return fact_.get_term_literal(tvar->get_loc(), search->second);
			}
			break;
		}

		default: break;
		}
		return term;
	};

	// Perform the replacement.
	return rebuild(target, closure);
}

pTerm
TermModifier::rebuild(pTerm target,
		std::function<pTerm (pTerm)> closure) const {
	NOTNULL(target);
	NOTNULL(closure);

	// See if the closure wants to replace this term immediately.
	pTerm new_term = closure(target);
	if (new_term != target) {
		return new_term;
	}

	// The target did not get replaced immediately so now we have to
	// descend into the type and the children.  We use this method to
	// rebuild all of them, potentially.

	// Now compute over the children and - if necessary - rebuild the
	// term.
	switch (target->get_kind()) {
	case SYMBOL_LITERAL_KIND: {
		// Compute a possibly new type.
		pTerm new_type = rebuild(target->get_type(), closure);
		if ((target->get_type() != new_type)) {
			pSymbolLiteral lit = TERM_CAST(ISymbolLiteral, target);
			return fact_.get_symbol_literal(lit->get_loc(), lit->get_name(),
					new_type);
		}
		break;
	}

	case STRING_LITERAL_KIND: {
		// Compute a possibly new type.
		pTerm new_type = rebuild(target->get_type(), closure);
		if ((target->get_type() != new_type)) {
			pStringLiteral lit = TERM_CAST(IStringLiteral, target);
			return fact_.get_string_literal(lit->get_loc(), lit->get_value(),
					new_type);
		}
		break;
	}

	case INTEGER_LITERAL_KIND: {
		// Compute a possibly new type.
		pTerm new_type = rebuild(target->get_type(), closure);
		if ((target->get_type() != new_type)) {
			pIntegerLiteral lit = TERM_CAST(IIntegerLiteral, target);
			return fact_.get_integer_literal(lit->get_loc(), lit->get_value(),
					new_type);
		}
		break;
	}

	case FLOAT_LITERAL_KIND: {
		// Compute a possibly new type.
		pTerm new_type = rebuild(target->get_type(), closure);
		if ((target->get_type() != new_type)) {
			pFloatLiteral lit = TERM_CAST(IFloatLiteral, target);
			return fact_.get_float_literal(lit->get_loc(),
					lit->get_significand(), lit->get_exponent(),
					lit->get_radix(), new_type);
		}
		break;
	}

	case BIT_STRING_LITERAL_KIND: {
		// Compute a possibly new type.
		pTerm new_type = rebuild(target->get_type(), closure);
		if ((target->get_type() != new_type)) {
			pBitStringLiteral lit = TERM_CAST(IBitStringLiteral, target);
			return fact_.get_bit_string_literal(lit->get_loc(),
					lit->get_bits(), lit->get_length(), new_type);
		}
		break;
	}

	case BOOLEAN_LITERAL_KIND: {
		// Compute a possibly new type.
		pTerm new_type = rebuild(target->get_type(), closure);
		if ((target->get_type() != new_type)) {
			pBooleanLiteral lit = TERM_CAST(IBooleanLiteral, target);
			return fact_.get_boolean_literal(lit->get_loc(), lit->get_value(),
					new_type);
		}
		break;
	}

	case TERM_LITERAL_KIND: {
		pTermLiteral lit = TERM_CAST(ITermLiteral, target);
		pTerm term = lit->get_term();
		pTerm new_term = rebuild(term, closure);
		if (new_term != term) {
			return fact_.get_term_literal(lit->get_loc(), new_term);
		}
		break;
	}

	case VARIABLE_KIND: {
		// Compute a possibly new type.
		pTerm new_type = rebuild(target->get_type(), closure);
		pVariable var = TERM_CAST(IVariable, target);
		pTerm guard = var->get_guard();
		pTerm new_guard = rebuild(guard, closure);
		if ((target->get_type() != new_type) || (guard != new_guard)) {
			return fact_.get_variable(var->get_loc(), var->get_name(),
					new_guard, new_type);
		}
		break;
	}

	case TERM_VARIABLE_KIND: {
		pTermVariable var = TERM_CAST(ITermVariable, target);
		pTerm term_type = var->get_term_type();
		pTerm new_term_type = rebuild(term_type, closure);
		if (term_type != new_term_type) {
			return fact_.get_term_variable(var->get_loc(), var->get_name(),
					new_term_type);
		}
		break;
	}

	case BINDING_KIND: {
		pBinding bind = TERM_CAST(IBinding, target);
		// TODO Implement this.
		break;
	}

	case LAMBDA_KIND: {
		pLambda mp = TERM_CAST(ILambda, target);
		pTerm lhs = mp->get_lhs();
		pTerm rhs = mp->get_rhs();
		pTerm guard = mp->get_guard();
		pTerm new_lhs = rebuild(lhs, closure);
		pTerm new_rhs = rebuild(rhs, closure);
		pTerm new_guard = rebuild(guard, closure);
		if (lhs != new_lhs || rhs != new_rhs || guard != new_guard) {
			return fact_.get_lambda(mp->get_loc(), new_lhs, new_rhs, new_guard);
		}
		break;
	}

	case LIST_KIND: {
		pList list = TERM_CAST(IList, target);
		// TODO Implement this.
		break;
	}

	case PROPERTY_SPECIFICATION_KIND: {
		pPropertySpecification spec = TERM_CAST(IPropertySpecification, target);
		// TODO Implement this.
		break;
	}

	case SPECIAL_FORM_KIND: {
		pSpecialForm sf = TERM_CAST(ISpecialForm, target);
		pTerm tag = sf->get_tag();
		pTerm content = sf->get_content();
		pTerm new_tag = rebuild(tag, closure);
		pTerm new_content = rebuild(content, closure);
		if (tag != new_tag || content != new_content) {
			return fact_.get_special_form(sf->get_loc(), new_tag, new_content);
		}
		break;
	}

	case APPLY_KIND: {
		pApply apply = TERM_CAST(IApply, target);
		pTerm op = apply->get_operator();
		pTerm arg = apply->get_argument();
		pTerm new_op = rebuild(op, closure);
		pTerm new_arg = rebuild(arg, closure);
		if (op != new_op || arg != new_arg) {
			return fact_.apply(apply->get_loc(), op, arg);
		}
		break;
	}

	case STATIC_MAP_KIND: {
		pStaticMap map = TERM_CAST(IStaticMap, target);
		pTerm domain = map->get_domain();
		pTerm codomain = map->get_codomain();
		pTerm new_domain = rebuild(domain, closure);
		pTerm new_codomain = rebuild(codomain, closure);
		if (domain != new_domain || codomain != new_codomain) {
			return fact_.get_static_map(map->get_loc(), domain, codomain);
		}
		break;
	}

	case ROOT_KIND:
	default:
		break;
	} // Switch on kind.

	// Nothing changed.
	return target;
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
