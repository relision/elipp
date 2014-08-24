#ifndef TERM_H_
#define TERM_H_

/**
 * @file
 * Provide simple implementations of common elements for all terms.
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

#include <cstdarg>
#include "term/ITerm.h"
#include "Lazy.h"

namespace elision {
namespace term {
namespace basic {

/**
 * Helper macro to return a pointer to a term formatted as type information
 * (with a leading colon), up to and including the root.  Use
 * `+WITH_TYPE(type_)` in most cases.
 */
#define WITH_TYPE(item_m) \
	(std::string(": ") + item_m->to_string())

/**
 * Partial implementation of a term.  This class is abstract; subclasses
 * must implement at least `is_constant` and the `std::string` operator.
 */
class TermImpl: public virtual elision::term::ITerm {
public:
	/**
	 * Initialize a new instance.  The location is "internal."
	 * @param the_type	The type of this term.
	 */
	explicit TermImpl(pTerm the_type);

	/**
	 * Initialize a new instance.
	 * @param the_loc	The location of the term's declaration.
	 * @param the_type	The type of this term.
	 */
	TermImpl(Locus the_loc, pTerm the_type);

	/// Deallocate this instance.
	virtual ~TermImpl() = default;

	/// Return the type used during construction.
	inline virtual pTerm get_type() const {
		return type_;
	}

	virtual std::string to_string() const = 0;

	/// Return the default of zero.  Override if you need to.
	inline virtual debruijn_type get_de_bruijn_index() const {
		return 0;
	}

	/// Subclasses must provide an implementation.
	inline depth_type get_depth() const {
		return depth_;
	}

	/// Return the default of false.  Override if you need to.
	inline virtual bool is_meta_term() const {
		return false;
	}

	/// Subclasses must provide an implementation.
	virtual bool is_constant() const = 0;

	/// Return the location provided during construction.
	inline virtual Locus get_loc() const {
		return loc_;
	}

	/// Return whether this is the unique root.  Default is NO.
	inline virtual bool is_root() const {
		return false;
	}

	/// Return whether this is the special true literal.  Default is NO.
	inline virtual bool is_true() const {
		return false;
	}

	/// Return whether this is the special false literal.  Default is NO.
	inline virtual bool is_false() const {
		return false;
	}

	/**
	 * Compare this instance to another instance of the same class.  To
	 * implement this make sure you first cast `other` to the correct class.
	 * If the derived class where the implementation lives is `B`, then do
	 * `dynamic_cast<B const&>(other)` and compare to `*this`.  Types have
	 * already been checked.
	 * @param other	The term to compare to.
	 * @return	True iff the two are equal.
	 */
	virtual bool is_equal(ITerm const& other) const = 0;

	inline size_t get_hash() const {
		return hash_;
	}

	inline size_t get_other_hash() const {
		return other_hash_;
	}

protected:
	pTerm type_;
	Locus loc_;
	Lazy<size_t> hash_;
	Lazy<size_t> other_hash_;
	Lazy<depth_type> depth_;
};

inline size_t hash_value(TermImpl const& term) {
	return term.get_hash();
}

/**
 * Combine the hashes of two terms into a single hash value.
 * @param seed	Initial hash value.
 * @param term	The term to combine.
 * @return	The computed hash value.
 */
size_t hash_combine(size_t seed, pTerm term);

/**
 * Combine the other hashes of two terms into a single hash value.
 * @param seed	Initial other hash value.
 * @param term	The term to combine.
 * @return	The computed other hash value.
 */
size_t other_hash_combine(size_t seed, pTerm term);

/**
 * Combine the hashes of two terms into a single hash value.
 * @param seed	Initial hash value.
 * @param term	The term to combine.
 * @return	The computed hash value.
 */
inline size_t hash_combine(pTerm seed, pTerm term) {
	return hash_combine(seed->get_hash(), term);
}

/**
 * Combine the other hashes of two terms into a single hash value.
 * @param seed	Initial other hash value.
 * @param term	The term to combine.
 * @return	The computed other hash value.
 */
inline size_t other_hash_combine(pTerm seed, pTerm term) {
	return other_hash_combine(seed->get_hash(), term);
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* TERM_H_ */
