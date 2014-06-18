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

TermModifier::TermModifier(std::shared_ptr<TermFactory> fact) : fact_(fact) {
}

pTerm
TermModifier::substitute(std::unordered_map<std::string, pTerm>& map,
		pTerm target) const {
	NOTNULL(target);

	// Define the closure that instantiates variables as they are found.
	auto closure = [map](pTerm term) -> pTerm {
		switch (term->get_kind()) {
		case VARIABLE: {
			// See if this is a variable that can be replaced right now.  If so, we
			// are done.  We don't need to consider the type, because we are going
			// to get that from the replacement.
			pVariable var = CAST(Variable, term);
			auto search = map.find(var->get_name());
			if (search != map.end()) {
				// Found this variable, so replace it now.
				return search->second;
			}
			break;
		}

		case TERM_VARIABLE: {
			// See if this term variable can be replaced right now.  If so,
			// then we have to construct a term literal, but in any case we
			// are done.
			pTermVariable tvar = CAST(TermVariable, term);
			auto search = map.find(tvar->get_name());
			if (search != map.end()) {
				// Found the variable.  Build a term literal around the
				// replacement and return the result.
//				return fact_->get_term_literal(tvar->get_loc(), search->second);
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
	// potentially rebuild all of them.

	// Compute a possibly new type.
	pTerm new_type = rebuild(target->get_type(), closure);
	bool changed = (target->get_type() != new_type);

	// Now compute over the children and - if necessary - rebuild the
	// term.
	switch (target->get_kind()) {
	case SYMBOL_LITERAL: {
		pSymbolLiteral lit = CAST(SymbolLiteral, target);
		if (changed) {
			return fact_->get_symbol_literal(lit->get_loc(),
					lit->get_name(), new_type);
		}
		break;
	}

	case STRING_LITERAL: {
		pStringLiteral lit = CAST(StringLiteral, target);
		if (changed) {
			return fact_->get_string_literal(lit->get_loc(),
					lit->get_value(), new_type);
		}
		break;
	}

	case INTEGER_LITERAL: {
		pIntegerLiteral lit = CAST(IntegerLiteral, target);
		if (changed) {
			return fact_->get_integer_literal(lit->get_loc(),
					lit->get_value(), new_type);
		}
		break;
	}

	case FLOAT_LITERAL: {
		pFloatLiteral lit = CAST(FloatLiteral, target);
		if (changed) {
			return fact_->get_float_literal(lit->get_loc(),
					lit->get_significand(), lit->get_exponent(),
					lit->get_radix(), new_type);
		}
		break;
	}

	case BIT_STRING_LITERAL: {
		pBitStringLiteral lit = CAST(BitStringLiteral, target);
		if (changed) {
			return fact_->get_bit_string_literal(lit->get_loc(),
					lit->get_bits(), lit->get_length(), new_type);
		}
		break;
	}

	case BOOLEAN_LITERAL: {
		pBooleanLiteral lit = CAST(BooleanLiteral, target);
		if (changed) {
			return fact_->get_boolean_literal(lit->get_loc(),
					lit->get_value(), new_type);
		}
		break;
	}

	case TERM_LITERAL: {
		pTermLiteral lit = CAST(TermLiteral, target);
		// TODO Implement this.
		break;
	}

	case VARIABLE: {
		pVariable var = CAST(Variable, target);
		pTerm guard = var->get_guard();
		pTerm new_guard = rebuild(guard, closure);
		if (changed || (guard != new_guard)) {
			return fact_->get_variable(var->get_loc(),
					var->get_name(), new_guard, new_type);
		}
		break;
	}

	case TERM_VARIABLE: {
		pTermVariable var = CAST(TermVariable, target);
		if (changed) {
			return fact_->get_term_variable(var->get_loc(),
					var->get_name(), new_type);
		}
		break;
	}

	case BINDING: {
		pBinding bind = CAST(Binding, target);
		// TODO Implement this.
		break;
	}

	case LAMBDA: {
		pLambda lambda = CAST(Lambda, target);
		pVariable par = lambda->get_parameter();
		pTerm body = lambda->get_body();
		pVariable new_par = CAST(Variable, rebuild(par, closure));
		pTerm new_body = rebuild(body, closure);
		if (changed || par != new_par || body != new_body) {
			return fact_->get_lambda(lambda->get_loc(), new_par,
					new_body);
		}
		break;
	}

	case MAP_PAIR: {
		pMapPair mp = CAST(MapPair, target);
		pTerm lhs = mp->get_lhs();
		pTerm rhs = mp->get_rhs();
		pTerm guard = mp->get_guard();
		pTerm new_lhs = rebuild(lhs, closure);
		pTerm new_rhs = rebuild(rhs, closure);
		pTerm new_guard = rebuild(guard, closure);
		if (changed || lhs != new_lhs || rhs != new_rhs ||
				guard != new_guard) {
			return fact_->get_map_pair(mp->get_loc(), lhs, rhs, guard);
		}
		break;
	}

	case LIST: {
		pList list = CAST(List, target);
		// TODO Implement this.
		break;
	}

	case PROPERTY_SPECIFICATION: {
		pPropertySpecification spec = CAST(PropertySpecification, target);
		// TODO Implement this.
		break;
	}

	case SPECIAL_FORM: {
		pSpecialForm sf = CAST(SpecialForm, target);
		// TODO Implement this.
		break;
	}

	case APPLY: {
		pApply apply = CAST(Apply, target);
		pTerm op = apply->get_operator();
		pTerm arg = apply->get_argument();
		pTerm new_op = rebuild(op, closure);
		pTerm new_arg = rebuild(arg, closure);
		if (changed || op != new_op || arg != new_arg) {
			return fact_->apply(apply->get_loc(), op, arg);
		}
		break;
	}

	case STATIC_MAP: {
		pStaticMap map = CAST(StaticMap, target);
		pTerm domain = map->get_domain();
		pTerm codomain = map->get_codomain();
		pTerm new_domain = rebuild(domain, closure);
		pTerm new_codomain = rebuild(codomain, closure);
		if (changed || domain != new_domain || codomain != new_codomain) {
			return fact_->get_static_map(map->get_loc(), domain, codomain);
		}
		break;
	}

	case ROOT:
	default:
		break;
	} // Switch on kind.

	// Nothing changed.
	return target;
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
