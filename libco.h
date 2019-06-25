/*
  libco v18.02 (2017-11-06)
  author: byuu
  license: ISC
*/

#ifndef LIBCO_H
#define LIBCO_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void* cothread_t;

cothread_t co_active(void);
cothread_t co_create(unsigned int, void (*)(void));
void co_delete(cothread_t);
void co_switch(cothread_t);

#ifdef LIBCO_C

#if defined(LIBCO_MP)
  #define thread_local __thread
#else
  #define thread_local
#endif

#if __STDC_VERSION__ >= 201112L
  #if !defined(_MSC_VER)
    #include <stdalign.h>
  #endif
#else
  #define alignas(bytes)
#endif

#if defined(_MSC_VER)
  #define section(name) __declspec(allocate("." #name))
#elif defined(__APPLE__)
  #define section(name) __attribute__((section("__TEXT,__" #name)))
#else
  #define section(name) __attribute__((section("." #name "#")))
#endif

#ifndef __has_feature
  #define __has_feature(x) 0 /* compatibility with non-clang compilers */
#endif

#if defined(__SANITIZE_ADDRESS__) || __has_feature(address_sanitizer)
  #include <sanitizer/asan_interface.h>
  #define LIBCO_ASAN
#endif

#include "libco_config.h"

/* ifdef LIBCO_C */
#endif

#ifdef __cplusplus
}
#endif

/* ifndef LIBCO_H */
#endif
