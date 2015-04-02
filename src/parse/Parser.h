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

#include <vector>
#include "ElisionException.h"

namespace elision {
namespace parse {

class ParseException : public ElisionException {
public:
	ParseException(Locus loc, std::string const msg,
			ElisionException const& cause) :
				ElisionException(loc, msg, cause) {}
	ParseException(Locus loc, std::string const msg) :
				ElisionException(loc, msg) {}
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

	typedef wchar_t char_t;

	const int BLOCKSIZE = 4096;
	const char_t END = char_t(-1);

	char_t peek() const;
	std::vector<char_t> peek(int n);
	bool peek(std::wstring str);

	char_t consume();
	void consume(int n);
	void consume_whitespace();
	void peek_and_consume(std::wstring str);

	std::shared_ptr<Loc> loc() const;

	bool is_at_eof() const;

	void fail(std::string msg) {
		throw new ParseException(loc(), msg);
	}

private:
	bool at_eof_ = false;
	int this_line_ = 1;
	int this_column_ = 1;
	int lookcount_ = 0;
	int eofcount_ = 0;
	int block_ = 0;

	char_t look(int n) const;
	void read_other() const;
};

} /* namespace parse */
} /* namespace elision */

#endif /* PARSER_H_ */
