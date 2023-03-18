#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"

// To solve this assignment , i was helped by targeted questions by my private teacher

// struct defin AdptArray_
typedef struct AdptArray_
{
    int size;       // size of the array - (the largest position for the member entering the array + 1)
    int count_size; // size of the array allocated in memory 
    PElement *p; // a pointer to the location of the array in memory
    COPY_FUNC copy;
    DEL_FUNC del;
    PRINT_FUNC print;
} AdptArray;


/* initializes an empty array (with no members/ struct / elment) */
PAdptArray CreateAdptArray(COPY_FUNC copy_b, DEL_FUNC del_b, PRINT_FUNC print_b)
{
    PAdptArray ans = (PAdptArray)malloc(sizeof(AdptArray));
    if (ans == NULL) // if the ans is not booted successfully
    {
        return NULL;
    }
    // array initialization
    ans->p = NULL;
    ans->size = 0;
    ans->count_size = 0;
    ans->copy = copy_b;
    ans->del = del_b;
    ans->print = print_b;

    return ans;
}


/* free the memory of the object - including his organs 
delet the array */
void DeleteAdptArray(PAdptArray arr)
{
    if (arr == NULL) // if the array is empty 
    {
        
    }
    else
    {
        //go over the array and if the pointer of the array point on struct will delet the struct
        for (int i = 0; i < arr->size; i++) 
        {
            if (arr->p[i] != NULL)
            {
                arr->del(arr->p[i]);
            }
        }
    }
    //free the pointer of array && the array
    //that we defined in CreateAdptArray
    free(arr->p);
    free(arr);
}

/* get an index and a member and saves a copy of the member in the requested place
Free the old member if it exists */
Result SetAdptArrayAt(PAdptArray arr, int index, PElement new_p)
{
    // we chaking if the arr is empty or the index that we get is invalid 
    // in this case we retun FAIL
    if (arr == NULL || index < 0) 
    {
        return FAIL;
    }
    // we chaking if the index that we get is larger than our array then we will copy the array to memory large 
    // enough so that this reference will be valid
    if (index >= arr->count_size)
    {
        int temp = (index + 1) * 2; // we will increase(big) the array by mul of 2 , we add + 1 to case we get index = 0 and the count_size = 0 
        PElement *temp_p = (PElement *)realloc(arr->p, temp * sizeof(PElement));
        if (temp_p == NULL) // if the realloc is not booted successfully
        {
            return FAIL;
        }
        arr->p = temp_p;
        // in this part we initialize the new indexs of array that we get from the realloc
        for (int i = arr->count_size; i < temp ; i++) 
        {
            arr->p[i]=NULL;
        } 
        arr->count_size = temp;
    }
    if (arr->p[index] != NULL) // Free the old member if it exists 
    {
        arr->del(arr->p[index]);
    }
    arr->p[index] = arr->copy(new_p);//saves a copy of the new member in the requested place
    if (index > arr->size) //we update the size of the array just in case we get index bigger then size of array
    {
        arr->size = index + 1;
    }
    return SUCCESS;
}


/* get an index and return a copy of the member at this location*/
PElement GetAdptArrayAt(PAdptArray arr, int index)
{
    // first we chaking if the index is proper and if the arr is empty 
    if (index < 0 || index >= arr->size || arr == NULL)
    {
        return NULL;
    }
    // if you try to get index null 
    if (arr->p[index] == NULL)
    {
        return NULL;
    }
    return arr->copy(arr->p[index]);
}


/* Retuns the size of the array return (-1) if the array is not booted successfully*/
int GetAdptArraySize(PAdptArray arr)
{
    if (arr == NULL) // if the array is empty 
    {
        return -1;
    }
    return arr->size;
}


/*Prints the elements in the array */
void PrintDB(PAdptArray arr)
{
    if (arr == NULL) // if the array is empty 
    {
        
    }
    // go over the array and if the pointer of the array point on struct (like book / person)
    // we print the struct (element)
    for (int i = 0; i < arr->size; i++)
    {
        if (arr->p[i] != NULL)
        {
            arr->print(arr->p[i]);
        }
    }
}
