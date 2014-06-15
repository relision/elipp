/**
 * @file
 * Provide an implementation of static maps.
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

#include <basic/StaticMapImpl.h>

namespace elision {
namespace term {
namespace basic {

StaticMapImpl::StaticMapImpl(Locus the_loc, pTerm the_domain,
		pTerm the_codomain, pTerm the_type) : TermImpl(the_loc, the_type),
				domain_(the_domain), codomain_(the_codomain) {
}

std::string
StaticMapImpl::to_string() const {
	return domain_->to_string() + "=>" + codomain_->to_string();
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
