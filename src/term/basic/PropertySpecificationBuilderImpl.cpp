/**
 * @file
 * Implement a property specification builder.
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

#include <basic/PropertySpecificationBuilderImpl.h>
#include <basic/PropertySpecificationImpl.h>

namespace elision {
namespace term {
namespace basic {

PropertySpecificationBuilderImpl::PropertySpecificationBuilderImpl(
		pTerm TRUE, pTerm FALSE, pTerm type) : TRUE_(TRUE), FALSE_(FALSE),
				type_(type) {
	// Nothing else to do.
}

pPropertySpecification
PropertySpecificationBuilderImpl::get() {
	auto ret = new PropertySpecificationImpl(loc_, associative_, commutative_,
			idempotent_, absorber_, identity_, elements_, type_);
	reset();
	return std::shared_ptr<IPropertySpecification const>(ret);
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::reset() {
	loc_ = Loc::get_internal();
	associative_ = boost::none;
	commutative_ = boost::none;
	idempotent_ = boost::none;
	absorber_ = boost::none;
	identity_ = boost::none;
	elements_ = boost::none;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_loc(Locus loc) {
	loc_ = loc;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_associative(pTerm value) {
	associative_ = value;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_associative(bool value) {
	associative_ = value ? TRUE_ : FALSE_;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::clear_associative() {
	associative_ = boost::none;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_associative(
		boost::optional<pTerm> value) {
	associative_ = value;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_commutative(pTerm value) {
	commutative_ = value;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_commutative(bool value) {
	commutative_ = value ? TRUE_ : FALSE_;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::clear_commutative() {
	commutative_ = boost::none;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_commutative(
		boost::optional<pTerm> value) {
	commutative_ = value;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_idempotent(pTerm value) {
	idempotent_ = value;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_idempotent(bool value) {
	idempotent_ = value ? TRUE_ : FALSE_;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::clear_idempotent() {
	idempotent_ = boost::none;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_idempotent(
		boost::optional<pTerm> value) {
	idempotent_ = value;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_absorber(pTerm value) {
	absorber_ = value;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::clear_absorber() {
	absorber_ = boost::none;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_absorber(
		boost::optional<pTerm> value) {
	absorber_ = value;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_identity(pTerm value) {
	identity_ = value;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::clear_identity() {
	identity_ = boost::none;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_identity(
		boost::optional<pTerm> value) {
	identity_ = value;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_membership(pTerm value) {
	elements_ = value;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::clear_membership() {
	elements_ = boost::none;
	return this;
}

PropertySpecificationBuilder *
PropertySpecificationBuilderImpl::set_membership(
		boost::optional<pTerm> value) {
	elements_ = value;
	return this;
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
