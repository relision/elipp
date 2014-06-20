#ifndef OMITSEQ_H_
#define OMITSEQ_H_

/**
 * @file
 * Implement a functional sequence with fast deletion and insertion.
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

namespace elision {

/**
 * Provides a sequence data structure that has fast deletion and insertion
 * operations which remaining functional.  That is, these operations generate
 * a new sequence which references the old sequence transparently, avoiding
 * copying.
 */
template<typename T>
class OmitSeq {
public:
	/**
	 * Make a new, empty sequence.
	 */
	OmitSeq() : length_(0) {}

	/**
	 * Make a new sequence, wrapping the provided elements.  The elements are
	 * copied into this structure!
	 * @param elts	The elements to wrap.
	 */
	OmitSeq(std::vector<T> elts) : elements_(elts), length_(len(elts)) {}

	/// Deallocate this instance.
	virtual ~OmitSeq() = default;

	/**
	 * Get the requested element from the sequence using its zero-based index.
	 * @param	index	Position of element requested.
	 * @return	The requested element.
	 */
	virtual T& operator[](size_t index) const {
		return elements_[index];
	}

	/**
	 * Get the number of elements in this sequence.
	 */
	virtual size_t size() const {
		return length_;
	}

	OmitSeq<T> drop(size_t position) const {
		return OmitSeqDrop(*this, position);
	}

	OmitSeq<T> insert(size_t position, OmitSeq<T> others) const {
		return OmitSeqInsert(*this, position, others);
	}

private:
	typedef OmitSeq seq_t;
	std::vector<T> const elements_;
	size_t const length_;

	class OmitSeqDrop : public OmitSeq<T> {
		OmitSeqDrop(OmitSeq<T> const& backing, size_t omit) :
			backing_(backing), omit_(omit), length_(backing.length_-1) {}
		OmitSeq const& backing_;
		size_t const omit_;
		size_t const length_;

	public:
		virtual T& operator[](size_t index) const {
			if (index < omit_) return backing_[index];
			else return backing_[index+1];
		}
		virtual size_t size() const {
			return length_;
		}
	};

	class OmitSeqInsert : public OmitSeq<T> {
		OmitSeqInsert(OmitSeq<T> const& backing, size_t position,
				OmitSeq<T> const& others) :
					backing_(backing),
					others_(others),
					position_(position),
					length_(backing.length_ + others.length_) {}
		OmitSeq const& backing_;
		OmitSeq const& others_;
		size_t const position_;
		size_t const length_;

	public:
		virtual T& operator[](size_t index) const {
			if (index < position_)
				return backing_[index];
			else if (index < position_ + others_.length_)
				return others_[index - position_];
			else
				return backing_[index - others_.length_];
		}
		virtual size_t size() const {
			return length_;
		}
	};
};


} /* namespace elision */

#endif /* OMITSEQ_H_ */
