/**
 * @file
 * TODO: Describe purpose of file.
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

#include "ElisionException.h"

namespace elision {

ElisionException const&
ElisionException::get_cause() const {
	return cause_;
}

std::string const&
ElisionException::get_message() const {
	return message_;
}

bool
ElisionException::has_cause() const {
	return (&cause_ != this);
}

} /* namespace elision */
