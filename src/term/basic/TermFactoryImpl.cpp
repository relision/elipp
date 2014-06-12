/**
 * @file
 * TODO: Describe purpose of file.
 *
 * @author sprowell@gmail.com
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
 * Copyright (c) 2014 by Stacy Prowell (sprowell@gmail.com)
 * All rights reserved.
 * @endverbatim
 */

#include "TermFactoryImpl.h"
#include "LiteralImpl.h"

namespace elision {
namespace term {
namespace basic {

class RootTerm;
typedef std::shared_ptr<RootTerm const> Root;

/**
 * Provide a private implementation of the root term.
 */
class RootTerm : public virtual ITerm {
public:
	/**
	 * Get the unique instance of the root term.
	 * @return The root term.
	 */
	static Term fetch() {
		// Make a new instance of myself.  This is static so we really, really
		// only ever get one.  Just one.  Only one.  Note that we cannot use
		// make_shared because the constructor is private.
		static Root self = std::shared_ptr<RootTerm>(new RootTerm());
		// Make this instance its own type.
		self.get()->me_ = self;
		return self;
	}

	/// Clean up this instance.
	~RootTerm() {};

	inline bool is_constant() const { return true; }
	inline std::string to_string() const { return "^ROOT"; }
	inline Term get_type() const { return me_; }
	inline unsigned int get_de_bruijn_index() const { return 0; }
	inline unsigned int get_depth() const { return 0; }
	inline bool is_meta_term() const { return false; }
	inline Locus get_loc() const { return loc_; }
	inline bool is_root() const { return true; }

protected:
	inline bool is_equal(ITerm const& other) const {
		// If we get here then we match.
		return true;
	}

private:
	/**
	 * Construct a new instance.  This is private because it must only be
	 * called from `fetch`, which explicitly "fixes up" the `me_` field.
	 */
	RootTerm() {}

	/// Our type, which is ourself.
	mutable Root me_;

	/// Hold the internal loc for fast reference.
	Locus loc_ = Loc::get_internal();
};

// Little macro to initialize the root types.
#define INIT(m_name) m_name = get_root_term(#m_name);

TermFactoryImpl::TermFactoryImpl() : root_(RootTerm::fetch()){
	ROOT = root_;
	INIT(SYMBOL);
	INIT(STRING);
	INIT(INTEGER);
	INIT(FLOAT);
	INIT(BITSTRING);
	INIT(BOOLEAN);
}

pSymbolLiteral
TermFactoryImpl::get_root_term(std::string const name) const {
	// Go and get a pointer from the map.
	pSymbolLiteral rt = known_roots_[name];
	if (!rt) {
		// First time through.  Make a new symbol and store it.
		pSymbolLiteral nrt =
				get_symbol_literal(Loc::get_internal(), name, root_);
		known_roots_[name] = nrt;
		return nrt;
	}
	return rt;
}

// Shorthand to make a shared pointer of the correct type with the provided
// arguments.  Depends on names being the "usual" names.
#define MAKE(m_kind, ...) \
	std::shared_ptr<I ## m_kind const>(new m_kind ## Impl(loc, __VA_ARGS__, type))

pSymbolLiteral
TermFactoryImpl::get_symbol_literal(
		Locus loc, std::string const& name, Term type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(SymbolLiteral, name);
}

pStringLiteral
TermFactoryImpl::get_string_literal(
		Locus loc, std::string const& value, Term type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(StringLiteral, value);
}

pIntegerLiteral
TermFactoryImpl::get_integer_literal(
		Locus loc, eint_t value, Term type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(IntegerLiteral, value);
}

pFloatLiteral
TermFactoryImpl::get_float_literal(
		Locus loc, eint_t significand, eint_t exponent, uint16_t radix,
		Term type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(FloatLiteral, significand, exponent, radix);
}

pBitStringLiteral
TermFactoryImpl::get_bit_string_literal(
		Locus loc, eint_t bits, eint_t length, Term type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(BitStringLiteral, bits, length);
}

pBooleanLiteral
TermFactoryImpl::get_boolean_literal(
		Locus loc, bool value, Term type) const {
	NOTNULL(loc);
	NOTNULL(type);
	return MAKE(BooleanLiteral, value);
}

} /* namespace basic */
} /* namespace term */
} /* namespace elision */
