# Pintos
Labs for Principles of Operating Systems course (CompSci 143A) at UCI. [Pintos](http://pintos-os.org) 
is a teaching operating system for x86, challenging but not overwhelming, small
but realistic enough to understand OS in depth (it can run x86 machine and simulators 
including QEMU, Bochs and VMWare Player!). The main source code, documentation and assignments 
are developed by Ben Pfaff and others from Stanford (refer to its [LICENSE](./LICENSE)).
This repository also contains some changes made by [Ryan Huang](huang@cs.jhu.edu).



### Project 0
##### Exercise 0.1
Take a screenshot of the successful booting of Pintos in Bochs or QEMU, either in the terminal
or Bochs/QEMU window. Put the screenshot under pintos/src/p0.


##### Exercise 0.2
Enhance threads/init.c to implement a tiny kernel monitor in Pintos. Feel free to add new
source files in to the Pintos code base for this task, e.g., provide a readline library function. 



### Project 1

##### Exercise 1.1

Reimplement timer_sleep(), defined in devices/timer.c. Although a working implementation is
provided, it "busy waits," that is, it spins in a loop checking the current time and calling
thread_yield() until enough time has gone by. Reimplement it to avoid busy waiting.
Function: void timer_sleep (int64_t ticks)
Suspends execution of the calling thread until time has advanced by at least x timer ticks. Unless
the system is otherwise idle, the thread need not wake up after exactly x ticks. Just put it on the
ready queue after they have waited for the right amount of time.
timer_sleep() is useful for threads that operate in real-time, e.g. for blinking the cursor once per
second.
The argument to timer_sleep() is expressed in timer ticks, not in milliseconds or any other unit.
There are TIMER_FREQ timer ticks per second, where TIMER_FREQ is a macro defined in
devices/timer.h. The default value is 100. We don't recommend changing this value, because any
change is likely to cause many of the tests to fail.
Separate functions timer_msleep(), timer_usleep(), and timer_nsleep() do exist for sleeping a
specific number of milliseconds, microseconds, or nanoseconds, respectively, but these will call
timer_sleep() automatically when necessary. You do not need to modify them.

#### Priority Scheduling
##### Exercise 1.2.1

Implement priority scheduling in Pintos. When a thread is added to the ready list that has a
higher priority than the currently running thread, the current thread should immediately yield
the processor to the new thread. Similarly, when threads are waiting for a lock, semaphore, or
condition variable, the highest priority waiting thread should be awakened first. A thread may
raise or lower its own priority at any time, but lowering its priority such that it no longer has the
highest priority must cause it to immediately yield the CPU.
Thread priorities range from PRI_MIN (0) to PRI_MAX (63). Lower numbers correspond to
lower priorities, so that priority 0 is the lowest priority and priority 63 is the highest. The initial
thread priority is passed as an argument to thread_create(). If there's no reason to choose
another priority, use PRI_DEFAULT (31). The PRI_ macros are defined in threads/thread.h,
and you should not change their values.
One issue with priority scheduling is "priority inversion". Consider high, medium, and low
priority threads H, M, and L, respectively. If H needs to wait for L (for instance, for a lock held
by L), and M is on the ready list, then H will never get the CPU because the low priority thread
will not get any CPU time. A partial fix for this problem is for H to "donate" its priority to L while
L is holding the lock, then recall the donation once L releases (and thus H acquires) the lock.

##### Exercise 1.2.2

Implement priority donation. You will need to account for all different situations in which
priority donation is required.
Be sure to handle multiple donations, in which multiple priorities are donated to a single thread.
You must also handle nested donation: if H is waiting on a lock that M holds and M is waiting on
a lock that L holds, then both M and L should be boosted to H's priority. If necessary, you may
impose a reasonable limit on depth of nested priority donation, such as 8 levels.
You must implement priority donation for locks. You need not implement priority donation for
the other Pintos synchronization constructs. You do need to implement priority scheduling in all
cases.

##### Exercise 1.2.3

Finally, implement the following functions that allow a thread to examine and modify its own
priority. Skeletons for these functions are provided in threads/thread.c.
Function: void thread_set_priority (int new_priority)
Sets the current thread's priority to new_priority. If the current thread no longer has the highest
priority, yields.
Function: int thread_get_priority (void)
Returns the current thread's priority. In the presence of priority donation, returns the higher
(donated) priority.
You need not provide any interface to allow a thread to directly modify other threads' priorities.


#### Advanced Scheduler
##### Exercise 1.3
Implement a multilevel feedback queue scheduler similar to the 4.4BSD scheduler to reduce the
average response time for running jobs on your system. See section B. 4.4BSD Scheduler, for
detailed requirements.
Like the priority scheduler, the advanced scheduler chooses the thread to run based on
priorities. However, the advanced scheduler does not do priority donation. Thus, we recommend
that you have the priority scheduler working, except possibly for priority donation, before you
start work on the advanced scheduler.
You must write your code to allow us to choose a scheduling algorithm policy at Pintos startup
time. By default, the priority scheduler must be active, but we must be able to choose the 4.4BSD
scheduler with the -mlfqs kernel option. Passing this option sets thread_mlfqs, declared in
threads/thread.h, to true when the options are parsed by parse_options(), which happens early
in main().
When the 4.4BSD scheduler is enabled, threads no longer directly control their own priorities.
The priority argument to thread_create() should be ignored, as well as any calls to
thread_set_priority(), and thread_get_priority() should return the thread's current priority as
set by the scheduler.
