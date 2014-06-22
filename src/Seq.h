#ifndef SEQ_H_
#define SEQ_H_

/**
 * @file
 * TODO: Describe purpose of file.
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

#include <vector>
#include <cstddef>

#define D(msg_m) std::cout << msg_m << std::flush;
#define P(msg_m) std::cout << msg_m << std::flush << std::endl;

namespace elision {

template<typename T, typename Alloc>
class Seq;

template<typename T, typename Alloc>
struct seq {
	typedef std::shared_ptr<Seq<T, Alloc> const> type;
};

/**
 * Provide an immutable sequence data structure that has fast insertion and
 * deletion (creating new instances).
 * @param T		The type stored in the data structure.
 * @param Alloc	The allocator for elements.
 */
template<typename T, typename Alloc = std::allocator<T> >
class Seq {
	/* A note on indexing.
	 *
	 * index  					what
	 * 0      					backing.at(0)
	 * 1      					backing.at(1)
	 * ...
	 * insert 					inserted.at(0)
	 * insert+1					inserted.at(1)
	 * ...
	 * insert+inserted_length	backing.at(insert)
	 * insert+inserted_length+1	backing.at(insert+1)
	 * ...
	 *
	 * If index < insert then backing.at(index).
	 * If index < insert+inserted_length then inserted.at(index-insert).
	 * Otherwise inserted.at(index-inserted_length);
	 */

public:
	typedef typename Alloc::const_reference const_reference;
	typedef typename Alloc::const_pointer const_pointer;
	typedef Alloc allocator_type;
	typedef T value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

private:
	allocator_type alloc_;		//< Allocator for elements of the sequence.
	size_t length_;				//< Length of sequence.
	std::function<T (size_t)> fetch_ = [](size_t index) -> T {
		throw new std::logic_error("fetch uninitialized");
	};

	/**
	 * Make a new instance, with a single element omitted.  Constant time.
	 * @param backing	The elements of the sequence.
	 * @param omit		Zero-based index of the element to omit.
	 * @param alloc		Allocator for the elements.
	 * @throws std::range_error	The index is out of range.
	 */
	Seq(typename seq<T,Alloc>::type backing, size_t omit, Alloc const& alloc=Alloc()) :
			alloc_(alloc), length_(backing->size()) {
		fetch_ = [backing, omit](size_t pos) {
			return pos < omit ? backing->at(pos) : backing->at(pos + 1);
		};
	}

public:
	class const_iterator;

	/**
	 * Make a new instance.
	 * @param backing	The elements of the sequence.  The vector is copied.
	 * @param alloc		Allocator for the elements.
	 */
	Seq(std::vector<T> const backing, Alloc const& alloc=Alloc()) :
			alloc_(alloc), length_(backing.size()) {
		fetch_ = [backing](size_t pos) {
			return backing.at(pos);
		};
	}

	/**
	 * Copy construct a new instance.
	 * @param that		The sequence to copy.
	 */
	Seq(typename seq<T,Alloc>::type that) : alloc_(that->alloc_), length_(that->length_),
			fetch_(that->fetch) {
		// Nothing to do.
	}

	/**
	 * Make a new empty sequence.
	 * @param alloc		Allocator for the elements.
	 */
	Seq(Alloc const& alloc = Alloc()) : alloc_(alloc), length_(0) {
		fetch_ = [](size_t pos) {
			throw new std::range_error("index out of range");
		};
	}

	/**
	 * Make a new repeating sequence.
	 * @param n			Number of elements.
	 * @param x			The element to repeat.
	 * @param alloc		The allocator.
	 */
	Seq(size_type n, T const& x, Alloc const& alloc=Alloc()) : alloc_(alloc),
			length_(n) {
		auto vec = std::shared_ptr<std::vector<T> >(new std::vector<T>(n, x, alloc));
		fetch_ = [vec](size_t pos) {
			return vec->at(pos);
		};
	}

