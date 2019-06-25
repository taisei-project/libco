/*
  WARNING: the overhead of POSIX ucontext is very high,
  assembly versions of libco or libco_sjlj should be much faster

  this library only exists for two reasons:
  1: as an initial test for the viability of a ucontext implementation
  2: to demonstrate the power and speed of libco over existing implementations,
     such as pth (which defaults to wrapping ucontext on unix targets)

  use this library only as a *last resort*
*/

// NOTE: ASan support is based on code from QEMU:
// https://github.com/qemu/qemu/commit/d83414e1fd1941ca8228b5cf6a06697bd1ff7f83

#define LIBCO_C
#include "libco.h"

#define _BSD_SOURCE
#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <ucontext.h>

#ifdef __cplusplus
extern "C" {
#endif

static thread_local ucontext_t co_primary;
static thread_local ucontext_t* co_running = 0;

static void finish_switch_fiber(void *fake_stack_save) {
#ifdef LIBCO_ASAN
  const void *bottom_old;
  size_t size_old;

  __sanitizer_finish_switch_fiber(fake_stack_save, &bottom_old, &size_old);

  // FIXME: from QEMU; not sure what this is for
  /*
  if(!leader.stack) {
    leader.stack = (void *)bottom_old;
    leader.stack_size = size_old;
  }
  */
#endif
}

static void start_switch_fiber(void **fake_stack_save, const void *bottom, size_t size){
#ifdef LIBCO_ASAN
  __sanitizer_start_switch_fiber(fake_stack_save, bottom, size);
#endif
}

union ucarg {
  int i[2];
  void (*coentry)(void);
};

cothread_t co_active() {
  if(!co_running) co_running = &co_primary;
  return (cothread_t)co_running;
}

void co_trampoline(int i0, int i1) {
  union ucarg a;
  a.i[0] = i0;
  a.i[1] = i1;
  finish_switch_fiber(NULL);
  a.coentry();
}

cothread_t co_create(unsigned int heapsize, void (*coentry)(void)) {
  if(!co_running) co_running = &co_primary;
  ucontext_t* thread = (ucontext_t*)malloc(sizeof(ucontext_t));
  if(thread) {
    if((!getcontext(thread) && !(thread->uc_stack.ss_sp = 0)) && (thread->uc_stack.ss_sp = malloc(heapsize))) {
      thread->uc_link = co_running;
      thread->uc_stack.ss_size = heapsize;

      union ucarg a;
      a.coentry = coentry;
      makecontext(thread, (void(*)(void))co_trampoline, 2, a.i[0], a.i[1]);
    } else {
      co_delete((cothread_t)thread);
      thread = 0;
    }
  }
  return (cothread_t)thread;
}

void co_delete(cothread_t cothread) {
  if(cothread) {
    if(((ucontext_t*)cothread)->uc_stack.ss_sp) { free(((ucontext_t*)cothread)->uc_stack.ss_sp); }
    free(cothread);
  }
}

void co_switch(cothread_t cothread) {
  ucontext_t* old_thread = co_running;
  co_running = (ucontext_t*)cothread;

  void *fake_stack_save = NULL;
  start_switch_fiber(&fake_stack_save, co_running->uc_stack.ss_sp, co_running->uc_stack.ss_size);
  swapcontext(old_thread, co_running);
  finish_switch_fiber(fake_stack_save);
}

#ifdef __cplusplus
}
#endif
