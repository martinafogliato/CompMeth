#ifdef OMP
#include <omp.h>
#endif

typedef struct {

  long long in;
  long long diff;
  long long max;
  int trials;
} time_stats_t;

static inline void start_meas(time_stats_t *ts) __attribute__((always_inline)); //forces the function to be inlined ("inlined functions are as fast as macros")
static inline void stop_meas(time_stats_t *ts) __attribute__((always_inline));

#if defined(__i386__)
static inline unsigned long long rdtsc_oai(void) __attribute__((always_inline));
static inline unsigned long long rdtsc_oai(void) {
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x)); //volatile on __asm__ forces the compiler to execute code as-is, otherwise it may think it can be removed or lifted out of a loop and cached
	//opcode of rdtsc is F 31
    return x;
}
#elif defined(__x86_64__)
static inline unsigned long long rdtsc_oai() __attribute__((always_inline));
static inline unsigned long long rdtsc_oai() { 
  unsigned long long a, d;
  __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d)); //volatile prevents caching, otherwise the compiler is allowed to cache the timestamp while we need a fresh one every time
  //a=low part; d=high part
  //need to force serialization as well?
 //The Time Stamp Counter (TSC) is a 64-bit register present on all x86 processors since the Pentium. It counts the number of cycles since reset. The instruction RDTSC returns the TSC in EDX:EAX
  return (d<<32) | a; //on 64bit machine, rdtsc clears the higher 32 bits of RAX, to compensate we need to shift left by 32 the higher part
}
#endif

static inline void start_meas(time_stats_t *ts) {

#ifdef OMP
  int tid;

  tid = omp_get_thread_num(); //get number of threads used in a parallel region
  if (tid==0)
#endif
    {
      ts->trials++;
      ts->in = rdtsc_oai();
    }
}

static inline void stop_meas(time_stats_t *ts) {

  long long out = rdtsc_oai();

#ifdef OMP
  int tid;
  tid = omp_get_thread_num();
  if (tid==0)
#endif
    {
      ts->diff += (out-ts->in);
      if ((out-ts->in) > ts->max)
	ts->max = out-ts->in;
      
    }
}

static inline void reset_meas(time_stats_t *ts) {

  ts->trials=0;
  ts->diff=0;
  ts->max=0;
}
