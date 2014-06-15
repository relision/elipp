/**
 * @file
 * Provide an implementation of an apply.
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

#include <basic/ApplyImpl.h>

namespace elision {
namespace term {
namespace basic {

ApplyImpl::ApplyImpl(Locus the_loc, pTerm the_operator, pTerm the_argument,
		pTerm the_type) : TermImpl(the_loc, the_type),
				operator_(the_operator), argument_(the_argument) {
}

std::string
ApplyImpl::to_string() const {
	return operator_->to_string() + "." + argument_->to_string();
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
