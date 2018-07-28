#include <stdlib.h>
#include <stdio.h>

/*

Author: Yann MARCOU
Alias: DarkSegment
Contact: darksegment17@gmail.com

This program provide a test benchmark based on time consumption 
for the libconcurrent.a I developped.

This source code is free.

*/

#ifdef CONCURRENT
#include "Concurrent.h"
#endif

#ifndef SIZE
#define SIZE 10
#endif

void isPrime(int * _In, int * _Out){
	int l_Value=*_In;
	if(l_Value%2==0)return;
	int i=0;
	for(i=3;i<l_Value;++i){
		if(l_Value%i==0){
			return;
		}
	}
	*_Out=*_In;
}

int main(){
	
	
	int l_In[SIZE];
	int l_Out[SIZE];
	
	unsigned long long i;
	for(i=0;i<SIZE;++i){
		l_In[i]=i;
		l_Out[i]=0;
	}
	
	#ifdef CONCURRENT
	
	ConcurrentParams l_Params;
	l_Params.input=l_In;
	l_Params.inputTypeSize=sizeof(int);
	l_Params.output=l_Out;
	l_Params.outputTypeSize=sizeof(int);
	l_Params.elementCount=SIZE;
	l_Params.function=(void (*)(void*,void*))&isPrime;
	l_Params.threadCount=5;
	
	if(doConcurrent(&l_Params)!=0){
		perror("");
	}
	
	#else
	
	for(i=0;i<SIZE;++i){
		isPrime(&l_In[i],&l_Out[i]);
	}
	
	#endif
	
	unsigned long long l_Count=0;
	for(i=0;i<SIZE;++i){
		if(l_Out[i]!=0)l_Count++;
	}

	printf("Results: %llu\n",l_Count);
	
	return 0;
}
