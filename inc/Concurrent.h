#ifndef CONCURRENT_H
#define CONCURRENT_H

#include <stdlib.h>
#include <stdint.h>

/*

Author: Yann MARCOU
Alias: DarkSegment
Contact: darksegment17@gmail.com

The concurrent library is my own implementation in C langage of
an equivalent of QtConcurrent provided in Qt framework.

The source code of this library is free.

*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TConcurrentParams{
	void * input;
	size_t inputTypeSize;
	void * output;
	size_t outputTypeSize;
	uint64_t elementCount;
	void  (*function)(void*,void*);
	uint8_t threadCount;
	#ifdef _POSIX_THREAD_ATTR_STACKADDR
	size_t stackSize;
	#endif
} ConcurrentParams;

int doConcurrent(const ConcurrentParams * const);

#ifdef __cplusplus
}
#endif

#endif /* CONCURRENT_H */
