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

#include "BasicTerm.h"
#include <cctype>

namespace elision {
namespace term {
namespace basic {

std::string const
escape(std::string const& original, bool is_symbol) {
	// Traverse the given string and quote those characters necessary.  If we
	// don't find any, then great!  If we do, then we surround the entire
	// result with single quotation marks.
	std::string result = "";
	bool quote = !is_symbol;
	for (char ch : original) {
		// See if the character needs an escape.
		switch (ch) {
		case '\0': result += "\\0";   quote = true; break;
		case '\a': result += "\\a";   quote = true; break;
		case '\b': result += "\\b";   quote = true; break;
		case '\t': result += "\\t";   quote = true; break;
		case '\n': result += "\\n";   quote = true; break;
		case '\v': result += "\\v";   quote = true; break;
		case '\f': result += "\\f";   quote = true; break;
		case '\r': result += "\\r";   quote = true; break;
		case '"':  result += "\\\"";  quote = true; break;
		case '\'': result += "\\'";   quote = true; break;
		case '?':  result += "\\?";   quote = true; break;
		case '\\': result += "\\\\";  quote = true; break;
		case '`':  result += "\\`";   quote = true; break;
		default:
			// Here is where handling of symbols and string diverges.  For a
			// symbol everything needs to be alphanumeric, but strings are
			// always quoted, so that isn't necessary.
			result += ch;
			if (is_symbol) {
				// Is the character is letter or digit?
				if (isalnum(ch) || ch == '_') {
					// Yes.  It's fine.
				} else {
					// No.  Result is something else.
					quote = true;
				}
			} // Is a symbol.
		} // Switch on character.
	} // Traverse the string.

	// Now if the first character is not a letter or underscore, then the whole
	// thing *still* has to be quoted, no matter what, if this is a symbol.
	if (is_symbol) {
		char ch = result[0];
		if (isalpha(ch) || ch == '_') {
			quote = true;
		}
	}

	// If necessary, quote the result.
	if (quote) {
		if (is_symbol) result = '`' + result + '`';
		else result = '"' + result + '"';
	}

	// Done!
	return result;
}

BasicTerm::BasicTerm(Loc const& loc, Term const& type) :
		loc_(loc), type_(type) {}

BasicTerm::operator
std::string() const {
	// Produce a warning that this term needs a string representation!
	return "UNK-TERM";
}

unsigned int
BasicTerm::get_de_bruijn_index() const {
	return 0;
}

unsigned int
BasicTerm::get_depth() const {
	return 1;
}

bool
BasicTerm::is_meta_term() const {
	return false;
}

bool
BasicTerm::is_constant() const {
	return true;
}

Loc const&
BasicTerm::get_loc() const {
	return loc_;
}

Term const&
BasicTerm::get_type() const {
	return type_;
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
