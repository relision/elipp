#ifndef IPROPERTYSPECIFICATION_H_
#define IPROPERTYSPECIFICATION_H_

/**
 * @file
 * Define the public interface to a property specification.
 *
 * @author sprowell@gmail.com
 *
 * @section LICENSE
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

#include "ITerm.h"
#include <boost/optional.hpp>

namespace elision {
namespace term {

/**
 * A property specification was incorrect in some manner.  This typically
 * indicates that a bad value was specified for a property (setting a Boolean
 * property to a non-Boolean, for example) or that properties are being used
 * inconsistently (requiring idempotency but not associativity).
 */
class IllegalPropertySpecification : ElisionException {};

/**
 * Encapsulate the algebraic properties ascribed to some object.
 *
 * # Properties
 * The following properties are supported.
 * - ''Associativity'' implies that children can be arbitrarily grouped.
 *   For example, string concatenation is associative.
 * - ''Commutativity'' implies that children can be arbitrarily ordered.
 *   For example, multiplication is commutative.
 * - ''Idempotency'' implies that repeated children are ignored. For
 *   example, Boolean '''or''' is idempotent.
 * - An ''absorber'' is a special atom ''A'' that, when added to the children,
 *   causes the result to evaluate to simply ''A''. Zero is a multiplicative
 *   absorber.
 * - An ''identity'' is a special atom ''I'' that can be introduced or
 *   omitted from the child list without changing the value. Zero is the
 *   additive identity.
 *
 * # Restrictions
 * Some properties require others. At present idempotency requires
 * associativity. If an absorber or identity is present, associativity is
 * also required.
 *
 * Properties can be specified, or left unspecified. The entire properties
 * object can be matched and rewritten.
 *
 * Instances are applicable; applied to a typed list of atoms, they "overwrite"
 * the lists properties.
 */
class IPropertySpecification : public virtual ITerm {
public:
	/**
	 * Get any associativity specification.
	 * @return	The associativity specification.
	 */
	virtual boost::optional<bool> const get_associative() const = 0;

	/**
	 * Get any commutativity specification.
	 * @return	The commutativity specification.
	 */
	virtual boost::optional<bool> const get_commutative() const = 0;

	/**
	 * Get any idempotency specification.
	 * @return	The idempotency specification.
	 */
	virtual boost::optional<bool> const get_idempotent() const = 0;

	/**
	 * Get any absorber specification.
	 * @return	The absorber specification.
	 */
	virtual boost::optional<pTerm> get_absorber() const = 0;

	/**
	 * Get any identity specification.
	 * @return	The identity specification.
	 */
	virtual boost::optional<pTerm> get_identity() const = 0;

	/**
	 * Get any membership specification.
	 * @return	The membership specification.
	 */
	virtual boost::optional<pTerm> get_membership() const = 0;

	/**
	 * Check the associativity specification.  If it is set to a Boolean
	 * constant, return it.  If it is not, return the default.
	 * @return	The associativity, or the provided default.
	 */
	virtual bool check_associative(bool def) const = 0;

	/**
	 * Check the commutativity specification.  If it is set to a Boolean
	 * constant, return it.  If it is not, return the default.
	 * @return	The associativity, or the provided default.
	 */
	virtual bool check_commutative(bool def) const = 0;

	/**
	 * Check the idempotency specification.  If it is set to a Boolean
	 * constant, return it.  If it is not, return the default.
	 * @return	The associativity, or the provided default.
	 */
	virtual bool check_identity(bool def) const = 0;

	/**
	 * Determine if an absorber is specified.
	 * @return	True if an absorber is specified, and false otherwise.
	 */
	virtual bool const has_absorber() const = 0;

	/**
	 * Determine if an identity is specified.
	 * @return	True if an identity is specified, and false otherwise.
	 */
	virtual bool const has_identity() const = 0;

	/**
	 * Determine if membership is specified.
	 * @return	True if membership is specified, and false otherwise.
	 */
	virtual bool const has_membership() const = 0;
};

/// Shorthand for a property specification pointer.
typedef std::shared_ptr<IPropertySpecification const> PropertySpecification;

} /* namespace term */
} /* namespace elision */

#endif /* IPROPERTYSPECIFICATION_H_ */
