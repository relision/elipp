#ifndef LIST_H_
#define LIST_H_

/**
 * @file
 * Define lists.
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

namespace elision {
namespace term {

/**
 * A list consists of a collection of terms and an algebraic property
 * specification.
 */
class List : Term {
public:
	/// Get the algebraic property specification.
	virtual PropertySpecification const& get_property_specification() const = 0;

	/**
	 * Get an element from this list, by apparent position.
	 * @param position	The zero-based position.
	 * @return	The requested element.
	 * @throws	std::out_of_range	If the position is out of range.
	 */
	virtual Term const& operator[](unsigned int position) const = 0;

	/// Get the length of this list (the number of elements).
	virtual unsigned int get_length() const = 0;
};

} /* namespace term */
} /* namespace elision */

#endif /* LIST_H_ */
