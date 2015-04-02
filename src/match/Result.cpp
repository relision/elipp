/**
 * @file
 * Manage the results of a matching attempt.
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

#include <match/Result.h>

namespace elision {
namespace match {

Result::Result() {
	// TODO Auto-generated constructor stub
}

Result::~Result() {
	// TODO Auto-generated destructor stub
}

bool
Result::have_match() const {
	return false;
}

Result::const_iterator::const_iterator() {
}

Result::const_iterator
Result::begin() const {
	return *(new Result::const_iterator());
}

Result::const_iterator
Result::end() const {
	return *(new Result::const_iterator());
}


} /* namespace match */
} /* namespace elision */
