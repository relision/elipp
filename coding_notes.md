# Coding Notes for Elision

## Use the standard opening block on all files
Add the following at the top of your files.

``` cpp
/**
 * @file
 * TODO: Describe purpose of file.
 *
 * @author (your email here)
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
```

## Check arguments for null
C++ does not explicitly catch null pointer dereferences (or divide by zero,
etc.).  These give undefined behavior, and so it is important to stick with
the principle to **fail fast**.  There is a macro that will help, found in
`elision.h`: `NOTNULL(arg)`, where `arg` is the argument.  This will cause
a `std::invalid_argument` exception to be thrown if the argument is null.
Please use it.  It works correctly for smart pointers, etc.

## Document all public and protected members
Write Javadoc-style Doxygen comments on all public and protected members.
Document other stuff, too, if you want.  It is not necessary to document
inherited members.

## Use complete sentences in comments
Write complete sentences and try to use correct spelling and grammar in all your
comments.  You don't need to be verbose, you just need to communicate to someone
else who needs help understanding your code.

Assume people can read code and write comments that add useful information.  If
everything is incredibly self-explanatory to someone who picks up the code in 
five years, then no comments are needed.

## Write types right to left, and & and * are part of the type
When writing terms, write them so they can be properly read right to left.  This
avoids some ambiguous situations, and is generally preferred.  So, instead of
writing `const std::string &fred` you should write `std::string const& fred`.
You can then read the type as "reference to a constant instance of a string."
Does the position of `const` matter?  Not really.  This is simply a preference.
Note that Stroustrup, K&R, and the standards use `const std::string&`.  But
I prefer `std::string const&`, and it's my code.
See [this](http://www.unixwiz.net/techtips/reading-cdecl.html).

The basic type is on the far left, with modifiers to the right.  Simple, right?

## Put an underscore after protected and private member variables
Pretty self-explanatory.  Put the underscore at the end, not the beginning.
C++ reserves two leading underscores and a leading underscore followed by a
capital, so to avoid any hint of conflict, put the underscore at the end.

## Comment ending braces for large items
Please always comment the end brace for a namespace or loop.  Comment others
where the braces span a large section, or where there is deep nesting.  Nothing
too elaborate, and you can ignore the rule about complete sentences here.

``` cpp
namespace elision {
  // Stuff goes here...
} // namespace elision
```

## Pass std::string
Pass `std::string` by value.  This gets optimized by SSO and move semantics,
and is the C++11 preferred way to do this.  See this note on
[stackoverflow](https://stackoverflow.com/questions/10231349/are-the-days-of-passing-const-stdstring-as-a-parameter-over).

## Implement operator std::string()
Every class should implement this, and provide an appropriate string.  For a
term this is the Elision representation of the term - without any enclosing
semantic information, of course, since that is outside the scope of the term
instance.

## Implement std::hash for your class
Provide a reasonable has function for your class.  Do this by specializing the
`std::hash` template for your class.  See this note on
[stackoverflow](https://stackoverflow.com/questions/8157937/how-to-specialize-stdhashkeyoperator-for-user-defined-type-in-unordered).

Please put the specialization in the header file for the class.

## Implement operator== for your class
See this note on overriding standard operators for
[Caltech's CS11 course](http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html).

Next, implement `!=` in terms of `==` (unless there is a performance reason to
do something else).  Here is an example for some type `term_t`.

## Be explicit about inline definitions
Including short definitions in a header file is fine, but the complier is likely
(though not guaranteed, of course) to inline these.  To make it explicit that
you are not just lazy, please label these with inline, so folks don't move them
to a `.cpp` file, and also don't go looking for them in the `.cpp` file.

Please don't put constructor definitions in the header file.

## Use some simple notation
Don't get hung up on Hungarian notation to the point of insanity, but please
prefix abstract classes containing only pure virtuals with `I`, and follow
implementations with `Impl`.  Prefix pointer types with `p`.  Thus we end up
with `ITerm`, implemented as `TermImpl`, and with pointer type `pTerm`, which
is a typedef for `shard_ptr<ITerm const>`.

# The implementation order
  - **Literal**
  - **Variable** (needs Literals for guards)
  - **Static Map**
  - **Lambda** (needs Static Map for type and Variable for parameter)
  - Apply
  - Binding (needs Map Pair and allows application of Lambdas, and Turing completeness)
  - Map Pair (needs Literals for guards)
  - Property Specification (needs Variables and Literals)
  - List (needs Property Specification)
  - Special Form
