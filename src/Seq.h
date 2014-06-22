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

#define D(msg_m) std::cout << msg_m << std::flush;
#define P(msg_m) std::cout << msg_m << std::flush << std::endl;

namespace elision {

/**
 * Provide an immutable sequence data structure that has fast insertion and
 * deletion (creating new instances).
 * @param T		The type stored in the data structure.
 * @param Alloc	The allocator for elements.
 */
template<typename T, typename Alloc = std::allocator<T> >
class Seq {
	/**
	 * Store a sequence.  This is a common base class for all sequences.
	 * @param U	The type of elements in the sequence.
	 */
	template<typename U>
	struct seq {
		seq(size_t length) : length_(length) {
			// Nothing to do.
		}
		virtual ~seq() {}
		virtual U const& at(size_t index) const {
			throw std::runtime_error("Seq<T>::seq::at not overridden properly");
		}
		virtual size_t size() const { return length_; }
		size_t length_;
	};

	/**
	 * Store a sequence backed by a vector.  The vector is copied into the
	 * sequence.
	 * @param U	The type of elements in the sequence.
	 */
	template<typename U>
	struct vec_seq : public seq<U> {
		vec_seq(std::vector<U> const& back) : seq<U>(back.size()), backing_(back) {}
		std::vector<U> const backing_;	//< Elements in the sequence.
		virtual U const& at(size_t index) const {
			return backing_.at(index);
		}
	};

	/**
	 * Store a sequence with a single element omitted.  The sequence is passed
	 * by pointer and is never freed by this struct.
	 * @param U	The type of elements in the sequence.
	 */
	template<typename U>
	struct omit_seq : public seq<U> {
		omit_seq(seq<U> const* back, size_t omit) : backing_(back), omit_(omit),
				seq<U>(back->size()) {}
		seq<U> const* backing_;		//< Elements in the sequence.
		size_t omit_;				//< Index of the element that is omitted.
		virtual U const& at(size_t index) const {
			return (index < omit_) ? backing_->at(index) : backing_->at(index+1);
		}
	};

	/**
	 * Store a sequence with another sequence inserted into it.  The sequences
	 * are passed by pointer and are never freed by this struct.
	 * @param U	The type of elements in the sequence.
	 */
	template<typename U>
	struct insert_seq : public seq<U> {
		insert_seq(seq<U> const* back, size_t insert, seq<U> const* other) :
				backing_(back), insert_(insert), inserted_(other),
				seq<U>(back->size() + other->size()),
				inserted_length_(other->size()) {}
		seq<U> const* backing_;		//< Elements in the main sequence.
		size_t insert_;				//< First index of inserted elements.
		seq<U> const* inserted_;	//< Inserted elements.
		size_t inserted_length_;	//< Total sequence length.
		virtual U const& at(size_t index) const {
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

			// If the index is less than the start of the inserted elements,
			// then return directly from backing.
			if (index < insert_) return backing_->at(index);
			// If the index is at or past the insertion point, but not past
			// the end of the inserted sequence, then return from the inserted
			// sequence.
			if (index < insert_+inserted_length_)
				return inserted_->at(index - insert_);
			// The index is past the end of the inserted sequence.  Return from
			// the original backing sequence.
			return backing_->at(index - inserted_length_);
		}
	};

public:
	typedef typename Alloc::const_reference const_reference;
	typedef typename Alloc::const_pointer const_pointer;
	typedef Alloc allocator_type;
	typedef T value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

private:
	allocator_type alloc_;		//< Allocator for elements of the sequence.
	std::unique_ptr<seq<T> const> data_;		//< The data held in this sequence.
	// The data_ pointer is owned by this instance, and is explicitly deleted
	// in the destructor.  Note that it was allocated in the constructor to
	// hold whatever was passed in.

public:
	class const_iterator;

	/**
	 * Make a new instance.
	 * @param backing	The elements of the sequence.  The vector is copied.
	 * @param alloc		Allocator for the elements.
	 */
	Seq(std::vector<T> const& backing, Alloc const& alloc=Alloc()) :
			alloc_(alloc), data_(new vec_seq<T>(backing)) {
		// Nothing to do.
	}

