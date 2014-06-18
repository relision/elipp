#ifndef ISPECIALFORM_H_
#define ISPECIALFORM_H_

/**
 * @file
 * Define the public interface to a special form.
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
 * Specify the public interface to a special form.  Special forms are really
 * just pairs that are subject to some "special" treatment by the system.  The
 * first element of the pair is called the @b tag, and the second element is
 * called the @b content, but really either can be any term you wish.
 */
class ISpecialForm : public virtual ITerm {
public:
	/**
	 * Get the tag for this special form.
	 * @return	The tag.
	 */
	virtual pTerm get_tag() const = 0;

	/**
	 * Get the content for this special form.
	 * @return	The content.
	 */
	virtual pTerm get_content() const = 0;
};

/// Shorthand for a property specification pointer.
typedef std::shared_ptr<ISpecialForm const> pSpecialForm;

} /* namespace term */
} /* namespace elision */

#endif /* ISPECIALFORM_H_ */
