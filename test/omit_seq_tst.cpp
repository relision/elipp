/**
 * @file
 * Test working with omit sequences.
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
#include <Seq.h>

START_TEST

using namespace elision;

// Make several omit sequences.
auto v16 = std::vector<int>{1,2,3,4,5,6};
auto v00 = std::vector<int>{};
auto v35 = std::vector<int>{3,4,5};
auto v77 = std::vector<int>{7};
auto const os1 = Seq<int>(v16);
auto const os2 = Seq<int>(v00);
auto const os3 = Seq<int>(v35);
auto const os4 = Seq<int>(v77);

START_ITEM(build)

try {
	ENDL("Initialing with vectors:"); PUSH;
	for (auto here : v16) FLUSH(here << " "); ENDL("");
	for (auto here : v00) FLUSH(here << " "); ENDL("");
	for (auto here : v35) FLUSH(here << " "); ENDL("");
	for (auto here : v77) FLUSH(here << " "); ENDL("");
	POP;
	ENDL("Done");

	ENDL("Checking long for loop style"); PUSH;
	for (auto here = os1.begin(); here != os1.end(); here++) {
		FLUSH(*here << " ");
	}
	ENDL("");
	for (auto here = os2.begin(); here != os2.end(); here++) {
		FLUSH(*here << " ");
	}
	ENDL("");
	for (auto here = os3.begin(); here != os3.end(); here++) {
		FLUSH(*here << " ");
	}
	ENDL("");
	for (auto here = os4.begin(); here != os4.end(); here++) {
		FLUSH(*here << " ");
	}
	ENDL("");
	POP;
	ENDL("Done");

	ENDL("Checking short for loop style"); PUSH;
	for (auto here : os1) FLUSH(here << " "); ENDL("");
	for (auto here : os2) FLUSH(here << " "); ENDL("");
	for (auto here : os3) FLUSH(here << " "); ENDL("");
	for (auto here : os4) FLUSH(here << " "); ENDL("");
	POP;
	ENDL("Done");

	ENDL("Initializing via copy"); PUSH;
	auto os5 = os1;
	for (auto here : os5) FLUSH(here << " "); ENDL("");
	POP;
	ENDL("Done");

	ENDL("Initializing via iterator"); PUSH;
	auto os6 = Seq<int>(v16.begin(), v16.end());
	for (auto here : os6) FLUSH(here << " "); ENDL("");
	POP;
	ENDL("Done");
} catch (std::exception& e) {
	ENDL("Caught an exception: " << e.what());
	FAIL_ITEM(build, "");
}

END_ITEM(build)

START_ITEM(omit)

//try {
//	ENDL("Omitting second element"); PUSH;
//	auto s1 = os1.omit(1);
//	for (auto here : s1) FLUSH(here << " "); ENDL("");
//	MUST_THROW(os2.omit(1), std::range_error);
//	auto s3 = os3.omit(1);
//	for (auto here : s3) FLUSH(here << " "); ENDL("");
//	MUST_THROW(os4.omit(1), std::range_error);
//	POP;
//	ENDL("Done");
//} catch (std::exception& e) {
//	ENDL("Caught an exception: " << e.what());
//	FAIL_ITEM(omit, "");
//}

END_ITEM(omit)

START_ITEM(mix)

END_ITEM(mix)

END_TEST
