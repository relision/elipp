#ifndef ILAMBDA_H_
#define ILAMBDA_H_

/**
 * @file
 * Define the public interface to a lambda.
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

#include "ITerm.h"
#include "IVariable.h"

namespace elision {
namespace term {

class ILambda;
/// Shorthand for a lambda pointer.
typedef std::shared_ptr<ILambda const> Lambda;

/**
 * The public interface to a lambda instance.  A lambda in Elision consists of
 * a single parameter and a body.  When the lambda is applied to another term
 * (the argument), then the argument (or subject) is matched against the
 * parameter (or pattern), yielding a binding (or an error).  The binding is
 * then applied to the body to yield a new term.
 */
class ILambda : public virtual ITerm {
public:
	/**
	 * Get the lambda parameter.
	 * @return	The lambda parameter.
	 */
	virtual Variable get_parameter() const = 0;

	/**
	 * Get the lambda body.
	 * @return	The lambda body.
	 */
	virtual pTerm get_body() const = 0;
};

} /* namespace term */
} /* namespace elision */

#endif /* ILAMBDA_H_ */
