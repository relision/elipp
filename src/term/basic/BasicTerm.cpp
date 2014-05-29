/**
 * @file
 * TODO: Describe purpose of file.
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

#include "BasicTerm.h"

namespace elision {
namespace term {
namespace basic {

BasicTerm::BasicTerm(Loc const& loc, Term const& type) :
		loc_(loc), type_(type) {}

virtual unsigned int
BasicTerm::get_de_bruijn_index() const {
	return 0;
}

virtual unsigned int
BasicTerm::get_depth() const {
	return 1;
}

virtual bool
BasicTerm::is_meta_term() const {
	return false;
}

virtual bool
BasicTerm::is_constant() const {
	return true;
}

virtual Loc const&
BasicTerm::get_loc() const {
	return loc_;
}

virtual Term const&
BasicTerm::get_type() const {
	return type_;
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
