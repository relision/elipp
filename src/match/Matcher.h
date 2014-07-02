#ifndef MATCHER_H_
#define MATCHER_H_

/**
 * @file
 * Define the interface to the matching subsystem.
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

namespace elision {
namespace match {

/**
 * Perform constrained matching on two terms.
 */
class Matcher {
public:
	Matcher();
	virtual ~Matcher();


};

} /* namespace match */
} /* namespace elision */

#endif /* MATCHER_H_ */
