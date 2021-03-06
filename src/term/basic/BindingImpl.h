#ifndef BINDINGIMPL_H_
#define BINDINGIMPL_H_

/**
 * @file
 * Provide a basic implementation of a binding.
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

#include "TermImpl.h"
#include "term/IBinding.h"
#include "term/ILambda.h"
#include "Lazy.h"
#include <memory>

namespace elision {
namespace term {
namespace basic {

using namespace elision;
using namespace elision::term;

class BindingImpl: public IBinding, public TermImpl {
public:
	virtual ~BindingImpl() = default;

	virtual std::shared_ptr<map_t> get_map() const;

	virtual pTerm get_bind(std::string const& name) const;

	virtual bool has_bind(std::string const& name) const;

	inline bool is_constant() const {
		return constant_;
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<IBinding const*>(&other);
		return *get_map() == *oth->get_map();
	}

	inline TermKind get_kind() const {
		return BINDING_KIND;
	}

	inline std::string to_string() const {
		return strval_;
	}

	inline bool operator<(ITerm const& other) const {
		if (get_kind() != other.get_kind()) {
			return get_kind() < other.get_kind();
		}
		auto oth = CAST(IBinding, other);
		// We have to compare all the items in the map.  This is complicated
		// by the fact that the maps may have different keys, and we have to
		// compare keys in a specific order.  So first we have to sort the
		// keys, and then compare the keys in lexicographic order.  Fortunately
		// this is how C++ stores its maps.  Hooray! (?)
		return *map_ < *(oth->get_map());
	}

private:
	friend class TermFactoryImpl;
	BindingImpl(Locus the_loc, map_t* map, pTerm type);
	std::shared_ptr<map_t> const map_;
	Lazy<std::string> strval_;
	Lazy<bool> constant_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* BINDINGIMPL_H_ */
