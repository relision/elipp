#ifndef PROPERTYSPECIFICATIONIMPL_H_
#define PROPERTYSPECIFICATIONIMPL_H_

/**
 * @file
 * Define the interface for an implementation of property specifications.
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

#include <basic/TermImpl.h>
#include <IPropertySpecification.h>
#include <Lazy.h>

namespace elision {
namespace term {
namespace basic {

/**
 * 
 */
class PropertySpecificationImpl: public IPropertySpecification, public TermImpl {
public:
	virtual ~PropertySpecificationImpl() = default;

	inline boost::optional<pTerm> get_associative() const {
		return associative_;
	}

	inline boost::optional<pTerm> get_commutative() const {
		return commutative_;
	}

	inline boost::optional<pTerm> get_idempotent() const {
		return idempotent_;
	}

	inline boost::optional<pTerm> get_absorber() const {
		return absorber_;
	}

	inline boost::optional<pTerm> get_identity() const {
		return identity_;
	}

	inline boost::optional<pTerm> get_membership() const {
		return elements_;
	}

	inline bool check_associative(bool def) const {
		if (associative_) {
			// The value is set.  Get it and see if it is a constant.
			pTerm value = associative_.get();
			if (value->is_true()) {
				return true;
			}
			if (value->is_false()) {
				return false;
			}
		}
		return def;
	}

	inline bool check_commutative(bool def) const {
		if (commutative_) {
			// The value is set.  Get it and see if it is a constant.
			pTerm value = commutative_.get();
			if (value->is_true()) {
				return true;
			}
			if (value->is_false()) {
				return false;
			}
		}
		return def;
	}

	inline bool check_idempotent(bool def) const {
		if (idempotent_) {
			// The value is set.  Get it and see if it is a constant.
			pTerm value = commutative_.get();
			if (value->is_true()) {
				return true;
			}
			if (value->is_false()) {
				return false;
			}
		}
		return def;
	}

	inline bool has_absorber() const {
		return absorber_.is_initialized();
	}

	inline bool has_identity() const {
		return identity_.is_initialized();
	}

	inline bool has_membership() const {
		return elements_.is_initialized();
	}

	inline bool is_constant() const {
		return constant_;
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<IPropertySpecification const*>(&other);
		return associative_ == oth->get_associative() &&
				commutative_ == oth->get_commutative() &&
				idempotent_ == oth->get_idempotent() &&
				absorber_ == oth->get_absorber() &&
				identity_ == oth->get_identity() &&
				elements_ == oth->get_membership();
	}

	inline std::string to_string() const {
		return strval_;
	}

	inline TermKind get_kind() const {
		return PROPERTY_SPECIFICATION_KIND;
	}

private:
	friend class PropertySpecificationBuilderImpl;
	PropertySpecificationImpl(Locus the_loc,
			boost::optional<pTerm> const& the_associative,
			boost::optional<pTerm> const& the_commutative,
			boost::optional<pTerm> const& the_idempotent,
			boost::optional<pTerm> const& the_absorber,
			boost::optional<pTerm> const& the_identity,
			boost::optional<pTerm> const& the_elements,
			pTerm the_type);
	boost::optional<pTerm> associative_;
	boost::optional<pTerm> commutative_;
	boost::optional<pTerm> idempotent_;
	boost::optional<pTerm> absorber_;
	boost::optional<pTerm> identity_;
	boost::optional<pTerm> elements_;
	Lazy<std::string> strval_;
	Lazy<bool> constant_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* PROPERTYSPECIFICATIONIMPL_H_ */
