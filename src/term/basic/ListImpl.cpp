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
	bool constant = true;
	unsigned int depth = std::max(the_type->get_depth(), the_spec->get_depth());
	size_t hash = hash_combine(the_type, the_spec);
	size_t other_hash = hash_combine(the_type, the_spec);
	for (auto elt : elements_) {
		constant = constant && elt.get()->is_constant();
		depth = std::max(depth, elt.get()->get_depth());
		hash = hash_combine(hash, elt);
		other_hash = other_hash_combine(other_hash, elt);
	} // Iterate over contents.
	constant_ = constant;
	depth_ = depth;
	hash_ = hash;
	other_hash_ = other_hash;
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
