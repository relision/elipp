/**
 * @file
 * Provide method implementations for a term.
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

#include "TermImpl.h"

namespace elision {
namespace term {
namespace basic {

TermImpl::TermImpl(Term the_type) : type_(the_type), loc_(Loc::get_internal()) {
	NOTNULL(the_type);
}

TermImpl::TermImpl(Locus the_loc, Term the_type) :
	type_(the_type), loc_(the_loc) {
	NOTNULL(the_loc);
	NOTNULL(the_type);
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
