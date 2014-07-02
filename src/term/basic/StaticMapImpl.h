#ifndef STATICMAPIMPL_H_
#define STATICMAPIMPL_H_

/**
 * @file
 * Define a simple interface to a static map.
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
#include "term/IStaticMap.h"
#include <Lazy.h>

namespace elision {
namespace term {
namespace basic {

using namespace elision;
using namespace elision::term;

class StaticMapImpl: public IStaticMap, public TermImpl {
public:
	virtual ~StaticMapImpl() = default;

	inline pTerm get_domain() const {
		return domain_;
	}

	inline pTerm get_codomain() const {
		return codomain_;
	}

	inline bool is_constant() const {
		return domain_->is_constant() && codomain_->is_constant();
	}

	inline bool is_equal(ITerm const& other) const {
		auto oth = dynamic_cast<IStaticMap const*>(&other);
		return *get_domain() == *oth->get_domain() &&
				*get_codomain() == *oth->get_codomain();
	}

	inline TermKind get_kind() const {
		return STATIC_MAP_KIND;
	}

	inline std::string to_string() const {
		return strval_;
	}

	inline unsigned int get_depth() const {
		return std::max(get_type()->get_depth(), domain_->get_depth(),
				codomain_->get_depth()) + 1;
	}

private:
	friend class TermFactoryImpl;
	StaticMapImpl(Locus the_loc, pTerm the_domain, pTerm the_codomain,
			pTerm the_type);
	pTerm domain_;
	pTerm codomain_;
	Lazy<std::string> strval_;
};

} /* namespace basic */
} /* namespace term */
} /* namespace elision */

#endif /* STATICMAPIMPL_H_ */
