#include <pthread.h>
#include <sys/types.h>
#include <errno.h>
#include "Concurrent.h"

/*

Author: Yann MARCOU
Alias: DarkSegment
Contact: darksegment17@gmail.com

The concurrent library is my own implementation in C langage of
an equivalent of QtConcurrent provided in Qt framework.

The source code of this library is free.

*/

#define NO_ERROR 0

static pthread_mutex_t workMutex=PTHREAD_MUTEX_INITIALIZER;

static uint64_t currentIndex;

static uint64_t next(){
	return currentIndex+=1;
}

static void work(const ConcurrentParams * const _Params){
	while(1){

		pthread_mutex_lock(&workMutex);
		uint64_t l_Index=next();
		pthread_mutex_unlock(&workMutex);
		
		if(l_Index>=_Params->elementCount)break;

		void * l_InputPtr=_Params->input+(l_Index*_Params->inputTypeSize);
		void * l_OutputPtr=_Params->output+(l_Index*_Params->outputTypeSize);
		
		_Params->function(l_InputPtr,l_OutputPtr);
		
	}
}

int doConcurrent(const ConcurrentParams * const _Params){
	
	errno=NO_ERROR;

	currentIndex=0;
	
	pthread_attr_t l_PthreadAttr;
	pthread_attr_init(&l_PthreadAttr);
	
	#ifdef _POSIX_THREAD_ATTR_STACKADDR
	if(_Params->stackSize>PTHREAD_STACK_MIN){
		pthread_attr_getstackaddr(&l_PthreadAttr,&_Params->stackSize);
	}
	#endif
	
	uint8_t i;
	pthread_t l_PthreadID[_Params->threadCount];
	for(i=0;i<_Params->threadCount;++i){
		pthread_create(&l_PthreadID[i],&l_PthreadAttr,(void*(*)(void*))&work,(void*)_Params);
	}
	
	for(i=0;i<_Params->threadCount;++i){
		pthread_join(l_PthreadID[i],NULL);
	}
	
	return errno;
}
