#ifndef TERMMODIFIER_H_
#define TERMMODIFIER_H_

/**
 * @file
 * TODO: Describe purpose of file.
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
#include "TermFactory.h"
#include <functional>

namespace elision {
namespace term {
namespace basic {

/**
 * Provide methods to modify a term based on a replacement map.
 *
 * Once constructed this class can be reused as much as you want, since all
 * methods are marked `const`.
 */
class TermModifier {
public:
	/**
	 * Make a new instance.  Because we may need to construct new terms, this
	 * requires a term factory instance it can use.
	 * @param fact	The term factory.
	 */
	TermModifier(std::shared_ptr<TermFactory> fact);

	/// Deallocate this instance.
	virtual ~TermModifier() = default;

	/**
	 * Perform simple substitution of variables for their replacements.  This
	 * method is intended for performance when rewriting terms based on binds
	 * returned by matching.  Variable guards in the target are ignored.
	 *
	 * @param map		The binds.
	 * @param target	The term to rewrite.
	 * @return	The possibly-new term.  If the term is not modified, then the
	 * 			same input pointer is returned.
	 */
	pTerm substitute(std::unordered_map<std::string, pTerm> const& map,
			pTerm target) const;

	/**
	 * Perform general rebuilding of a term based on a provided closure.  This
	 * traverses the term and applies the closure to each sub-term.  The closure
	 * may return a new term and if it does, the sub-term is replaced and the
	 * entire term rebuilt.  This can be quite costly, depending on the
	 * closure being computed.
	 *
	 * If a closure returns a different term, then that term is not explored
	 * any further, as doing so could lead to madness.  This method visits the
	 * provided term first, then the type, then the children, recursively.  The
	 * closure only need to worry about the specific term it receives.
	 *
	 * @param target	The term to rebuild.
	 * @param closure	The closure to perform rebuilding.
	 * @return	The possibly-new term.  If the term is not modified, then the
	 * 			same input pointer is returned.
	 */
	pTerm rebuild(pTerm target, std::function<pTerm (pTerm)> closure) const;

private:
	std::shared_ptr<TermFactory const> fact_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* TERMMODIFIER_H_ */
