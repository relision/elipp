/**
 * @file
 * Provide method implementations for a term.
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

#include "TermImpl.h"

namespace elision {
namespace term {
namespace basic {

TermImpl::TermImpl(pTerm the_type) : type_(the_type), loc_(Loc::get_internal()) {
	NOTNULL(the_type);
}

size_t hash_combine(size_t seed1, size_t seed2) {
	size_t ret = seed1;
	ret ^= seed2 + 0x9e3779b9 + (ret << 6) + (ret >> 2);
	return ret;
}

size_t other_hash_combine(size_t seed1, size_t seed2) {
	size_t ret = seed1;
	ret ^= seed2 + 0x9b9773e9 + (ret << 7) + (ret >> 1);
	return ret;
}

TermImpl::TermImpl(Locus the_loc, pTerm the_type) :
	type_(the_type), loc_(the_loc) {
	NOTNULL(the_loc);
	NOTNULL(the_type);
}

size_t hash_combine(size_t seed, pTerm head) {
	return hash_combine(seed, head->get_hash());
}

size_t other_hash_combine(size_t seed, pTerm head) {
	return other_hash_combine(seed, head->get_other_hash());
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
