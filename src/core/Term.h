#ifndef TERM_H_
#define TERM_H_

/**
 * @file
 * Define the basic types that are used by all terms.
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

#include <string>

namespace elision {
namespace term {

/**
 * Every term can have an associated location, which tells where the term
 * was originally declared.  This can be @b internal, or it can be from a
 * @b file, or it could be from an interactive @b console session.
 *
 * @section using Using
 * Every term has an associated location that is provided during construction.
 * To make a location, do one of the following.
 *   - If the location is from @c file with line number @c line and column
 *     number @c column, then invoke <tt>Loc(file, line, column)</tt>.
 *   - If the location is from a console session with line number @c line and
 *     column number @c column, then invoke <tt>Loc(line, column)</tt>.
 *   - If the term is being created as part of an internal process (such as
 *     the root type) or otherwise has no associated location, then get the
 *     internal location via <tt>Loc::get_internal()</tt>.
 */
class Loc {
public:
    /**
     * Initialize a new instance.  Note that both the line and column numbers
     * are one-based, so zero can be used to indicate that the respective
     * value is not known.
     * @param source    The source.  This should be the file name for files,
     *                  the string "(console)" for the console, and the empty
     *                  string for internal.
     * @param line      The source line number.  If none is known, use zero.
     * @param column    The source column.  If none is known, use zero.
     */
    Loc(std::string const& source, unsigned int line = 0,
            unsigned int column = 0);

    /**
     * Initialize a console-based location.
     * @param line      The source line number.  If none is known, use zero.
     * @param column    The source column.  If none is known, use zero.
     */
    Loc(unsigned int line = 0, unsigned int column = 0);

    /**
     * Copy constructor.
     * @param loc       Another location.
     */
    Loc(Loc const& loc);

    /**
     * Compare two locations.
     * @return  True iff the locations are the same, and false otherwise.
     */
    bool operator==(Loc const& other) const;

    /**
     * Compare two locations.
     * @return  False iff the locations are the same, and true otherwise.
     */
    bool operator!=(Loc const& other) const;

    /**
     * Get this location instance as a string.  The resulting string has the
     * form: <tt>source:line:column</tt>.  This is based on the usual error
     * format of many compilers.
     *
     * If the location is internal (the source is the empty string) then the
     * result is just the empty string.
     * @return  This location instance as a string.
     */
    operator std::string() const;

    /// Deallocate this instance.
    virtual ~Loc();

    /**
     * Get the source.  This will be the filename, the empty string (for
     * an internal location), or the special string <tt>(console)</tt> for
     * a console location.
     * @return  The source name.
     */
    std::string& get_source();

    /**
     * Get the line number, if provided.  Returns zero if none.
     * @return  The one-based line number.
     */
    unsigned int get_line();

    /**
     * Get the column number, if known.  Returns zero if not known.
     * @return  The one-based column number.
     */
    unsigned int get_column();

    /**
     * Get the special internal location.
     * This is much faster than using <tt>Loc("")</tt>, since it only constructs
     * the first time.
     */
    static Loc const& get_internal();

private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
};


/**
 * This is the common base class for all terms.
 */
class Term {
public:
    /// Deallocate this instance.
    virtual ~Term() {}

    /**
     * Get the type of this term.  Every term has an associated type.
     * @return  The type of this term.
     */
    virtual Term const& get_type() = 0;

    /**
     * Generate a primitive string representation of this term.  This is used
     * solely for debugging, as it cannot exploit any semantic information.
     */
    virtual operator std::string() = 0;
};

} /* namespace term */
} /* namespace elision */

#endif /* TERM_H_ */
