#ifndef LISTIMPL_H_
#define LISTIMPL_H_

/**
 * @file
 * Define the interface for an implementation of list.
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

#include <Lazy.h>
#include <basic/TermImpl.h>
#include <IList.h>
#include <vector>

namespace elision {
namespace term {
namespace basic {

class ListImpl: public IList, public TermImpl {
public:
	virtual ~ListImpl() = default;

	inline pPropertySpecification get_property_specification() const {
		return properties_;
	}

	inline std::vector<pTerm> get_elements() const {
		return elements_;
	}

	inline pTerm operator[](size_t position) const {
		return elements_[position];
	}

	inline size_t size() const {
		return elements_.size();
	}

	inline bool is_constant() const {
		return constant_;
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<IList const*>(&other);
		return get_property_specification() ==
				oth->get_property_specification() &&
				get_elements() == oth->get_elements();
	}

	inline TermKind get_kind() const {
		return LIST;
	}

	virtual std::string to_string() const {
		return strval_;
	}

private:
	friend class TermFactoryImpl;
	ListImpl(Locus the_loc, pPropertySpecification the_spec,
			std::vector<pTerm>& the_elements, pTerm the_type);
	pPropertySpecification properties_;
	std::vector<pTerm> elements_;
	Lazy<std::string> strval_;
	Lazy<bool> constant_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* LISTIMPL_H_ */