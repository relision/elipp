#ifndef RESULT_H_
#define RESULT_H_

/**
 * @file
 * Define the interface for retrieving matching results.
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

#include <term/IBinding.h>

namespace elision {
namespace match {


/**
 * Get the results of a match.  This class provides methods to check whether
 * there are any matches (`empty`) and to iterate over the matches
 * (`begin` and `end`).  Since the matches are generated on demand, there is
 * no way to get the count of matches //a priori//.
 */
class Result {
public:
	/// Deallocate this instance.
	virtual ~Result();

	/**
	 * Determine if there are any matches available.  If this returns true, then
	 * the iterator is guaranteed to return at least one match.
	 * @return	True if there are any matches.  False if there are not.
	 */
	virtual bool have_match() const;

	/**
	 * Determine if there are any matches available.  If this returns false,
	 * then the iterator is guaranteed to return at least one match.
	 * @return	False if there are any matches.  True if there are not.
	 */
	bool empty() const { return !have_match(); }

	/**
	 * The type for the returned matches.
	 */
	typedef elision::term::IBinding::map_t map_t;

	class const_iterator;

	/**
	 * Get an iterator pointing to the first match, if any.
	 * @return	An iterator.
	 */
	virtual const_iterator begin() const;

	/**
	 * Get an iterator pointing past the last match, if any.
	 * @return	An iterator.
	 */
	virtual const_iterator end() const;

	/**
	 * Implement an iterator over matches.
	 */
	class const_iterator : public std::iterator<std::forward_iterator_tag, map_t> {
	public:
		/**
		 * Make a new instance.
		 */
		const_iterator();
		const_iterator & operator++();
		const_iterator & operator++(int);
		map_t const& operator*() const;
		map_t const* operator->() const;
		bool operator==(const_iterator const& other) const;
		bool operator!=(const_iterator const& other) const {
			return !operator==(other);
		}

	private:
	};

private:
	friend class Matcher;
	Result();
};

} /* namespace match */
} /* namespace elision */

#endif /* RESULT_H_ */
