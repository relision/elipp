#ifndef BASICTERM_H_
#define BASICTERM_H_

/**
 * @file
 * Provide a basic definition of a term.
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

#include "Loc.h"
#include "Term.h"

namespace elision {
namespace term {
namespace basic {

/**
 * Provide a basic implementation of elements common to terms.
 */
class BasicTerm: public elision::term::Term {
public:
	/**
	 * Make a new instance.
	 * @param loc		The location of the term's definition.
	 * @param type		The type of this term.
	 */
	BasicTerm(Loc const& loc, Term const& type);

	/// Deallocate this instance.
	virtual ~BasicTerm() = default;

private:
	Loc const& loc_;
	Term const& type_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* BASICTERM_H_ */
