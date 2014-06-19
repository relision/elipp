#ifndef SPECIALFORMIMPL_H_
#define SPECIALFORMIMPL_H_

/**
 * @file
 * Define the interface for an implementation of special forms.
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

#include <basic/TermImpl.h>
#include <ISpecialForm.h>
#include <Lazy.h>

namespace elision {
namespace term {
namespace basic {

class SpecialFormImpl: public ISpecialForm, public TermImpl {
public:
	virtual ~SpecialFormImpl() = default;

	inline pTerm get_tag() const {
		return tag_;
	}

	inline pTerm get_content() const {
		return content_;
	}

	inline bool is_constant() const {
		return tag_->is_constant() && content_->is_constant();
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<ISpecialForm const*>(&other);
		return *get_tag() == *oth->get_tag() &&
				*get_content() == *oth->get_content();
	}

	inline TermKind get_kind() const {
		return SPECIAL_FORM_KIND;
	}

	inline std::string to_string() const {
		return strval_;
	}

private:
	friend class TermFactoryImpl;
	SpecialFormImpl(Locus the_loc, pTerm the_tag, pTerm the_content,
			pTerm the_type);
	pTerm tag_;
	pTerm content_;
	Lazy<std::string> strval_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* SPECIALFORMIMPL_H_ */
