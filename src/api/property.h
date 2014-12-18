#ifndef CTF_PROPERTY_H
#define CTF_PROPERTY_H

/* 
 * Each CTF object contains certain set of properties that can be modified or
 * retrieved. Macros _CTF_PROPERTY_ and _CTF_PROPERTY_SET are intended to
 * generate C functions that perform this operations. However, they cover only
 * the case when a perfect mapping between the property and its implementation
 * exists. Every other special case should be handled with an actual function.
 *
 * Both getter and setter generators provide two complementary macros, _PROTO
 * and _IMPL used to create the prototype and implementation, respectively.
 * 
 * Each property function is defined by ts name, the type of objects it
 * operates on and the output property. Setter functions additionally expect an
 * argument containing the new value. The name of the property is coded in the
 * name of the function. Therefore, libctf provides two functions (get, set)
 * per one property.
 */

#include "set.h"
#include "get.h"

#endif

