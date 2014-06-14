/**
 * @file
 * Perform testing on literals.
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

#include "test_frame.h"
#include "term/TermFactory.h"
#include "term/basic/TermFactoryImpl.h"
#include <boost/lexical_cast.hpp>

using namespace elision;
using namespace elision::term;

START_TEST

// Get a term factory.
HANG("Making a factory");
std::unique_ptr<TermFactory> fact(new elision::term::basic::TermFactoryImpl());
ENDL("Done");

START_ITEM(symbols)

try {
	// Make some symbols.
	HANG("Making symbols");
	pSymbolLiteral s1 = fact->get_symbol_literal("joe1");
	pSymbolLiteral s2 = fact->get_symbol_literal("1joe");
	pSymbolLiteral s3 = fact->get_symbol_literal(Loc::get_internal(), "");
	pSymbolLiteral s4 = fact->get_symbol_literal(Loc::get_internal(), "joe1");
	pSymbolLiteral s5 = fact->get_symbol_literal(Loc::get(17, 21),
			"^5`\n4\" \t");
	pSymbolLiteral s6 = fact->get_symbol_literal(Loc::get(21, 17), "joe1",
			fact->INTEGER);
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
	HANG("Making some strings");
	pStringLiteral s1 = fact->get_string_literal("fred");
	pStringLiteral s2 = fact->get_string_literal(Loc::get(17,21), "fred");
	pStringLiteral s3 = fact->get_string_literal(Loc::get(21,17), "fred");
	pStringLiteral s4 = fact->get_string_literal(Loc::get_internal(), "fred",
			fact->SYMBOL);
	pStringLiteral s5 = fact->get_string_literal(Loc::get_internal(), "fred",
			fact->SYMBOL);
	pStringLiteral s6 = fact->get_string_literal(Loc::get(17,21), "fred",
			fact->SYMBOL);
	pStringLiteral s7 = fact->get_string_literal("");
	pStringLiteral s8 = fact->get_string_literal("\n \t\\*\"'");
	pStringLiteral s9 = fact->get_string_literal(Loc::get_internal(),
			"\n \t\\*\"'", fact->SYMBOL);
	ENDL("Done");

	ENDL("Some strings"); PUSH;
	SHOW_STRING(*s1);
	SHOW_STRING(*s2);
	SHOW_STRING(*s3);
	SHOW_STRING(*s4);
	SHOW_STRING(*s5);
	SHOW_STRING(*s6);
	SHOW_STRING(*s7);
	SHOW_STRING(*s8);
	SHOW_STRING(*s9);
	POP;

	ENDL("Checking values"); PUSH;
	VALIDATE(s1->get_value(), "fred", "1");
	VALIDATE(s2->get_value(), "fred", "2");
	VALIDATE(s3->get_value(), "fred", "3");
	VALIDATE(s4->get_value(), "fred", "4");
	VALIDATE(s5->get_value(), "fred", "5");
	VALIDATE(s6->get_value(), "fred", "6");
	VALIDATE(s7->get_value(), "", "7");
	VALIDATE(s8->get_value(), "\n \t\\*\"'", "8");
	VALIDATE(s9->get_value(), "\n \t\\*\"'", "9");
	POP;

	ENDL("Checking strings"); PUSH;
	VALIDATE(std::string(*s1), "\"fred\": STRING: ^ROOT", "1");
	VALIDATE(std::string(*s2), "\"fred\": STRING: ^ROOT", "2");
	VALIDATE(std::string(*s3), "\"fred\": STRING: ^ROOT", "3");
	VALIDATE(std::string(*s4), "\"fred\": SYMBOL: ^ROOT", "4");
	VALIDATE(std::string(*s5), "\"fred\": SYMBOL: ^ROOT", "5");
	VALIDATE(std::string(*s6), "\"fred\": SYMBOL: ^ROOT", "6");
	VALIDATE(std::string(*s7), "\"\": STRING: ^ROOT", "7");
	VALIDATE(std::string(*s8), "\"\\n \\t\\\\*\\\"\\'\": STRING: ^ROOT", "8");
	VALIDATE(std::string(*s9), "\"\\n \\t\\\\*\\\"\\'\": SYMBOL: ^ROOT", "9");
	POP;

	ENDL("Checking equality and inequality"); PUSH;
	MUST_EQUAL(*s1, *s2, "different locus");
	MUST_NOT_EQUAL(*s1, *s4, "different types");
	MUST_EQUAL(*s2, *s3, "different locus");
	MUST_NOT_EQUAL(*s4, *s3, "different types");
	MUST_EQUAL(*s4, *s6, "different locus");
	MUST_NOT_EQUAL(*s8, *s9, "different type");
	MUST_NOT_EQUAL(*s7, *s1, "different values");
	MUST_NOT_EQUAL(*s8, *s7, "different values");
	POP;
} catch (std::exception& e) {
	// Failed!
	ENDL("Caught an exception: " << e.what());
	POP;
	FAIL_ITEM(strings, "");
}

END_ITEM(strings)

START_ITEM(integers)

try {
	HANG("Making some integers");
	pIntegerLiteral i1 = fact->get_integer_literal(0);
	pIntegerLiteral i2 = fact->get_integer_literal(-1);
	pIntegerLiteral i3 = fact->get_integer_literal(65535);
	pIntegerLiteral i4 = fact->get_integer_literal(65536);
	eint_t value = 666;
	value *= 1024;
	value *= 4096;
#ifdef HAVE_BOOST_CPP_INT
	value *= 16384;
	value *= 32768;
	value *= 8191;
#endif
	pIntegerLiteral i5 = fact->get_integer_literal(Loc::get_internal(), value, fact->FLOAT);
	pIntegerLiteral i6 = fact->get_integer_literal(Loc::get(17, 21), value);
	pIntegerLiteral i7 = fact->get_integer_literal(Loc::get_internal(), -value, fact->FLOAT);
	pIntegerLiteral i8 = fact->get_integer_literal(Loc::get(21, 17), -value);
	pIntegerLiteral i9 = fact->get_integer_literal(value);
	pIntegerLiteral i10 = fact->get_integer_literal(-value);
	ENDL("Done");

	ENDL("Some integers"); PUSH;
	SHOW_STRING(*i1);
	SHOW_STRING(*i2);
	SHOW_STRING(*i3);
	SHOW_STRING(*i4);
	SHOW_STRING(*i5);
	SHOW_STRING(*i6);
	SHOW_STRING(*i7);
	SHOW_STRING(*i8);
	SHOW_STRING(*i9);
	SHOW_STRING(*i10);
	POP;

	ENDL("Checking values"); PUSH;
	VALIDATE(i1->get_value(), 0, "1");
	VALIDATE(i2->get_value(), -1, "2");
	VALIDATE(i3->get_value(), 65535, "3");
	VALIDATE(i4->get_value(), 65536, "4");
	VALIDATE(i5->get_value(), value, "5");
	VALIDATE(i6->get_value(), value, "6");
	VALIDATE(i7->get_value(), -value, "7");
	VALIDATE(i8->get_value(), -value, "8");
	VALIDATE(i9->get_value(), value, "9");
	VALIDATE(i10->get_value(), -value, "10");
	POP;

	ENDL("Checking strings"); PUSH;
	VALIDATE(std::string(*i1), "0: INTEGER: ^ROOT", "1");
	VALIDATE(std::string(*i2), "-1: INTEGER: ^ROOT", "2");
	VALIDATE(std::string(*i3), "65535: INTEGER: ^ROOT", "3");
	VALIDATE(std::string(*i4), "65536: INTEGER: ^ROOT", "4");
	VALIDATE(std::string(*i5), boost::lexical_cast<std::string>(value) +
			": FLOAT: ^ROOT", "5");
	VALIDATE(std::string(*i6), boost::lexical_cast<std::string>(value) +
			": INTEGER: ^ROOT", "6");
	VALIDATE(std::string(*i7), boost::lexical_cast<std::string>(-value) +
			": FLOAT: ^ROOT", "7");
	VALIDATE(std::string(*i8), boost::lexical_cast<std::string>(-value) +
			": INTEGER: ^ROOT", "8");
	VALIDATE(std::string(*i9), boost::lexical_cast<std::string>(value) +
			": INTEGER: ^ROOT", "9");
	VALIDATE(std::string(*i10), boost::lexical_cast<std::string>(-value) +
			": INTEGER: ^ROOT", "10");
	POP;

	ENDL("Checking equality and inequality"); PUSH;
	MUST_EQUAL(*i5, *i5, "same object");
	MUST_EQUAL(*i6, *i9, "different locus");
	MUST_EQUAL(*i8, *i10, "different locus");
	MUST_NOT_EQUAL(*i1, *i2, "different values");
	MUST_NOT_EQUAL(*i2, *i3, "different values");
	MUST_NOT_EQUAL(*i3, *i4, "different values");
	MUST_NOT_EQUAL(*i5, *i6, "different types");
	MUST_NOT_EQUAL(*i7, *i8, "different types");
	POP;
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
	pBooleanLiteral b1 = fact->get_boolean_literal(Loc::get_internal(), true,
			fact->ROOT);
	pBooleanLiteral b2 = fact->get_boolean_literal(Loc::get_internal(), false,
			fact->ROOT);
	pBooleanLiteral b3 = fact->get_boolean_literal(Loc::get_internal(), true);
	pBooleanLiteral b4 = fact->get_boolean_literal(Loc::get_internal(), false,
			fact->BOOLEAN);
	pBooleanLiteral b5 = fact->get_boolean_literal(Loc::get(17,21), true,
			fact->BOOLEAN);
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
