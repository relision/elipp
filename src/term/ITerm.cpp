/**
 * @file
 * Common implementations.
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

namespace elision {
namespace term {

bool operator==(ITerm const& first, ITerm const& second) {
	// Check for simple equality.
	if (&first == &second) {
		return true;
	}

	// Check for simple inequality.
	if (typeid(first) != typeid(second)) {
		return false;
	}

	// Get pointers to the types.
	Term ftype = first.get_type();
	Term stype = second.get_type();
	if (ftype != stype) {
		// Watch out for the root term.
		if (ftype->is_root()) {
			if (!stype->is_root()) {
				// The types do not match.
				return false;
			}
		}
		// At least one type is not the root.
		if (*ftype != *stype) {
			// The types do not match.
			return false;
		}
	}

	// Now invoke the subclass method to determine the rest of the story.
	return first.is_equal(second);
}

bool operator!=(ITerm const& first, ITerm const& second) {
	return !operator==(first, second);
}

} /* namespace term */
} /* namespace elision */
