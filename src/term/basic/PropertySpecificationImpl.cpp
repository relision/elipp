/**
 * @file
 * Provide an implementation of property specifications.
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

#include <basic/PropertySpecificationImpl.h>

namespace elision {
namespace term {
namespace basic {

PropertySpecificationImpl::PropertySpecificationImpl(
		Locus the_loc,
		boost::optional<pTerm> const& the_associative,
		boost::optional<pTerm> const& the_commutative,
		boost::optional<pTerm> const& the_idempotent,
		boost::optional<pTerm> const& the_absorber,
		boost::optional<pTerm> const& the_identity,
		boost::optional<pTerm> const& the_elements,
		pTerm the_type) : TermImpl(the_loc, the_type),
				associative_(the_associative),
				commutative_(the_commutative),
				idempotent_(the_idempotent),
				absorber_(the_absorber),
				identity_(the_identity),
				elements_(the_elements) {
	strval_ = [this]() {
		std::string ret = "%";
		if (associative_) {
			pTerm value = *associative_;
			if (value->is_true()) {
				ret += "A";
			} else if (value->is_false()) {
				ret += "!A";
			} else {
				ret += "A[" + value->to_string() + "]";
			}
		}
		if (commutative_) {
			pTerm value = *commutative_;
			if (value->is_true()) {
				ret += "C";
			} else if (value->is_false()) {
				ret += "!C";
			} else {
				ret += "C[" + value->to_string() + "]";
			}
		}
		if (idempotent_) {
			pTerm value = *idempotent_;
			if (value->is_true()) {
				ret += "I";
			} else if (value->is_false()) {
				ret += "!I";
			} else {
				ret += "I[" + value->to_string() + "]";
			}
		}
		if (absorber_) {
			ret += "B[" + absorber_.get()->to_string() + "]";
		}
		if (identity_) {
			ret += "D[" + identity_.get()->to_string() + "]";
		}
		if (elements_) {
			ret += "E[" + elements_.get()->to_string() + "]";
		}
		return ret;
	};
	constant_ = [this]() {
		return associative_.get()->is_constant() &&
				commutative_.get()->is_constant() &&
				idempotent_.get()->is_constant() &&
				absorber_.get()->is_constant() &&
				identity_.get()->is_constant() &&
				elements_.get()->is_constant();
	};
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */