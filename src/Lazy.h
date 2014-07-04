#ifndef LAZY_H_
#define LAZY_H_

/**
 * @file
 * Provide the ability to store a lazily-computed value.
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

#include <functional>
#include <stdexcept>

#ifdef USE_BOOST_THREADS
#  include <boost/thread/shared_mutex.hpp>
#endif

namespace elision {

/**
 * Hold and defer computation of a value until it is explicitly requested.
 * This code is based on a suggestion from
 * [Konrad Rudolph](https://stackoverflow.com/users/1968/konrad-rudolph)
 * found in an answer to a question on
 * [stackoverflow](https://stackoverflow.com/questions/414243/lazy-evaluation-in-c).
 * 
 * To use this make an instance and pass the computation (or value).  This can
 * be a lambda.  The following is an example.
 *
 * ~~~{.cpp}
 * Lazy<std::string> val = [](){
 *   return x->to_string() + "." + y->to_string();
 * };
 * ~~~
 *
 * Here the string computational cost (and the space required by the string)
 * are not used until the string is required.  This can happen in three ways.
 *
 *   - Explicitly.  `std::string result = val.get();`
 *   - Implicitly by conversion.  `std::string result = val;`
 *   - Explicitly by dereference.  `std::string result = *val;`
 *
 * The result is a **reference** to the computed value, which remains held in
 * the instance until it is collected.
 *
 * These instances should be thread-safe.
 *
 * @param T	The type of the result.
 */
template<typename T>
class Lazy {
public:
	/**
	 * Make a new instance.  No computation is stored, so attempting to take
	 * the value of the resulting instance (before assigning to it, for
	 * example) results in a `runtime_error`.
	 */
	Lazy() : evaluator_([]()->T {
		throw std::runtime_error("Lazy value not set.");
	}), have_value_(false) {
		// Nothing to see here.
	}

	/**
	 * Make a new instance, but delay the computation.
	 * @param evaluator	The function that computes the lazy value.
	 */
	Lazy(std::function<T()> evaluator) :
		evaluator_(evaluator), have_value_(false) {
		// Nothing to do.
	}

	/**
	 * Explicitly provide a copy constructor.
	 * @param other	The other lazy value to copy.
	 */
	Lazy(Lazy<T> const& other) :
		evaluator_(other.evaluator_), have_value_(false) {
		// Nothing to do.
	}

	/**
	 * Permit non-lazy initialization.
	 * @param value	The non-lazy value to initialize this.
	 */
	Lazy(T value) : have_value_(true), value_(value) {
		// Nothing to do.
	}

	/// Deallocate this instance.
	virtual ~Lazy() = default;

	/**
	 * Get the value stored, and force its computation if necessary.
	 * @return	The stored value.
	 */
	T& get() {
		if (!have_value_) {
			evaluate();
		}
#ifdef USE_BOOST_THREADS
		boost::shared_lock<boost::shared_mutex> lock(evaluator_lock_);
#endif
		return value_;
	}

	/**
	 * Get the value stored, and force its computation if necessary.  This
	 * allows it to be used where the end type is expected - so it is
	 * computed implicitly.
	 * @return	The stored value.
	 */
	operator T() {
		return get();
	}

	/**
	 * Get the value stored, and force its computation if necessary.  This
	 * allows it to be used via the usual dereference - so it is computed
	 * implicitly.
	 * @return	The stored value.
	 */
	T& operator*() {
		return get();
	}

	/**
	 * Get the value stored, and force its computation if necessary.
	 * @return	The stored value.
	 */
	T& get() const {
		if (!have_value_) {
			evaluate();
		}
#ifdef USE_BOOST_THREADS
		boost::shared_lock<boost::shared_mutex> lock(evaluator_lock_);
#endif
		return value_;
	}

	/**
	 * Get the value stored, and force its computation if necessary.  This
	 * allows it to be used where the end type is expected - so it is
	 * computed implicitly.
	 * @return	The stored value.
	 */
	operator T() const {
		return get();
	}

	/**
	 * Get the value stored, and force its computation if necessary.  This
	 * allows it to be used via the usual dereference - so it is computed
	 * implicitly.
	 * @return	The stored value.
	 */
	T& operator*() const {
		return get();
	}

	/**
	 * Handle assignment to this lazy value.  This, combined with the
	 * no-argument constructor, allows for reasonable use of this as a
	 * object member.  The provided value is copied into this value, but
	 * no computation is performed, and the value remains lazy.
	 * @param	other	The other lazy value we are copying.
	 * @return	This instance.
	 */
	Lazy<T>& operator=(Lazy<T> const& other) {
#ifdef USE_BOOST_THREADS
		boost::shared_lock<boost::shared_mutex> lock(evaluator_lock_);
#endif
		evaluator_ = other.evaluator_;
		have_value_ = false;
		return *this;
	}

	/**
	 * Handle assignment to this lazy value.  This, combined with the
	 * no-argument constructor, allows for reasonable use of this as a
	 * object member.  The provided value is copied into this value, but
	 * no computation is performed, and the value remains lazy.
	 * @param	evaluator	A closure that generates the value.
	 * @return	This instance.
	 */
	Lazy<T>& operator=(std::function<T()> evaluator) {
#ifdef USE_BOOST_THREADS
		boost::shared_lock<boost::shared_mutex> lock(evaluator_lock_);
#endif
		evaluator_ = evaluator;
		have_value_ = false;
		return *this;
	}

	/**
	 * Allow assigning a non-lazy value.  This permits directly assigning the
	 * value when you have been forced to compute it by some other means.
	 * @param	value	The value.
	 * @return	This instance.
	 */
	Lazy<T>& operator=(T value) {
#ifdef USE_BOOST_THREADS
		boost::shared_lock<boost::shared_mutex> lock(evaluator_lock_);
#endif
		evaluator_ = []()->T {
			throw std::runtime_error("Lazy value not set.");
		};
		have_value_ = true;
		value_ = value;
		return *this;
	}

private:
	std::function<T()> evaluator_;
	mutable T value_;
	mutable bool have_value_;
#ifdef USE_BOOST_THREADS
	mutable boost::shared_mutex evaluator_lock_;
#endif

	void evaluate() const {
#ifdef USE_BOOST_THREADS
		boost::shared_lock<boost::shared_mutex> lock(evaluator_lock_);
#endif
		if (!have_value_) value_ = evaluator_();
		have_value_ = true;
	}
};

} /* namespace elision */

#endif /* LAZY_H_ */
