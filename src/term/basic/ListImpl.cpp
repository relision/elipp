/**
 * @file
 * Provide an implementation of a list.
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

#include <basic/ListImpl.h>

namespace elision {
namespace term {
namespace basic {

ListImpl::ListImpl(Locus the_loc, pPropertySpecification the_spec,
		std::vector<pTerm>& the_elements, pTerm the_type) :
			TermImpl(the_loc, the_type), properties_(the_spec),
			elements_(the_elements) {
	strval_ = [this]() {
		bool first = true;
		std::string res = properties_->to_string() + "(";
		for (auto i : elements_) {
			res += (first ? "" : ", ") + i.get()->to_string();
		} // Add all elements.
		return res + ")";
	};
	constant_ = [this]() {
		bool ret = true;
		for (auto i : elements_) {
			ret = ret && i.get()->is_constant();
		} // Iterate over contents.
		return ret;
	};
	depth_ = [this]() {
		unsigned int depth = the_type->get_depth();
		for (auto i : elements_) {
			depth = std::max(depth, i.get()->get_depth());
		} // Get the depth.
		return depth + 1;
	};
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
