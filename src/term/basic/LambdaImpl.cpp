/**
 * @file
 * Provide an implementation of a lambda.
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

#include <basic/LambdaImpl.h>

namespace elision {
namespace term {
namespace basic {

LambdaImpl::LambdaImpl(Locus the_loc, pTerm the_lhs, pTerm the_rhs,
		pTerm the_guard, pTerm the_type) : TermImpl(the_loc, the_type),
				lhs_(the_lhs), rhs_(the_rhs), guard_(the_guard) {
	strval_ = [this]() {
		return lhs_->to_string() + " ->{ " + guard_->to_string() + " } " +
				rhs_->to_string();
	};
	depth_ = [this, the_type]() {
		// Depth does not depend on the guard.
		return std::max(lhs_->get_depth(),
				std::max(rhs_->get_depth(), the_type->get_depth())) + 1;
	};
	hash_ = [this]() {
		return hash_combine(lhs_, rhs_);
	};
	other_hash_ = [this]() {
		return other_hash_combine(lhs_, rhs_);
	};
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
