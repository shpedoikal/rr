/* -*- Mode: C++; tab-width: 8; c-basic-offset: 8; indent-tabs-mode: t; -*- */

#ifndef RR_PROCESS_SYSCALL_H_
#define RR_PROCESS_SYSCALL_H_

#include "types.h"
#include "util.h"

class Task;

/**
 * Call this just before the recorder is going to store a
 * syscall-entry event.  If any data needs to be saved at syscall
 * entry, do it now.
 */
void rec_before_record_syscall_entry(Task* t, int syscallno);

/**
 * Prepare |t| to enter its current syscall event.  Return nonzero if
 * a context-switch is allowed for |t|, 0 if not.
 *
 * Set |*kernel_sync_addr| to non-NULL to force waiting on that memory
 * cell in the child's address space to become |sync_val|.  This is an
 * overly general mechanism that's used for FUTEX_LOCK_PI.  If you're
 * not FUTEX_LOCK_PI, you probably shouldn't be using this.
 */
int rec_prepare_syscall(Task* t, void** kernel_sync_addr, uint32_t* sync_val);
/**
 * Prepare |t| for its current syscall event to be interrupted and
 * possibly restarted.
 */
void rec_prepare_restart_syscall(Task* t);
/**
 * Restore any argument registers fudged for |t|'s current syscall and
 * store any nondeterministic outparam data.
 */
void rec_process_syscall(Task* t);

#endif /* RR_PROCESS_SYSCALL_H_ */
