/*
 * File: genlib.h
 * Version: 1.1
 * Modified on Fri Jul 15 15:45:52 1994 by eroberts
 * Last modified 2019-10-25 by Anders Carstensen
 *	Changed name of functions to begin with lower case letter
 *	In source file added - #pragma warning(disable:4996)
 *	which in windows enables the use of unsafe functions
 *	such as scanf. 
 * -----------------------------------------------------
 * This file contains several definitions that form the
 * core of a general-purpose ANSI C library developed by Eric
 * Roberts.  The goal of this library is to provide a basic
 * set of tools and conventions that increase the readability
 * of C programs, particularly as they are used in a teaching
 * environment.
 *
 * The basic definitions provided by genlib.h are:
 *
 *    1.  Declarations for several new "primitive" types
 *        (most importantly bool and string) that are
 *        used throughout the other libraries and
 *        applications as fundamental types.
 *
 *    2.  A new set of functions for memory allocation.
 *
 *    3.  A function for error handling.
 */

#ifndef _genlib_h
#define _genlib_h

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/* Section 1 -- Define new "primitive" types */

/*
 * Type: bool
 * ----------
 * This type has two values, FALSE and TRUE, which are equal to 0
 * and 1, respectively.  Most of the advantage of defining this type
 * comes from readability because it allows the programmer to
 * provide documentation that a variable will take on only one of
 * these two values.  Designing a portable representation, however,
 * is surprisingly hard, because many libraries and some compilers
 * define these names.  The definitions are usually compatible but
 * may still be flagged as errors.
 */

#ifdef THINK_C
   typedef int bool;
#else
#  ifdef TRUE
#    ifndef bool
#      define bool int
#    endif
#  else
#    ifdef bool
#      define FALSE 0
#      define TRUE 1
#    else
       typedef enum {FALSE, TRUE} bool;
#    endif
#  endif
#endif

/*
 * Type: string
 * ------------
 * The type string is identical to the type char *, which is
 * traditionally used in C programs.  The main point of defining a
 * new type is to improve program readability.   At the abstraction
 * levels at which the type string is used, it is usually not
 * important to take the string apart into its component characters.
 * Declaring it as a string emphasizes this atomicity.
 */

typedef char *string;

/*
 * Constant: UNDEFINED
 * -------------------
 * Besides NULL, the only other constant of pointer type is
 * UNDEFINED, which is used in certain packages as a special
 * sentinel to indicate an undefined pointer value.  In many
 * such contexts, NULL is a legitimate data value and is
 * therefore inappropriate as a sentinel.
 */

#define UNDEFINED ((void *) undefined_object)

extern char undefined_object[];

/* Section 2 -- Memory allocation */

/*
 * General notes:
 * --------------
 * These functions provide a common interface for memory
 * allocation.  All functions in the library that allocate
 * memory do so using getBlock and freeBlock.  Even though
 * the ANSI standard defines malloc and free for the same
 * purpose, using getBlock and freeBlock provides greater
 * compatibility with non-ANSI implementations, automatic
 * out-of-memory error detection, and the possibility of
 * substituting a garbage-collecting allocator.
 */

/*
 * Function: getBlock
 * Usage: ptr = (type) getBlock(nbytes);
 * -------------------------------------
 * getBlock allocates a block of memory of the given size.  If
 * no memory is available, getBlock generates an error.
 */

void *getBlock(size_t nbytes);

/*
 * Function: freeBlock
 * Usage: freeBlock(ptr);
 * ----------------------
 * freeBlock frees the memory associated with ptr, which must
 * have been allocated using getBlock, New, or NewArray.
 */

void freeBlock(void *ptr);

/*
 * Macro: New
 * Usage: p = New(pointer-type);
 * -----------------------------
 * The New pseudofunction allocates enough space to hold an
 * object of the type to which pointer-type points and returns
 * a pointer to the newly allocated pointer.  Note that
 * "New" is different from the "new" operator used in C++;
 * the former takes a pointer type and the latter takes the
 * target type.
 */

#define New(type) ((type) getBlock(sizeof *((type) NULL)))

/*
 * Macro: NewArray
 * Usage: p = NewArray(n, element-type);
 * -------------------------------------
 * NewArray allocates enough space to hold an array of n
 * values of the specified element type.
 */

#define NewArray(n, type) ((type *) getBlock((n) * sizeof(type)))

/* Section 3 -- Basic error handling */

/*
 * Function: error
 * Usage: error(msg, ...)
 * ----------------------
 * error generates an error string, expanding % constructions
 * appearing in the error message string just as printf does.
 * After printing the error message, the program terminates.
 */

void error(string msg, ...);

#endif
