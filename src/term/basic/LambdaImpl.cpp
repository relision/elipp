/**
 * @file
 * Provide an implementation of lambdas.
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

LambdaImpl::LambdaImpl(Locus the_loc, pVariable the_parameter, pTerm the_body,
		pTerm the_type) : TermImpl(the_loc, the_type),
				parameter_(the_parameter), body_(the_body) {
	strval_ = [this]() {
		return "\\" + parameter_->to_string() + "." +
				body_->to_string();
	};
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
