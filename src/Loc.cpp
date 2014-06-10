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

#include "Loc.h"
#include <sstream>

namespace elision {

struct Loc::Impl {
    std::string source_{""};
    unsigned int line_ = 0;
    unsigned int column_ = 0;
};

Loc::Loc(const std::string& source, unsigned int line, unsigned int column)
:pimpl_(new Impl) {
    pimpl_->source_ = source;
    pimpl_->line_ = line;
    pimpl_->column_ = column;
}

Loc::Loc(unsigned int line, unsigned int column) :pimpl_(new Impl) {
    pimpl_->source_ = "(console)";
    pimpl_->line_ = line;
    pimpl_->column_ = column;
}

Loc::Loc(Loc const& loc) {
    pimpl_->source_ = loc.pimpl_->source_;
    pimpl_->line_ = loc.pimpl_->line_;
    pimpl_->column_ = loc.pimpl_->column_;
}

Loc::~Loc() {}

std::string& Loc::get_source() { return pimpl_->source_; }

unsigned int Loc::get_line() { return pimpl_->line_; }

unsigned int Loc::get_column() { return pimpl_->column_; }

bool
Loc::operator==(Loc const& other) const {
    return pimpl_->source_ == other.pimpl_->source_ &&
            pimpl_->line_ == other.pimpl_->line_ &&
            pimpl_->column_ == other.pimpl_->column_;
}

bool
Loc::operator!=(Loc const& other) const {
    return !(*this == other);
}

Loc::operator
std::string() const {
    std::ostringstream str;
    if (pimpl_->source_.length() > 0) {
        str << pimpl_->source_ << ":"
                << pimpl_->line_ << ":"
                << pimpl_->column_;
    }
    return(str.str());
}

EPTR(Loc)
Loc::get_internal() {
    static EPTR(Loc) internal = std::shared_ptr<Loc const>(new Loc(""));
    return internal;
}

} /* namespace elision */
