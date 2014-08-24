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

#include "BindingImpl.h"
#include <unordered_map>

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
	constant_ = [this]() {
		bool ret = true;
		for (auto entry : *map_) {
			ret = ret && entry.second->is_constant();
		} // Check constancy over all pairs.
		return ret;
	};
	depth_ = [this, type]() {
		unsigned int depth = type->get_depth();
		for (auto elt : *map_) {
			depth = std::max(depth, elt.second->get_depth());
		} // Find deepest element.
		return depth + 1;
	};
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
