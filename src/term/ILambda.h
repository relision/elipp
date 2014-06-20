#ifndef ILAMBDA_H_
#define ILAMBDA_H_

/**
 * @file
 * Define the public interface to a lambda.
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
 * Specify the public interface to a lambda.  A lambda consists of a left-hand
 * side (lhs) and a right-hand side (rhs), and a guard.  The effect of applying
 * a lambda to another term (the argument) is to match the argument (the
 * subject) against the lhs (the pattern), giving a set of bindings.  The
 * bidings are then applied to the guard.  If the guard evaluates to `true`,
 * then the bindings are applied to the rhs to yield a new term.  If the
 * argument does not match the lhs, or the guard does not evaluate to `true`,
 * then no new term is generated.
 */
class ILambda : public virtual ITerm {
public:
	/**
	 * Get the left hand side of this lambda.
	 * @return	The left hand term.
	 */
	virtual pTerm get_lhs() const = 0;

	/**
	 * Get the right hand side of this lambda.
	 * @return	The right hand side.
	 */
	virtual pTerm get_rhs() const = 0;

	/**
	 * Get the guard for this lambda.
	 * @return	The guard for this lambda.
	 */
	virtual pTerm get_guard() const = 0;
};

/// Shorthand for a lambda pointer.
typedef std::shared_ptr<ILambda const> pLambda;

} /* namespace term */
} /* namespace elision */


#endif /* ILAMBDA_H_ */
