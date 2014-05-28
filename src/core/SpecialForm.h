#ifndef SPECIALFORM_H_
#define SPECIALFORM_H_

/**
 * @file
 * Define special forms.
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

/**
 * Define the structure of a special form.
 */
class SpecialForm : Term {
public:
	/// Get the tag.
	virtual Term const& get_tag() const = 0;

	/// Get the content.
	virtual Term const& get_content() const = 0;
};

} /* namespace term */
} /* namespace elision */

#endif /* SPECIALFORM_H_ */
