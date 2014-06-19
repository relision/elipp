#ifndef PROPERTYSPECIFICATIONBUILDERIMPL_H_
#define PROPERTYSPECIFICATIONBUILDERIMPL_H_

/**
 * @file
 * Define the property specification builder implementation.
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

#include <IPropertySpecificationBuilder.h>

namespace elision {
namespace term {
namespace basic {

class PropertySpecificationBuilderImpl: public elision::term::PropertySpecificationBuilder {
public:
	/// Deallocate this instance.
	virtual ~PropertySpecificationBuilderImpl() = default;

	virtual pPropertySpecification get();
	virtual PropertySpecificationBuilder * reset();

	virtual PropertySpecificationBuilder * set_loc(Locus loc);

	virtual PropertySpecificationBuilder * set_associative(pTerm value);
	virtual PropertySpecificationBuilder * set_associative(bool value);
	virtual PropertySpecificationBuilder * clear_associative();
	virtual PropertySpecificationBuilder * set_associative(
			boost::optional<pTerm> value);

	virtual PropertySpecificationBuilder * set_commutative(pTerm value);
	virtual PropertySpecificationBuilder * set_commutative(bool value);
	virtual PropertySpecificationBuilder * clear_commutative();
	virtual PropertySpecificationBuilder * set_commutative(
			boost::optional<pTerm> value);

	virtual PropertySpecificationBuilder * set_idempotent(pTerm value);
	virtual PropertySpecificationBuilder * set_idempotent(bool value);
	virtual PropertySpecificationBuilder * clear_idempotent();
	virtual PropertySpecificationBuilder * set_idempotent(
			boost::optional<pTerm> value);

	virtual PropertySpecificationBuilder * set_absorber(pTerm value);
	virtual PropertySpecificationBuilder * clear_absorber();
	virtual PropertySpecificationBuilder * set_absorber(
			boost::optional<pTerm> value);

	virtual PropertySpecificationBuilder * set_identity(pTerm value);
	virtual PropertySpecificationBuilder * clear_identity();
	virtual PropertySpecificationBuilder * set_identity(
			boost::optional<pTerm> value);

	virtual PropertySpecificationBuilder * set_membership(pTerm value);
	virtual PropertySpecificationBuilder * clear_membership();
	virtual PropertySpecificationBuilder * set_membership(
			boost::optional<pTerm> value);

private:
	friend class TermFactoryImpl;
	/**
	 * Make a new instance.  The true and false values muse be specified so
	 * that this class can turn simple Boolean values into terms without
	 * needing access to a term factory.
	 *
	 * @param TRUE	The true value.
	 * @param FALSE	The false value.
	 * @param type	The type to use for property specifications.
	 */
	PropertySpecificationBuilderImpl(pTerm TRUE, pTerm FALSE, pTerm type);

	pTerm TRUE_;
	pTerm FALSE_;
	boost::optional<pTerm> associative_;
	boost::optional<pTerm> commutative_;
	boost::optional<pTerm> idempotent_;
	boost::optional<pTerm> absorber_;
	boost::optional<pTerm> identity_;
	boost::optional<pTerm> elements_;
	Locus loc_ = Loc::get_internal();
	pTerm type_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* PROPERTYSPECIFICATIONBUILDERIMPL_H_ */
