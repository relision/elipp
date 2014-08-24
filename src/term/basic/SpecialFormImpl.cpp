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
	depth_ = [this]() {
		return std::max(get_type()->get_depth(),
				std::max(tag_->get_depth(), content_->get_depth())) + 1;
	};
	hash_ = [this]() {
		return hash_combine(hash_combine(tag_, content_), type_);
	};
	other_hash_ = [this]() {
		return other_hash_combine(other_hash_combine(type_, content_), tag_);
	};
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
