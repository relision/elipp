/**
 * @file
 * Provide an implementation of special forms.
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

#include <basic/SpecialFormImpl.h>

namespace elision {
namespace term {
namespace basic {

SpecialFormImpl::SpecialFormImpl(Locus the_loc, pTerm the_tag,
		pTerm the_content, pTerm the_type) : TermImpl(the_loc, the_type),
				tag_(the_tag), content_(the_content) {
	strval_ = [this]() {
		return "{: " + tag_->to_string() + " " + content_->to_string() + " :}";
	};
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
