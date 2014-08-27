#ifndef PARSER_H_
#define PARSER_H_

/**
 * @file
 * Define an interface supporting creating recursive-descent parsers.
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

#include "ElisionException.h"

namespace elision {
namespace parse {

class ParseException : public ElisionException {
public:
	ParseException(Locus loc, std::string const& msg,
			ElisionException const& cause) :
				ElisionException(loc, msg, cause) {}
	virtual ~ParseException() = default;
};

/**
 * Provide a simple class to use for building recursive-descent parsers.
 * Just make an instance and then use the methods to process input.
 */
class Parser {
public:
	Parser();
	virtual ~Parser() = default;
};

} /* namespace parse */
} /* namespace elision */

#endif /* PARSER_H_ */
