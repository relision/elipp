#ifndef PROPERTYSPECIFICATION_H_
#define PROPERTYSPECIFICATION_H_

/**
 * @file
 * Define a property specification.
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

#include "Term.h"
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
 *
 * @param loc Location of this specification.
 * @param associative Optional associativity. Default is none.
 * @param commutative Optional commutativity. Default is none.
 * @param idempotent Optional idempotency. Default is none.
 * @param absorber Optional absorber. Default is none.
 * @param identity Optional identity. Default is none.
 */
class PropertySpecification : Term {
public:
	/// Check associativity.
	virtual boost::optional<bool> const& is_associative() const = 0;

	/// Check commutativity.
	virtual boost::optional<bool> const& is_commutative() const = 0;

	/// Check idempotency.
	virtual boost::optional<bool> const& is_idempotent() const = 0;

	/// Get the absorber, if any.
	virtual boost::optional<Term> const& get_absorber() const = 0;

	/// Get the element specification, if any.
	virtual boost::optional<Term> const& get_elements() const = 0;

	/// Get the identity, if any.
	virtual boost::optional<Term> const& get_identity() const = 0;
};

} /* namespace term */
} /* namespace elision */

#endif /* PROPERTYSPECIFICATION_H_ */
