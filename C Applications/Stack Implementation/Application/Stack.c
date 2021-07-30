/*****************************************************************************
* Module: Stack Module
* File Name: Stack.c
* Description: Source file for Stack Module
* Author: Mohamed Magdy
* Date: 11-July-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "Stack.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
/* head of stack */
node* gpstr_head = Null_Ptr;

/* error state */
EN_Error_t E_State = E_NOK;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Parameters (in): data to be pushed
* Parameters (out): Error Status
* Return value: EN_Error_t
* Description: pushes data to the top of the stack
************************************************************************************/
EN_Error_t push(uint8_t u8_data)
{
    /* 1. allocate node */
    node* new_node = (node*) malloc(sizeof(node));


    if(new_node != Null_Ptr)
    {
        /* 2. put in the data  */
        new_node->u8_data  = u8_data;

        /* 3. Make next of new node as current head */
        new_node->pstr_next = gpstr_head;

        /* 4. move the head to point to the new node (new head)*/
        gpstr_head  = new_node;
    }
    else
    {
        printf("\nNo Heap Space or Overflow\n");
    }
    return E_OK;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Poped (Pulled) Data
* Return value: uint8_t
* Description: pops out data from the top of the stack
************************************************************************************/
uint8_t pull(void)
{
  uint8_t u8_pop_data = Initial_Value;

  if(gpstr_head != Null_Ptr)
  {
    u8_pop_data = gpstr_head->u8_data;
    node* temp = gpstr_head;
    gpstr_head = gpstr_head->pstr_next;
    free(temp);
    return u8_pop_data;
  }
  else
    {
        return E_NOK;
        //printf("\nNo data to be poped\n");
    }
    return E_OK;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: EN_Error_t
* Description: prints the content of the stack
************************************************************************************/
EN_Error_t printStack(void)
{
    node* temp = gpstr_head;
    while (temp != Null_Ptr)
    {
        printf("%d\n", temp->u8_data);
        temp = temp->pstr_next;
    }
    if(temp == Null_Ptr)
    printf("\nStack Empty\n");

    return E_OK;
}


/*- APIs IMPLEMENTATION
-----------------------------------*/
/************************************************************************************
* Parameters (in): Expression
* Parameters (out): Balance State
* Return value: uint8_t*
* Description: checks whether the given expression has balancedParentheses or not
************************************************************************************/

uint8_t* balancedParentheses(uint8_t* expression)
{
    uint8_t u8_StringLen = strlen(expression);
    uint8_t u8_Counter = Initial_Value;

    if(expression[0] == ')' || expression[0] == '}' ||expression[0] == ']') return "Not Balanced";

    for(u8_Counter = 0; u8_Counter<u8_StringLen; u8_Counter++)
    {

        if(expression[u8_Counter] == '(' || expression[u8_Counter] == '{' || expression[u8_Counter] == '['
        || expression[u8_Counter] == ')' || expression[u8_Counter] == '}' || expression[u8_Counter] == ']')
        {

            if(expression[u8_Counter] == '(' || expression[u8_Counter] == '{' || expression[u8_Counter] == '[')
            {

                push(expression[u8_Counter]);

            }
            else
            {
                        if((expression[u8_Counter] == ')' && pull() == '(')  ||
                          (expression[u8_Counter] == '}' && pull() == '{')   ||
                          (expression[u8_Counter] == ']' && pull() == '['))
                        {

                        }
                        else
                        {
                            return "Not Balanced";
                        }
            }
        }

    }

    return "Balanced";

}
