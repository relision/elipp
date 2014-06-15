/**
 * @file
 * Test the static map implementation.
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

START_ITEM(maps);

try {
	HANG("Making some static maps");
	pTerm d1 = fact->get_symbol_literal("fred");
	pTerm d2 = fact->get_string_literal("fred");
	pTerm d3 = fact->BOOLEAN;
	pTerm d4 = fact->INTEGER;
	pStaticMap m11 = fact->get_static_map(Loc::get_internal(), d1, d1);
	pStaticMap m12 = fact->get_static_map(Loc::get_internal(), d1, d2);
	pStaticMap m13 = fact->get_static_map(Loc::get_internal(), d1, d3);
	pStaticMap m14 = fact->get_static_map(Loc::get_internal(), d1, d4);
	pStaticMap m21 = fact->get_static_map(Loc::get_internal(), d2, d1);
	pStaticMap m22 = fact->get_static_map(Loc::get_internal(), d2, d2);
	pStaticMap m23 = fact->get_static_map(Loc::get_internal(), d2, d3);
	pStaticMap m24 = fact->get_static_map(Loc::get_internal(), d2, d4);
	pStaticMap m31 = fact->get_static_map(Loc::get_internal(), d3, d1);
	pStaticMap m32 = fact->get_static_map(Loc::get_internal(), d3, d2);
	pStaticMap m33 = fact->get_static_map(Loc::get_internal(), d3, d3);
	pStaticMap m34 = fact->get_static_map(Loc::get_internal(), d3, d4);
	pStaticMap m41 = fact->get_static_map(Loc::get_internal(), d4, d1);
	pStaticMap m42 = fact->get_static_map(Loc::get_internal(), d4, d2);
	pStaticMap m43 = fact->get_static_map(Loc::get_internal(), d4, d3);
	pStaticMap m44 = fact->get_static_map(Loc::get_internal(), d4, d4);
	ENDL("Done");

	ENDL("Some static maps"); PUSH;
	SHOW_STRING(*m11);
	SHOW_STRING(*m12);
	SHOW_STRING(*m13);
	SHOW_STRING(*m14);
	SHOW_STRING(*m21);
	SHOW_STRING(*m22);
	SHOW_STRING(*m23);
	SHOW_STRING(*m24);
	SHOW_STRING(*m31);
	SHOW_STRING(*m32);
	SHOW_STRING(*m33);
	SHOW_STRING(*m34);
	SHOW_STRING(*m41);
	SHOW_STRING(*m42);
	SHOW_STRING(*m43);
	SHOW_STRING(*m44);
	POP;

	ENDL("Checking strings"); PUSH;
	VALIDATE(std::string(*m11), "fred: SYMBOL: ^ROOT=>fred: SYMBOL: ^ROOT", "11");
	VALIDATE(std::string(*m12), "fred: SYMBOL: ^ROOT=>\"fred\": STRING: ^ROOT", "11");
	VALIDATE(std::string(*m13), "fred: SYMBOL: ^ROOT=>BOOLEAN: ^ROOT", "11");
	VALIDATE(std::string(*m14), "fred: SYMBOL: ^ROOT=>INTEGER: ^ROOT", "11");
	VALIDATE(std::string(*m21), "\"fred\": STRING: ^ROOT=>fred: SYMBOL: ^ROOT", "11");
	VALIDATE(std::string(*m22), "\"fred\": STRING: ^ROOT=>\"fred\": STRING: ^ROOT", "11");
	VALIDATE(std::string(*m23), "\"fred\": STRING: ^ROOT=>BOOLEAN: ^ROOT", "11");
	VALIDATE(std::string(*m24), "\"fred\": STRING: ^ROOT=>INTEGER: ^ROOT", "11");
	VALIDATE(std::string(*m31), "BOOLEAN: ^ROOT=>fred: SYMBOL: ^ROOT", "11");
	VALIDATE(std::string(*m32), "BOOLEAN: ^ROOT=>\"fred\": STRING: ^ROOT", "11");
	VALIDATE(std::string(*m33), "BOOLEAN: ^ROOT=>BOOLEAN: ^ROOT", "11");
	VALIDATE(std::string(*m34), "BOOLEAN: ^ROOT=>INTEGER: ^ROOT", "11");
	VALIDATE(std::string(*m41), "INTEGER: ^ROOT=>fred: SYMBOL: ^ROOT", "11");
	VALIDATE(std::string(*m42), "INTEGER: ^ROOT=>\"fred\": STRING: ^ROOT", "11");
	VALIDATE(std::string(*m43), "INTEGER: ^ROOT=>BOOLEAN: ^ROOT", "11");
	VALIDATE(std::string(*m44), "INTEGER: ^ROOT=>INTEGER: ^ROOT", "11");
	POP;

	ENDL("Testing equality and inequality"); PUSH;
	MUST_EQUAL(*m11, *m11, "same");
	MUST_NOT_EQUAL(*m11, *m12, "different codomain");
	MUST_NOT_EQUAL(*m11, *m21, "different domain");
	MUST_EQUAL(*m31, *m31, "same");
	MUST_NOT_EQUAL(*m34, *m33, "different codomain");
	MUST_NOT_EQUAL(*m34, *m44, "different domain");
	POP;
} catch (std::exception& e) {
	// Failed!
	ENDL("Caught an exception: " << e.what());
	FAIL_ITEM(maps, "");
}

END_ITEM(maps);

END_TEST
