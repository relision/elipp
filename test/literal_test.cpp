/**
 * @file
 * Perform testing on literals.
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

#include "test_frame.h"
#include "term/TermFactory.h"
#include "term/basic/TermFactoryImpl.h"
#include <boost/lexical_cast.hpp>

using namespace elision;
using namespace elision::term;

START_TEST

// Get a term factory.
HANG("Making a factory")
std::unique_ptr<TermFactory> fact(new elision::term::basic::TermFactoryImpl());
ENDL("Done")

START_ITEM(symbols)

try {
	// Make some symbols.
	HANG("Making symbols");
	pSymbolLiteral s1 = fact->get_symbol_literal("joe1");
	pSymbolLiteral s2 = fact->get_symbol_literal("1joe");
	pSymbolLiteral s3 = fact->get_symbol_literal(Loc::get_internal(), "");
	pSymbolLiteral s4 = fact->get_symbol_literal(Loc::get_internal(), "joe1");
	pSymbolLiteral s5 = fact->get_symbol_literal(Loc::get(17, 21), "^5`\n4\" \t");
	pSymbolLiteral s6 = fact->get_symbol_literal(Loc::get(21, 17), "joe1", fact->INTEGER);
	ENDL("Done");

	ENDL("Some symbols"); PUSH;
	SHOW_STRING(*s1);
	SHOW_STRING(*s2);
	SHOW_STRING(*s3);
	SHOW_STRING(*s4);
	SHOW_STRING(*s5);
	SHOW_STRING(*s6); POP;

	// Check values.
	ENDL("Checking stored values"); PUSH;
	VALIDATE(s1->get_name(), "joe1", "1");
	VALIDATE(s2->get_name(), "1joe", "2");
	VALIDATE(s3->get_name(), "", "3");
	VALIDATE(s4->get_name(), "joe1", "4");
	VALIDATE(s5->get_name(), "^5`\n4\" \t", "5");
	VALIDATE(s6->get_name(), "joe1", "6");
	POP;

	// Check strings.
	ENDL("Checking string cast"); PUSH;
	VALIDATE(std::string(*s1), "joe1: SYMBOL: ^ROOT", "1");
	VALIDATE(std::string(*s2), "`1joe`: SYMBOL: ^ROOT", "2");
	VALIDATE(std::string(*s3), "``: SYMBOL: ^ROOT", "3");
	VALIDATE(std::string(*s4), "joe1: SYMBOL: ^ROOT", "4");
	VALIDATE(std::string(*s5), "`^5\\`\\n4\\\" \\t`: SYMBOL: ^ROOT", "5");
	VALIDATE(std::string(*s6), "joe1: INTEGER: ^ROOT", "6");
	POP;

	// Check equality.  This shows that type information is used, but not
	// location.
	ENDL("Checking equality and inequality"); PUSH;
	MUST_EQUAL(*s1, *s4, "same");
	MUST_NOT_EQUAL(*s1, *s6, "different types");
	MUST_EQUAL(*s1, *s4, "different locus");
	MUST_NOT_EQUAL(*s1, *s6, "different types");
	MUST_NOT_EQUAL(*s1, *s5, "different values");
	POP;
} catch (std::exception& e) {
	// Failed!
	ENDL("Caught an exception: " << e.what());
	FAIL_ITEM(symbols, "");
}

END_ITEM(symbols)

START_ITEM(strings)

try {

} catch (std::exception& e) {
	// Failed!
	ENDL("Caught an exception: " << e.what());
	FAIL_ITEM(strings, "");
}

END_ITEM(strings)

START_ITEM(integers)

try {

} catch (std::exception& e) {
	// Failed!
	ENDL("Caught an exception: " << e.what());
	FAIL_ITEM(integers, "");
}

END_ITEM(integers)

START_ITEM(floats)

try {

} catch (std::exception& e) {
	// Failed!
	ENDL("Caught an exception: " << e.what());
	FAIL_ITEM(floats, "");
}

END_ITEM(floats)

START_ITEM(bitstrings)

try {

} catch (std::exception& e) {
	// Failed!
	ENDL("Caught an exception: " << e.what());
	FAIL_ITEM(bitstrings, "");
}

END_ITEM(bitstrings)

START_ITEM(booleans)

try {
	// Make some Booleans.
	HANG("Making Booleans");
	pBooleanLiteral b1 = fact->get_boolean_literal(Loc::get_internal(), true, fact->ROOT);
	pBooleanLiteral b2 = fact->get_boolean_literal(Loc::get_internal(), false, fact->ROOT);
	pBooleanLiteral b3 = fact->get_boolean_literal(Loc::get_internal(), true);
	pBooleanLiteral b4 = fact->get_boolean_literal(Loc::get_internal(), false, fact->BOOLEAN);
	pBooleanLiteral b5 = fact->get_boolean_literal(Loc::get(17,21), true, fact->BOOLEAN);
	pBooleanLiteral b6 = fact->get_boolean_literal(Loc::get(21,17), false);
	ENDL("Done");

	ENDL("Some Booleans"); PUSH;
	SHOW_STRING(*b1);
	SHOW_STRING(*b2);
	SHOW_STRING(*b3);
	SHOW_STRING(*b4);
	SHOW_STRING(*b5);
	SHOW_STRING(*b6);
	POP;

	// Check values.
	ENDL("Checking stored values"); PUSH;
	VALIDATE(b1->get_value(), true, "1");
	VALIDATE(b2->get_value(), false, "2");
	VALIDATE(b3->get_value(), true, "3");
	VALIDATE(b4->get_value(), false, "4");
	VALIDATE(b5->get_value(), true, "5");
	VALIDATE(b6->get_value(), false, "6");
	POP;

	// Location does not matter when comparing.
	ENDL("Checking equality and inequality"); PUSH;
	MUST_NOT_EQUAL(*b1, *b2, "different value");
	MUST_NOT_EQUAL(*b1, *b3, "different type");
	MUST_NOT_EQUAL(*b1, *b5, "different type");
	MUST_EQUAL(*b2, *b2, "self");
	MUST_EQUAL(*b3, *b5, "different locus");
	MUST_EQUAL(*b6, *b4, "different locus");
	MUST_NOT_EQUAL(*b4, *b3, "different value");
	POP;

	// Check the string values.
	ENDL("Checking string cast"); PUSH;
	VALIDATE(std::string(*b1), "true: ^ROOT", "1");
	VALIDATE(std::string(*b2), "false: ^ROOT", "2");
	VALIDATE(std::string(*b3), "true: BOOLEAN: ^ROOT", "3");
	VALIDATE(std::string(*b4), "false: BOOLEAN: ^ROOT", "4");
	VALIDATE(std::string(*b5), "true: BOOLEAN: ^ROOT", "5");
	VALIDATE(std::string(*b6), "false: BOOLEAN: ^ROOT", "6");
	POP;
} catch (std::exception& e) {
	// Failed!
	ENDL("Caught an exception: " << e.what());
	FAIL_ITEM(booleans, "");
}

END_ITEM(booleans)

END_TEST