	/**
	 * Make a new sequence from an iterator.
	 * @param first		First element.
	 * @param last		Last element.
	 * @param alloc		Allocator for the elements.
	 */
	template<typename InputIter>
	Seq(InputIter first, InputIter last, Alloc const& alloc = Alloc()) :
			alloc_(alloc), length_(0) {
		auto vec = std::shared_ptr<std::vector<T> >(new std::vector<T>(first,last, alloc));
		length_ = vec->size();
		fetch_ = [vec](size_t pos) {
			return vec->at(pos);
		};
	}

	/// Deallocate this instance.
	virtual ~Seq() {
		clear();
	}

	/**
	 * Get the allocator.
	 * @return	The allocator.
	 */
	allocator_type get_allocator() const { return alloc_; }

	/**
	 * Get an iterator pointing to the first element of the sequence.
	 * @return	Iterator to first element.
	 */
	const_iterator begin() const { return const_iterator(0, fetch_); }

	/**
	 * Get an iterator pointing one past the last element of the sequence.
	 * @return	Iterator just past the end of the sequence.
	 */
	const_iterator end() const { return const_iterator(length_, fetch_); }

	/**
	 * Get an element from the sequence.
	 * @param index		Zero-based index of the element.
	 * @return	The requested element.
	 * @throws std::range_error	The index is out of bounds.
	 */
	T const& at(size_t index) const { return fetch_(index); }

	/**
	 * Clear the content of this sequence.
	 */
	void clear() {
	}

	/**
	 * Determine if this sequence is empty.
	 * @return	True if the sequence is empty.
	 */
	bool empty() const { return size() == 0; }

	/**
	 * Get the number of elements in this sequence.
	 * @return	The number of elements in this sequence.
	 */
	size_type size() const { return length_; }

	/**
	 * Construct a new sequence from this sequence, omitting the specified
	 * element.  This is a constant-time operation.
	 * @param index		Zero-based index of element to omit.
	 * @return	New sequence.
	 * @throws std::range_error		The index if out of bounds.
	 */
	Seq<T> omit(size_t index) const {
		Seq<T> ret(*this, index);
		return ret;
	}

//	/**
//	 * Construct a new sequence from this sequence by inserting all elements
//	 * of another sequence into this one.
//	 * @param start		Zero-based index of the first inserted element.
//	 * @param data		The sequence ot insert.
//	 * @return	The new sequence.
//	 * @throws std::range_error		The index if out of bounds.
//	 */
//	Seq<T> insert(size_t start, Seq<T> const& data) const {
//		Seq<T> ret(*this, start, data);
//		return ret;
//	}

	/**
	 * Get the elements of this sequence as a new vector that is constructed
	 * and returned.
	 * @return	The elements of this sequence.
	 */
	std::vector<T> elements() const {
		std::vector<T> ret(begin(), end());
		return ret;
	}

	/**
	 * Implement an iterator.
	 * @param T		Type of element stored in the sequence.
	 */
	class const_iterator : public std::iterator<std::forward_iterator_tag, T> {
	public:
		/**
		 * Make a new instance.
		 * @param pos		Zero-based index of the iterator.
		 * @param data		The sequence.  This is passed as a pointer, and is
		 * 					never freed by this object.
		 */
		const_iterator(size_t pos, std::function<T (size_t)> fetch) :
				pos_(pos), fetch_(fetch) {
			// Nothing to do.
		}
		const_iterator & operator++() { ++pos_; return *this; }
		const_iterator & operator++(int) { ++pos_; return *this; }
		T const& operator*() const { return fetch_(pos_); }
		T const* operator->() const { return &fetch_(pos_); }
		bool operator==(const_iterator const& other) const {
			return pos_ == other.pos_;
		}
		bool operator!=(const_iterator const& other) const {
			return !operator==(other);
		}

	private:
		size_t pos_;
		std::function<T (size_t)> fetch_;
	};
};

template<typename T>
bool operator==(typename Seq<T>::const_iterator const& first,
		typename Seq<T>::const_iterator const& second) {
	return first.operator==(second);
}

template<typename T>
bool operator!=(typename Seq<T>::const_iterator const& first,
		typename Seq<T>::const_iterator const& second) {
	return first.operator!=(second);
}

} /* namespace elision */

#endif /* SEQ_H_ */
