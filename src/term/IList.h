#ifndef ILIST_H_
#define ILIST_H_

/**
 * @file
 * Define the public interface to a list.
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

#include "ITerm.h"
#include "IPropertySpecification.h"

namespace elision {
namespace term {

/**
 * A list consists of a collection of terms and an algebraic property
 * specification.
 */
class IList : public virtual ITerm {
public:
	/**
	 * Get the property specification for this list.
	 * @return	The property specification for this list.
	 */
	virtual pPropertySpecification get_property_specification() const = 0;

	/**
	 * Get an element from this list, by apparent position.
	 * @param position	The zero-based position.
	 * @return	The requested element.
	 * @throws	std::out_of_range	If the position is out of range.
	 */
	virtual pTerm operator[](unsigned int position) const = 0;

	/**
	 * Get the length of this list (the number of elements).
	 * @return	The length of the list.
	 */
	virtual unsigned int get_length() const = 0;
};

/// Shorthand for a list pointer.
typedef std::shared_ptr<IList const> pList;

} /* namespace term */
} /* namespace elision */

#endif /* ILIST_H_ */