	/**
	 * Make a new instance, with a single element omitted.  Constant time.
	 * @param backing	The elements of the sequence.
	 * @param index		Zero-based index of the element to omit.
	 * @param alloc		Allocator for the elements.
	 * @throws std::range_error	The index is out of range.
	 */
	Seq(Seq<T> const& backing, size_t index, Alloc const& alloc=Alloc()) :
			alloc_(alloc), data_(new omit_seq<T>(backing.data_, index)) {
		// Nothing to do.
	}

	/**
	 * Make a new instance that inserts one sequence into another.  Constant
	 * time.
	 * @param backing	The elements of the primary sequence.
	 * @param start		Zero-based index of the first inserted element.
	 * @param other		The sequence to insert.
	 * @param alloc		Allocator for the elements.
	 * @throws std::range_error	The index is out of range.
	 */
	Seq(Seq<T> const& backing, size_t start, Seq<T> const& other,
			Alloc const& alloc=Alloc()) : alloc_(alloc),
					data_(new insert_seq<T>(backing.data_, start, other)) {
		// Nothing to do.
	}

	/**
	 * Copy construct a new instance.
	 * @param that		The sequence to copy.
	 */
	Seq(Seq<T> const& that) : alloc_(that.alloc_),
			data_{std::unique_ptr<seq<T> const>(that.data_)} {
		// Nothing to do.
	}

	/**
	 * Make a new empty sequence.
	 * @param alloc		Allocator for the elements.
	 */
	Seq(Alloc const& alloc = Alloc());
	Seq(size_type n, T const& x, Alloc const& alloc=Alloc()) : alloc_(alloc),
			data_(vec_seq<T>(std::vector<T>(n, x, alloc))) {
		// Nothing to do.
	}

	/**
	 * Make a new sequence from an iterator.
	 * @param first		First element.
	 * @param last		Last element.
	 * @param alloc		Allocator for the elements.
	 */
	template<typename InputIter>
	Seq(InputIter first, InputIter last, Alloc const& alloc = Alloc()) :
			alloc_(alloc), data_(new vec_seq<T>(std::vector<T>(first, last, alloc))) {
		// Nothing to do.
	}

	/// Deallocate this instance.
	virtual ~Seq() {
		//delete data_;
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
	const_iterator begin() const { return const_iterator(0, data_); }

	/**
	 * Get an iterator pointing one past the last element of the sequence.
	 * @return	Iterator just past the end of the sequence.
	 */
	const_iterator end() const { return const_iterator(data_->size(), data_); }

	/**
	 * Get an element from the sequence.
	 * @param index		Zero-based index of the element.
	 * @return	The requested element.
	 * @throws std::range_error	The index is out of bounds.
	 */
	T const& at(size_t index) const { return data_->at(index); }

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
	size_type size() const { return data_->size(); }

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

	/**
	 * Construct a new sequence from this sequence by inserting all elements
	 * of another sequence into this one.
	 * @param start		Zero-based index of the first inserted element.
	 * @param data		The sequence ot insert.
	 * @return	The new sequence.
	 * @throws std::range_error		The index if out of bounds.
	 */
	Seq<T> insert(size_t start, Seq<T> const& data) const {
		Seq<T> ret(*this, start, data);
		return ret;
	}

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
		const_iterator(size_t pos, seq<T> const* elts) : pos_(pos), elts_(elts) {
			// Nothing to do.
		}
		const_iterator & operator++() { ++pos_; return *this; }
		const_iterator & operator++(int) { ++pos_; return *this; }
		T const& operator*() const { return elts_->at(pos_); }
		T const* operator->() const { return &elts_->at(pos_); }
		bool operator==(const_iterator const& other) const {
			return pos_ == other.pos_;
		}
		bool operator!=(const_iterator const& other) const {
			return !operator==(other);
		}

	private:
		size_t pos_;
		seq<T> const* elts_;
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
