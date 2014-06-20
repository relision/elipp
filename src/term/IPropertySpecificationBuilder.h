#ifndef IPROPERTYSPECIFICATIONBUILDER_H_
#define IPROPERTYSPECIFICATIONBUILDER_H_

/**
 * @file
 * Define the interface for a property specification builder.
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

#include <IPropertySpecification.h>

namespace elision {
namespace term {

/**
 * This is a class to construct property specifications.  These are complicated
 * objects that have many different components.
 */
class PropertySpecificationBuilder {
public:
	/// Deallocate this instance.
	virtual ~PropertySpecificationBuilder() = default;

	/**
	 * Complete the property specification and return the result.  The builder
	 * is reset at the end of this method, so it can be used to construct a new
	 * property specification.
	 *
	 * This method will throw a `logic_error` if the type of either the
	 * absorber or identity (if specified) does not match the membership
	 * type (if specified).  This can only be checked at this point, so be
	 * aware.
	 *
	 * @return	The new property specification.
	 * @throws	std::logic_error	The type of an absorber or identity does
	 * 			not match the type required by the membership specification.
	 */
	virtual pPropertySpecification get() = 0;

	/**
	 * Reset this property specification builder to the defaults.
	 * @return	This property specification builder.
	 */
	virtual PropertySpecificationBuilder * reset() = 0;

	/**
	 * Merge another property specification.  Anything that is specified in the
	 * provided spec overrides what is already specified in this builder.  That
	 * is, if associativity is set to true, and it is set to false in the
	 * provided spec, then the result it to set associativity to false.  If
	 * associativity is not specified in the provided spec, then it remains
	 * set to true.
	 * @param spec	The overriding specification.
	 * @return	This property specification builder.
	 */
	virtual PropertySpecificationBuilder * override(
			pPropertySpecification spec) = 0;

	/**
	 * Specify the associative property.  The provided term must have type
	 * `BOOLEAN`, or a `invalid_argument` is thrown.
	 * @param	value	The value for this property.
	 * @return	This property builder.
	 * @throws	std::invalid_argument	The type is not `BOOLEAN`.
	 */
	virtual PropertySpecificationBuilder * set_associative(pTerm value) = 0;

	/**
	 * Specify the associative property.
	 * @param	value	The value for this property.
	 * @return	This property builder.
	 */
	virtual PropertySpecificationBuilder * set_associative(bool value) = 0;

	/**
	 * Reset the associative property to unspecified.
	 * @return	This property builder.
	 */
	virtual PropertySpecificationBuilder * clear_associative() = 0;

	/**
	 * Explicitly set the associative property.  If the value is not
	 * initialized, the property is cleared.  If it is set, then the property
	 * is set.
	 *
	 * If the term is set, but its type is not `BOOLEAN`, then an
	 * `invalid_argument` exception is thrown.
	 *
	 * @param 	The value for the property.
	 * @return	This property builder.
	 * @throws	std::invalid_argument	The type is not `BOOLEAN`.
	 */
	virtual PropertySpecificationBuilder * set_associative(
			boost::optional<pTerm> value) = 0;

	/**
	 * Specify the commutative property.  The provided term must have type
	 * `BOOLEAN`, or a `invalid_argument` is thrown.
	 * @param	value	The value for this property.
	 * @return	This property builder.
	 * @throws	std::invalid_argument	The type is not `BOOLEAN`.
	 */
	virtual PropertySpecificationBuilder * set_commutative(pTerm value) = 0;

	/**
	 * Specify the commutative property.
	 * @param	value	The value for this property.
	 * @return	This property builder.
	 */
	virtual PropertySpecificationBuilder * set_commutative(bool value) = 0;

	/**
	 * Reset the commutative property to unspecified.
	 * @return	This property builder.
	 */
	virtual PropertySpecificationBuilder * clear_commutative() = 0;

