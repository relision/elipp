/**
 * @file
 * Provide an implementation of a binding atom.
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

#include "BindingImpl.h"

namespace elision {
namespace term {
namespace basic {

BindingImpl::BindingImpl(Locus loc, BindingImpl::map_t* map, pTerm type) :
		TermImpl(loc, type), map_(map) {
	strval_ = [this]() {
		std::string ret("{~ ");
		for (auto elt : *map_) {
			ret += escape(elt.first, true);
			ret += "->";
			ret += elt.second->to_string();
		} // Add all the binds.
		ret += " }";
		return ret;
	};
	bool is_constant = true;
	unsigned int depth = 0;
	size_t hash = 0;
	size_t other_hash = 1;
	for (auto entry : *map_) {
		is_constant = is_constant && entry.second->is_constant();
		depth = std::max(depth, entry.second->get_depth());
		hash = hash_combine(hash, entry.second);
		other_hash = hash_combine(other_hash, entry.second);
	} // Loop over all entries.
	constant_ = is_constant;
	hash_ = hash;
	other_hash_ = other_hash;
	depth_ = depth + 1;
}

std::shared_ptr<BindingImpl::map_t>
BindingImpl::get_map() const {
	return map_;
}

pTerm
BindingImpl::get_bind(std::string const& name) const {
	// Go and fetch the object related to this name.
	return map_->at(name);
}

bool
BindingImpl::has_bind(std::string const& name) const {
	try {
		map_->at(name);
		return true;
	} catch (std::out_of_range & e) {
		return false;
	}
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
