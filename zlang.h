/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    zlang.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZLANG_GUARD_ZLANG_H
#define ZLANG_GUARD_ZLANG_H


#define Z_ZLANG_CAT_I(x, y) x ## y
#define Z_ZLANG_CAT(x, y) Z_ZLANG_CAT_I(x, y)

#define Z_ZLANG_IF(c) Z_ZLANG_CAT(Z_ZLANG_IF_, c)
#define Z_ZLANG_IF_0(t, f) f
#define Z_ZLANG_IF_1(t, f) t

#define Z_ZLANG_IF_INVOKE(m, ...) Z_ZLANG_IF(m(__VA_ARGS__))
#define Z_ZLANG_REM(...) __VA_ARGS__


#define Z_ZLANG_IS_PAREN(x) Z_ZLANG_IS_PAREN_CHECK(Z_ZLANG_IS_PAREN_PROBE x)
#define Z_ZLANG_IS_PAREN_CHECK(...) Z_ZLANG_IS_PAREN_CHECK_N(__VA_ARGS__,0)
#define Z_ZLANG_IS_PAREN_PROBE(...) ~, 1,
#ifndef _MSC_VER
#define Z_ZLANG_IS_PAREN_CHECK_N(x, n, ...) n
#else
// MSVC workarounds
#define Z_ZLANG_IS_PAREN_CHECK_RES(x) x
#define Z_ZLANG_IS_PAREN_CHECK_II(x, n, ...) n
#define Z_ZLANG_IS_PAREN_CHECK_I(x) Z_ZLANG_IS_PAREN_CHECK_RES(Z_ZLANG_IS_PAREN_CHECK_II x)
#define Z_ZLANG_IS_PAREN_CHECK_N(...) Z_ZLANG_IS_PAREN_CHECK_I((__VA_ARGS__))
#endif

#define ZLANG_NIL (Z_ZLANG_ERROR_NOT_FOUND)

// TODO: When a match is found it gets qualified twice, perhaps there is a way
// to make sure we only call it once
#define Z_ZLANG_QUALIFY(ns, x) Z_ZLANG_CAT(ZLANG_,  Z_ZLANG_CAT(Z_ZLANG_CAT(ns, _), x))

#define Z_ZLANG_FIND_FALSE(...) NIL Z_ZLANG_FIND_FALSE_1
#define Z_ZLANG_FIND_FALSE_1(...) Z_ZLANG_FIND_FALSE_2
#define Z_ZLANG_FIND_FALSE_2(...)

#define Z_ZLANG_FIND_TRUE(p, d, x, ...) x



