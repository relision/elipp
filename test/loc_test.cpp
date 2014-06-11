/**
 * @file
 * Test the use of the @code Loc data structure.
 *
 * @author ysp
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
 * Copyright (c) 2014 by Stacy Prowell (sprowell@gmail.com).
 * All rights reserved.
 * @endverbatim
 */

#include "test_frame.h"
#include "Loc.h"

START_TEST

START_ITEM(simple)
    namespace et = elision;
	try {
	    // Try the console location.
        HANG("Getting console")
        et::Locus console1 = et::Loc::get(17,21);
        et::Locus console2 = et::Loc::get(210,0);
        if (*console1 == *console2) {
            FAIL_ITEM(simple, "Unequal console locations show equal.");
        }
        // One way to get the string.  Get the underlying pointer, and then
        // dereference it so it can be converted.
        std::string consolestr = *(console1.get());
        ENDL(consolestr);
        if (consolestr != "(console):17:21") {
            FAIL_ITEM(simple, "Console string is incorrect.");
        }

        // Try the unique internal location.
	    HANG("Getting internal")
	    et::Locus internal1(et::Loc::get_internal());
	    et::Locus internal2(et::Loc::get_internal());
        et::Locus internal3 = et::Loc::get("");
        if (*internal1 != *internal2) {
            FAIL_ITEM(simple, "Internal locations via get_internal are not equal.");
        }
        if (*internal1 != *internal3) {
            FAIL_ITEM(simple, "Internal locations via constructor are not equal.");
        }
        // Another way to get the string.  Directly invoke the operator that
        // converts to a string.
	    std::string internalstr = internal1->operator std::string();
	    ENDL(internalstr);
	    if (internalstr != "") {
	        FAIL_ITEM(simple, "Internal string is incorrect.");
	    }

	    // Try a real location.
        HANG("Getting a location");
        et::Locus loc1 = et::Loc::get("test.eli", 17, 21);
        et::Locus loc2 = et::Loc::get("test.eli", 17, 21);
        et::Locus loc3 = et::Loc::get("test.eli", 210, 0);
        et::Locus loc4 = et::Loc::get("retest.eli", 210, 0);
        if (*loc1 != *loc2) {
            FAIL_ITEM(simple, "Equal locations show unequal.");
        }
        if (*loc1 == *loc3) {
            FAIL_ITEM(simple, "Unequal locations show equal (numbers).");
        }
        if (*loc3 == *loc4) {
            FAIL_ITEM(simple, "Unequal locations show equal (sources).");
        }
        std::string loc1str = *loc1;
        ENDL(loc1str);
        if (loc1str != "test.eli:17:21") {
            FAIL_ITEM(simple, "Location 1 test string is incorrect.");
        }
        SUCCESS;
	} catch (std::exception& e) {
		ENDL("Caught an exception: " << e.what ());
		FAIL_ITEM(simple, "");
	}
END_ITEM(simple)

END_TEST