	/**
	 * Explicitly set the commutative property.  If the value is not
	 * initialized, the property is cleared.  If it is set, then the property
	 * is set.
	 *
	 * If the term is set, but its type is not `BOOLEAN`, then an
	 * `invalid_argument` exception is thrown.
	 *
	 * @param 	The value for the property.
	 * @return	This property builder.
	 * @throws	std::invalid_argument	The type is not `BOOLEAN`.
	 */
	virtual PropertySpecificationBuilder * set_commutative(
			boost::optional<pTerm> value) = 0;

	/**
	 * Specify the idempotent property.  The provided term must have type
	 * `BOOLEAN`, or a `invalid_argument` is thrown.
	 * @param	value	The value for this property.
	 * @return	This property builder.
	 * @throws	std::invalid_argument	The type is not `BOOLEAN`.
	 */
	virtual PropertySpecificationBuilder * set_idempotent(pTerm value) = 0;

	/**
	 * Specify the idempotent property.
	 * @param	value	The value for this property.
	 * @return	This property builder.
	 */
	virtual PropertySpecificationBuilder * set_idempotent(bool value) = 0;

	/**
	 * Reset the idempotent property to unspecified.
	 * @return	This property builder.
	 */
	virtual PropertySpecificationBuilder * clear_idempotent() = 0;

	/**
	 * Explicitly set the idempotent property.  If the value is not
	 * initialized, the property is cleared.  If it is set, then the property
	 * is set.
	 *
	 * If the term is set, but its type is not `BOOLEAN`, then an
	 * `invalid_argument` exception is thrown.
	 *
	 * @param 	The value for the property.
	 * @return	This property builder.
	 * @throws	std::invalid_argument	The type is not `BOOLEAN`.
	 */
	virtual PropertySpecificationBuilder * set_idempotent(
			boost::optional<pTerm> value) = 0;

	/**
	 * Specify the absorber property.
	 * @param	value	The value for this property.
	 * @return	This property builder.
	 */
	virtual PropertySpecificationBuilder * set_absorber(pTerm value) = 0;

	/**
	 * Reset the absorber property to unspecified.
	 * @return	This property builder.
	 */
	virtual PropertySpecificationBuilder * clear_absorber() = 0;

	/**
	 * Explicitly set the absorber property.  If the value is not initialized,
	 * the property is cleared.  If it is set, then the property is set.
	 * @param 	The value for the property.
	 * @return	This property builder.
	 */
	virtual PropertySpecificationBuilder * set_absorber(
			boost::optional<pTerm> value) = 0;

	/**
	 * Specify the identity property.
	 * @param	value	The value for this property.
	 * @return	This property builder.
	 */
	virtual PropertySpecificationBuilder * set_identity(pTerm value) = 0;

	/**
	 * Reset the identity property to unspecified.
	 * @return	This property builder.
	 */
	virtual PropertySpecificationBuilder * clear_identity() = 0;

	/**
	 * Explicitly set the identity property.  If the value is not initialized,
	 * the property is cleared.  If it is set, then the property is set.
	 * @param 	The value for the property.
	 * @return	This property builder.
	 */
	virtual PropertySpecificationBuilder * set_identity(
			boost::optional<pTerm> value) = 0;

	/**
	 * Specify the membership property.
	 * @param	value	The value for this property.
	 * @return	This property builder.
	 */
	virtual PropertySpecificationBuilder * set_membership(pTerm value) = 0;

	/**
	 * Reset the membership property to unspecified.
	 * @return	This property builder.
	 */
	virtual PropertySpecificationBuilder * clear_membership() = 0;

	/**
	 * Explicitly set the membership property.  If the value is not
	 * initialized, the property is cleared.  If it is set, then the property
	 * is set.
	 * @param 	The value for the property.
	 * @return	This property builder.
	 */
	virtual PropertySpecificationBuilder * set_membership(
			boost::optional<pTerm> value) = 0;
};

} /* namespace term */
} /* namespace elision */

#endif /* IPROPERTYSPECIFICATIONBUILDER_H_ */
