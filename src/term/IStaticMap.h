#ifndef STATICMAP_H_
#define STATICMAP_H_

/**
 * @file
 * Define the structure of a static map.
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
 * A static map represents a mapping from one term to another.  Unlike a
 * map pair, it cannot be applied and is effectively a constant - though
 * variables may be used for the domain and codomain.
 */
class IStaticMap : public virtual ITerm {
public:
	/**
	 * Get the domain.
	 * @return	The domain.
	 */
	virtual pTerm get_domain() const = 0;

	/**
	 * Get the codomain.
	 * @return	The codomain.
	 */
	virtual pTerm get_codomain() const = 0;
};

/// Shorthand for a map pair pointer.
typedef std::shared_ptr<IStaticMap const> pStaticMap;

} /* namespace term */
} /* namespace elision */

#endif /* STATICMAP_H_ */
