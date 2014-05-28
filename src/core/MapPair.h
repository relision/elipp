#ifndef MAPPAIR_H_
#define MAPPAIR_H_

/**
 * @file
 * Define a map pair.
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

namespace elision {
namespace term {

class MapPair : Term {
public:
	/**
	 * Get the left hand side of this map pair.
	 * @return	The left hand term.
	 */
	virtual Term const& get_lhs() const = 0;

	/**
	 * Get the right hand side of this map pair.
	 * @return	The right hand side.
	 */
	virtual Term const& get_rhs() const = 0;

	/**
	 * Get the guard for this map pair.
	 * @return	The guard for this map pair.
	 */
	virtual Term const& get_guard() const = 0;
};

} /* namespace term */
} /* namespace elision */

#endif /* MAPPAIR_H_ */
