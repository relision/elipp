#ifndef CONTEXT_H_
#define CONTEXT_H_

/**
 * @file
 * Hold contextual information necessary during matching.
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
namespace term {
namespace basic {

/**
 * 
 */
class Context {
public:
	Context();
	virtual ~Context();
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* CONTEXT_H_ */
