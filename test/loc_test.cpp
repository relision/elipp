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
#include "Term.h"

START_TEST

START_ITEM(simple)
    namespace et = elision::term;
	try {
	    // Try the console location.
        HANG("Getting console")
        et::Loc const& console1 = et::Loc(17,21);
        et::Loc const& console2 = et::Loc(210,0);
        if (console1 == console2) {
            FAIL_ITEM(simple, "Unequal console locations show equal.");
        }
        std::string consolestr = console1;
        ENDL(consolestr);
        if (consolestr != "(console):17:21") {
            FAIL_ITEM(simple, "Console string is incorrect.");
        }

        // Try the unique internal location.
	    HANG("Getting internal")
	    et::Loc const& internal1 = et::Loc::get_internal();
        et::Loc const& internal2 = et::Loc::get_internal();
        et::Loc const& internal3 = et::Loc("");
        if (internal1 != internal2) {
            FAIL_ITEM(simple, "Internal locations via get_internal are not equal.");
        }
        if (internal1 != internal3) {
            FAIL_ITEM(simple, "Internal locations via constructor are not equal.");
        }
	    std::string internalstr = internal1;
	    ENDL(internalstr);
	    if (internalstr != "") {
	        FAIL_ITEM(simple, "Internal string is incorrect.");
	    }

	    // Try a real location.
        HANG("Getting a location");
        et::Loc const& loc1 = et::Loc("test.eli", 17, 21);
        et::Loc const& loc2 = et::Loc("test.eli", 17, 21);
        et::Loc const& loc3 = et::Loc("test.eli", 210, 0);
        et::Loc const& loc4 = et::Loc("retest.eli", 210, 0);
        if (loc1 != loc2) {
            FAIL_ITEM(simple, "Equal locations show unequal.");
        }
        if (loc1 == loc3) {
            FAIL_ITEM(simple, "Unequal locations show equal (numbers).");
        }
        if (loc3 == loc4) {
            FAIL_ITEM(simple, "Unequal locations show equal (sources).");
        }
        std::string loc1str = loc1;
        ENDL(loc1str);
        if (loc1str != "test.eli:17:21") {
            FAIL_ITEM(simple, "Location 1 test string is incorrect.");
        }
	} catch (std::exception& e) {
		FAIL_ITEM(simple, "");
		ENDL("Caught an exception: " << e.what ());
	}
END_ITEM(simple)

END_TEST
