#ifndef ITERMFACTORY_H_
#define ITERMFACTORY_H_

/**
 * @file
 * Define the interface to the term factory.
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

#include "IApply.h"
#include "IBinding.h"
#include "ILambda.h"
#include "IList.h"
#include "ILiteral.h"
#include "IMapPair.h"
#include "IPropertySpecification.h"
#include "IPropertySpecificationBuilder.h"
#include "ISpecialForm.h"
#include "IStaticMap.h"
#include "IVariable.h"

namespace elision {
namespace term {

/**
 * A term factory is required to make instances of terms.  To use this get an
 * instance and then stash it somewhere.  Then invoke instance methods to
 * create terms.
 * 
 * It should be the case that terms from multiple term factories can be
 * combined interchangeably, and care should be taken to ensure this is so.
 */
class TermFactory {
public:
	/// Deallocate this instance.
	virtual ~TermFactory() {};

	//======================================================================
	// Access to root types.
	//======================================================================

	/**
	 * Get the unique root.
	 * @return	The unique root type.
	 */
	virtual pTerm get_root() const = 0;

	/**
	 * Get a root term specified by name.  This keeps a registry of known
	 * root terms.  Requesting one via this method creates it and adds it
	 * to the registry.
	 * @param	name	The name of the root term.
	 * @return	The requested root term.
	 */
	virtual pSymbolLiteral get_root_term(std::string const name) const = 0;

	//======================================================================
	// Well-known root types (and ^ROOT, itself).  Subclasses must initialize
	// these!
	//======================================================================

	pTerm ROOT;					//< Simple access to the root.
	pSymbolLiteral SYMBOL;		//< Simple access to the symbol type.
	pSymbolLiteral STRING;		//< Simple access to the string type.
	pSymbolLiteral INTEGER;		//< Simple access to the integer type.
	pSymbolLiteral FLOAT;		//< Simple access to the float type.
	pSymbolLiteral BITSTRING;	//< Simple access to the bit string type.
	pSymbolLiteral BOOLEAN;		//< Simple access to the Boolean type.
	pSymbolLiteral ANY;			//< The wildcard.
	pSymbolLiteral NONE;		//< Match nothing.
	pSymbolLiteral MAP;			//< Simple access to the type for map pairs.
	pSymbolLiteral SPECIAL_FORM;//< Simple access to the special form type.
	pSymbolLiteral PROPERTIES;	//< Simple access to the type for property specs.

	//======================================================================
	// Well-known literals.
	//======================================================================

	pBooleanLiteral TRUE;		//< True literal.
	pBooleanLiteral FALSE;		//< False literal.

	//======================================================================
	// Make literals.
	//======================================================================

	virtual pSymbolLiteral get_symbol_literal(
			Locus loc, std::string const& name, pTerm type) const = 0;
	virtual pStringLiteral get_string_literal(
			Locus loc, std::string const& value, pTerm type) const = 0;
	virtual pIntegerLiteral get_integer_literal(
			Locus loc, eint_t value, pTerm type) const = 0;
	virtual pFloatLiteral get_float_literal(
			Locus loc, eint_t significand, eint_t exponent, uint16_t radix,
			pTerm type) const = 0;
	virtual pBitStringLiteral get_bit_string_literal(
			Locus loc, eint_t bits, eint_t length, pTerm type) const = 0;
	virtual pBooleanLiteral get_boolean_literal(
			Locus loc, bool value, pTerm type) const = 0;
	virtual pTermLiteral get_term_literal(
			Locus loc, pTerm term) const = 0;

	//======================================================================
	// Make literals with the default type.
	//======================================================================

	pSymbolLiteral get_symbol_literal(Locus loc,
			std::string const& name) const {
		return get_symbol_literal(loc, name, SYMBOL);
	}
	pStringLiteral get_string_literal(Locus loc,
			std::string const& value) const {
		return get_string_literal(loc, value, STRING);
	}
	pIntegerLiteral get_integer_literal(Locus loc,
			eint_t value) const {
		return get_integer_literal(loc, value, INTEGER);
	}
	pFloatLiteral get_float_literal(Locus loc, eint_t significand,
			eint_t exponent, uint16_t radix) const {
		return get_float_literal(loc, significand, exponent, radix, FLOAT);
	}
	pBitStringLiteral get_bit_string_literal(Locus loc, eint_t bits,
			eint_t length) const {
		return get_bit_string_literal(loc, bits, length, BITSTRING);
	}
	pBooleanLiteral get_boolean_literal(Locus loc, bool value) const {
		return get_boolean_literal(loc, value, BOOLEAN);
	}

	//======================================================================
	// Make literals with default type and internal location.
	//======================================================================

	pSymbolLiteral get_symbol_literal(std::string const& name) const {
		return get_symbol_literal(Loc::get_internal(), name);
	}
	pStringLiteral get_string_literal(std::string const& value) const {
		return get_string_literal(Loc::get_internal(), value);
	}
	pIntegerLiteral get_integer_literal(eint_t value) const {
		return get_integer_literal(Loc::get_internal(), value);
	}
	pFloatLiteral get_float_literal(eint_t significand, eint_t exponent,
			uint16_t radix) const {
		return get_float_literal(Loc::get_internal(), significand, exponent,
				radix);
	}
	pBitStringLiteral get_bit_string_literal(eint_t bits,
			eint_t length) const {
		return get_bit_string_literal(Loc::get_internal(), bits, length);
	}
	pBooleanLiteral get_boolean_literal(bool value) const {
		return get_boolean_literal(Loc::get_internal(), value);
	}
	pTermLiteral get_term_literal(pTerm term) const {
		return get_term_literal(Loc::get_internal(), term);
	}

	//======================================================================
	// Make variables.
	//======================================================================

	virtual pVariable get_variable(Locus loc, std::string name, pTerm guard,
			pTerm type) const = 0;

	//======================================================================
	// Make term variables.
	//======================================================================

	virtual pTermVariable get_term_variable(Locus loc, std::string name,
			pTerm type) const = 0;

	//======================================================================
	// Make static maps.
	//======================================================================

	virtual pStaticMap get_static_map(Locus loc, pTerm domain,
			pTerm codomain) const = 0;

	//======================================================================
	// Make map pairs.
	//======================================================================

	virtual pMapPair get_map_pair(Locus loc, pTerm lhs, pTerm rhs,
			pTerm guard) const = 0;

	//======================================================================
	// Make lambdas.
	//======================================================================

	virtual pLambda get_lambda(Locus loc, pVariable parameter,
			pTerm body) const = 0;

	//======================================================================
	// Make special forms.
	//======================================================================

	virtual pSpecialForm get_special_form(Locus loc, pTerm tag,
			pTerm content) const = 0;

	//======================================================================
	// Make lists.
	//======================================================================

	virtual pList get_list(Locus loc, pPropertySpecification spec,
			std::vector<pTerm>& elements) const = 0;

	//======================================================================
	// Handle application.
	//======================================================================

	virtual pTerm apply(Locus loc, pTerm op, pTerm arg) const = 0;

	//======================================================================
	// Build property specifications.
	//======================================================================

	/**
	 * Get a property specification builder instance to construct property
	 * specifications.
	 * @return	A new property specification builder.
	 */
	virtual std::unique_ptr<PropertySpecificationBuilder>
	get_property_specification_builder() const = 0;
};

} /* namespace term */
} /* namespace elision */

#endif /* ITERMFACTORY_H_ */
