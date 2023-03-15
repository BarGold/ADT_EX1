#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"

 typedef struct AdptArray_
 {
    int size; // size of array
    int count_size; // count how many elment 
    PElement* p; 
    COPY_FUNC copy;
    DEL_FUNC del;
    PRINT_FUNC print;
 }AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copy_b, DEL_FUNC del_b,PRINT_FUNC print_b){
    PAdptArray ans = (PAdptArray)malloc(sizeof(AdptArray)); 
    if(ans == NULL){
        return NULL;
    }
    ans->p = NULL;
    ans->size = 0 ;
    ans->count_size = 0;
    ans->copy = copy_b;
    ans->del = del_b;
    ans->print = print_b;

    return ans;
}

void DeleteAdptArray(PAdptArray arr){
    if (arr == NULL){
        printf ("Array is empty");
    }
    else{
        for (int i = 0; i < arr->size; i++)
        {
        if (arr->p[i] != NULL)
        {
            arr->del(arr->p[i]); 
        }
        }
    }
    free(arr->p);
    free(arr);
}


Result SetAdptArrayAt(PAdptArray arr, int index, PElement new_p)
{
    if(arr == NULL || index < 0){
        return FAIL;
    }
    if(index >= arr->count_size)
    {
        int temp = (index + 1) * 2;
        PElement *n_p = (PElement*)realloc(arr->p , temp * sizeof(PElement));
        if(n_p == NULL){
            return FAIL;
        }
        arr->p = n_p;
        arr->count_size = temp;
    }
    if(arr->p[index] != NULL)
    {
        arr->del(arr->p[index]);
    }
    arr->p[index] = arr->copy(new_p);
    if (index > arr->size )
    {
        arr->size = index + 1;
    }
    return SUCCESS;
    
}

PElement GetAdptArrayAt(PAdptArray arr, int index)
{
    if(index >= arr->size || index < 0 || arr == NULL){
        return NULL;
    }
    if(arr->p[index]== NULL){
        return NULL;
    }
    return arr->copy(arr->p[index]);
}

int GetAdptArraySize(PAdptArray arr){
    if(arr == NULL)
    {
        return -1;
    }
    return arr->size;
}

void PrintDB(PAdptArray arr)
{
    if(arr == NULL){
        printf ("Array is empty");
    }
    for (int i = 0; i < arr->size; i++)
    {
        if(arr->p[i] != NULL)
        {
            arr->print(arr->p[i]);
        }
    }
}

