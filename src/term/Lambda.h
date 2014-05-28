#ifndef LAMBDA_H_
#define LAMBDA_H_

/**
 * @file
 * Definition of lambdas.
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

#include "Term.h"
#include "Variable.h"

namespace elision {
namespace term {

/**
 * A lambda.
 */
class Lambda : Term {
public:
	/**
	 * Get the lambda parameter.
	 * @return	The lambda parameter.
	 */
	virtual Variable const& get_parameter() const = 0;

	/**
	 * Get the lambda body.
	 * @return	The lambda body.
	 */
	virtual Term const& get_body() const = 0;
};

} /* namespace term */
} /* namespace elision */

#endif /* LAMBDA_H_ */