#define Z_ZLANG_FIND(p, d, ...) Z_ZLANG_FIND_1(p, d, ~, __VA_ARGS__, (), ())
#define Z_ZLANG_FIND_1(p, d, q, x, ...) Z_ZLANG_IF(Z_ZLANG_IS_PAREN(x))(Z_ZLANG_FIND_FALSE, Z_ZLANG_IF_INVOKE)(p, d, x)(Z_ZLANG_FIND_TRUE, Z_ZLANG_FIND_2)(p, d, x, __VA_ARGS__)
#define Z_ZLANG_FIND_2(p, d, q, x, ...) Z_ZLANG_IF(Z_ZLANG_IS_PAREN(x))(Z_ZLANG_FIND_FALSE, Z_ZLANG_IF_INVOKE)(p, d, x)(Z_ZLANG_FIND_TRUE, Z_ZLANG_FIND_3)(p, d, x, __VA_ARGS__)
#define Z_ZLANG_FIND_3(p, d, q, x, ...) Z_ZLANG_IF(Z_ZLANG_IS_PAREN(x))(Z_ZLANG_FIND_FALSE, Z_ZLANG_IF_INVOKE)(p, d, x)(Z_ZLANG_FIND_TRUE, Z_ZLANG_FIND_4)(p, d, x, __VA_ARGS__)
#define Z_ZLANG_FIND_4(p, d, q, x, ...) Z_ZLANG_IF(Z_ZLANG_IS_PAREN(x))(Z_ZLANG_FIND_FALSE, Z_ZLANG_IF_INVOKE)(p, d, x)(Z_ZLANG_FIND_TRUE, Z_ZLANG_FIND_5)(p, d, x, __VA_ARGS__)
#define Z_ZLANG_FIND_5(p, d, q, x, ...) Z_ZLANG_IF(Z_ZLANG_IS_PAREN(x))(Z_ZLANG_FIND_FALSE, Z_ZLANG_IF_INVOKE)(p, d, x)(Z_ZLANG_FIND_TRUE, Z_ZLANG_FIND_6)(p, d, x, __VA_ARGS__)
#define Z_ZLANG_FIND_6(p, d, q, x, ...) Z_ZLANG_IF(Z_ZLANG_IS_PAREN(x))(Z_ZLANG_FIND_FALSE, Z_ZLANG_IF_INVOKE)(p, d, x)(Z_ZLANG_FIND_TRUE, Z_ZLANG_FIND_7)(p, d, x, __VA_ARGS__)
#define Z_ZLANG_FIND_7(p, d, q, x, ...) Z_ZLANG_IF(Z_ZLANG_IS_PAREN(x))(Z_ZLANG_FIND_FALSE, Z_ZLANG_IF_INVOKE)(p, d, x)(Z_ZLANG_FIND_TRUE, Z_ZLANG_FIND_8)(p, d, x, __VA_ARGS__)
#define Z_ZLANG_FIND_8(p, d, q, x, ...) Z_ZLANG_IF(Z_ZLANG_IS_PAREN(x))(Z_ZLANG_FIND_FALSE, Z_ZLANG_IF_INVOKE)(p, d, x)(Z_ZLANG_FIND_TRUE, Z_ZLANG_FIND_9)(p, d, x, __VA_ARGS__)






#define Z_ZLANG_INVOKE_REM(m) m, 

#define Z_ZLANG_PRIMITIVE_INVOKE(m, x) m(x)
#define Z_ZLANG_PRIMITIVE_INVOKE_I(x) Z_ZLANG_PRIMITIVE_INVOKE x

#define Z_ZLANG_INVOKE(x) Z_ZLANG_PRIMITIVE_INVOKE_I((Z_ZLANG_INVOKE_REM x))

#define Z_ZLANG_SEARCH_PREDICATE(d, x) Z_ZLANG_IS_PAREN(Z_ZLANG_QUALIFY(x, d))
#define Z_ZLANG_SEARCH_SELECT_NS() Z_ZLANG_IF(Z_ZLANG_IS_PAREN(ZLANG_USE))(Z_ZLANG_REM ZLANG_USE, ZLANG_NS)
#define Z_ZLANG_SEARCH_NS(m, x) Z_ZLANG_QUALIFY(Z_ZLANG_FIND(Z_ZLANG_SEARCH_PREDICATE, x, Z_ZLANG_SEARCH_SELECT_NS()), x)
#define Z_ZLANG_SEARCH_FIRST(m, x) m
#define Z_ZLANG_SEARCH_I(m, x) Z_ZLANG_IF(Z_ZLANG_IS_PAREN(m))(Z_ZLANG_SEARCH_FIRST, Z_ZLANG_SEARCH_NS)(m, x)
#define Z_ZLANG_SEARCH(x) Z_ZLANG_SEARCH_I(Z_ZLANG_CAT(ZLANG_, x), x)

#define ZLANG(x) Z_ZLANG_INVOKE(Z_ZLANG_SEARCH(x))


#ifndef ZLANG_DONT_USE_DOLLAR_SIGN
#define $ ZLANG
#endif

// #define ZLANG_NS zlang
// #define ZLANG_USE (zlang2)
// #define TEST1(x) x
// #define ZLANG_zlang_test (TEST1)

// #define TEST2(x) 0
// #define ZLANG_zlang2_test (TEST2)

// $(test passed)
// $(zlang_test passed)

#endif
