/**
 * @file
 * Provide an implementation of a map pair.
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

#include <basic/MapPairImpl.h>

namespace elision {
namespace term {
namespace basic {

MapPairImpl::MapPairImpl(Locus the_loc, pTerm the_lhs, pTerm the_rhs,
		pTerm the_guard, pTerm the_type) : TermImpl(the_loc, the_type),
				lhs_(the_lhs), rhs_(the_rhs), guard_(the_guard) {
}

std::string
MapPairImpl::to_string() const {
	return lhs_->to_string() + " ->{ " + guard_->to_string() + " } " +
			rhs_->to_string();
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
