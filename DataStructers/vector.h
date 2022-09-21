//
// Created by idang on 9/14/22.
//
#include<malloc.h>
#include <memory.h>
#include <assert.h>
#include <stdlib.h>
#include "iter.h"
#ifndef UNTITLED1_VECTOR_H
#define UNTITLED1_VECTOR_H

typedef  struct vector
{
    struct iter * it ;
    void  * arr;
    int size ;
    int len;
};

//iter

void * getIndexVector(size_t index , struct vector * vec){
    return vec->arr + vec->size * index  ;
}

void * iterNextVec( int  * current,struct vector * ln){

    return getIndexVector((*current)++ , ln);
}

int iterHasNextVec(int  * current,struct vector * ln){
    return *current  < ln->len;
}

void iterResetVec(struct linked * current,struct vector * ln){
    current = 0 ;
}




//functions
struct vector * createVector(int size ){
    struct vector * vec = (struct vector * )malloc(sizeof(struct vector));
    memset(vec , 0 , sizeof(struct vector));
    if(size <=0 ){
        fprintf(stderr , "cant create vector of size 0");
        exit(-1);
    }
    vec->size=size;
    vec->it= malloc(sizeof(struct iter));
    vec->it->current = malloc(sizeof(int));
    int * curi = vec->it->current ;
    *curi = 0 ;
    vec->it->next=iterNextVec;
    vec->it->reset=iterResetVec;
    vec->it->hasNext=iterHasNextVec;
    return  vec ;
}

void addVector(void * content , struct  vector *  vec ){
    vec->arr = realloc( vec->arr, vec->size * ++vec->len);
    memcpy( vec->arr + (vec->size ) * (vec -> len -1 ) ,content , vec-> size  );
}

int searchVector(void *  content , struct vector* vec){
    for(size_t index =0 ; index<vec->len;index++){
        if(!memcmp(content,vec->arr+index*vec->size,vec->size))
            return index;
    }
    return -1;

}

int deleteIndexVector(size_t index  ,struct vector * vec ){
    if(index < 0 || index >= vec->len|| vec -> len < 1 )
        return  -1 ;
    void * arrNew = malloc(vec->size * --vec->len);
    memcpy(arrNew , vec->arr , (index)* vec->size   );
    memcpy(arrNew +(index+1)*vec->size    ,arrNew + (index) * vec->size , (vec->len-index)*vec-> size  );
    free(vec->arr);
    vec->arr=arrNew ;
    return index;

}

int deleteVector(void * content  ,struct vector * vec ){
    return deleteIndexVector(searchVector(content,vec),vec);
}

void * deleteLastVector(struct vector * vec){
    deleteIndexVector(vec->len - 1 , vec ) ;

}

void * setIndexVector(size_t index , void * data , struct vector * vec){
    memcpy(vec->arr + index * vec->size , data,vec->size);
}



void * getLastVector(struct vector * vec ){
    return getIndexVector(vec->len-1 , vec);
}

void freeVector(struct vector * vec){
    if(vec->len > 0 ){
        free(vec->arr);
    }
    vec->arr = NULL;

}

void resetVector(struct vector * vec){
    freeVector(vec);
    vec->len=0;
}

void forEach(void (*callback)(void * x), struct vector * vec){
    for(int i = 0 ; i<vec->len ;i++)
        callback(vec->arr + i * vec->size );
}

void fornEach(void (*callback)(void * x), size_t len , struct vector * vec){
    if(len > vec->len){
        fprintf(stderr ,"cant loop , segmation error");
        exit(-1);
    }

    for(int i = 0 ; i<len ;i++)
        callback(vec->arr + i * vec->size );
}

void sortVector(struct vector * vec , int (* compare )(const void * a , const void * b )){
    qsort(vec->arr,vec->len , vec->size  , compare );
}

struct vector * cloneVector (struct vector * vec){
    struct vector * vecClone = (struct vector * )malloc(sizeof(struct vector));
    vecClone->arr= malloc(vec->len*vec->size);
    memcpy(vecClone->arr,vec->arr,vec->size*vec->len);
    vecClone->len=vec->len;
    vecClone->size=vec->size;
}
void addNVector(void * array , size_t len , struct vector * vec){
    vec->len+=len;
    vec->arr = realloc( vec->arr, vec->size * vec->len);
    memcpy( vec->arr + (vec->size ) * (vec -> len - len ) ,array , vec-> size * len  );
}




#endif //UNTITLED1_VECTOR_H
