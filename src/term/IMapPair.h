#ifndef IMAPPAIR_H_
#define IMAPPAIR_H_

/**
 * @file
 * Define the public interface to a map pair.
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

#include "ITerm.h"

namespace elision {
namespace term {

/**
 * Specify the public interface to a map pair.  A map pair consists of a left-
 * (lhs) and right-hand side (rhs), and a guard.  The effect of applying a map
 * pair to another term (the argument) is to match the argument (the subject)
 * against the lhs (the pattern), giving a set of bindings.  The bidings are
 * then applied to the guard.  If the guard evaluates to `true`, then the
 * bindings are applied to the rhs to yield a new term.  If the argument does
 * not match the lhs, or the guard does not evaluate to `true`, then no new
 * term is generated.
 */
class IMapPair : public virtual ITerm {
public:
	/**
	 * Get the left hand side of this map pair.
	 * @return	The left hand term.
	 */
	virtual pTerm get_lhs() const = 0;

	/**
	 * Get the right hand side of this map pair.
	 * @return	The right hand side.
	 */
	virtual pTerm get_rhs() const = 0;

	/**
	 * Get the guard for this map pair.
	 * @return	The guard for this map pair.
	 */
	virtual pTerm get_guard() const = 0;
};

/// Shorthand for a map pair pointer.
typedef std::shared_ptr<IMapPair const> MapPair;

} /* namespace term */
} /* namespace elision */


#endif /* IMAPPAIR_H_ */
