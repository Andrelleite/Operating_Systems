/************************************************************************************
*
*		META 2 - SISTEMAS OPERATIVOS , 2018-2019
*
*		AUTORES: André Leite e Sara Inácio
*		DATA: 09/12/2018
*		LANGUAGE: C
*		COMPILE AS: no compile
*   FILE: queue.c
*
*************************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "queue.h"

//inicializa a queue
q_node init_q()
{
    q_node node = (q_node)malloc(sizeof(Queue));

    if(node != NULL)
    {
        node->n = 0;
        node->next = NULL;
        node->order = NULL;
    }
    else
    {
        exit(-1);
    }

    return node;
}

//insere elemento na queue
void insert_q(Order *new_node,q_node lista )
{
    q_node node = (q_node)malloc(sizeof(Queue));
    q_node post = lista->next;
    q_node ante = lista;
    node->order = new_node;

    if(lista->next == NULL)
    {
        node->next = lista->next;
        lista->next = node;
        lista->n++;
    }
    else
    {
        while(post != NULL)
        {
            ante = post;
            post = post->next;
        }

        ante->next = node;
        node->next = post;
        lista->n++;
    }
}


//imprime elemento da queue
void print_q(q_node lista)
{
    q_node act = lista->next;

    if(lista->next != NULL)
    {
      while(act != NULL)
      {
          printf("ORDER ID %d | PRODUCTS: %s | QUANTITY: %d\n",act->order->id,act->order->prod_name,act->order->quantity);
          act = act->next;
      }
    }
    else
    {
      printf("No orders.\n");
    }
}

//remove elemento da queue
void pop_node(q_node node, q_node lista)
{
    q_node act = lista;
    q_node post = lista->next;
    int found = 0;

    if(post != NULL)
    {
        while(found == 0 && post != NULL)
        {
            if(post->order->id == node->order->id)
            {
                found = 1;
                act->next = post->next;
                node->next = NULL;
            }

            act = post;
            post = post->next;
        }
    }
    lista->n--;
}

//procura e devolve um elemento da queue
q_node search_order(int id, q_node lista)
{
    q_node node = (q_node)malloc(sizeof(Queue));
    q_node act = lista;
    int found = 0;

    while(act != NULL && found == 0)
    {
        act = act->next;

        if(act->order->id == id)
        {
            found = 1;
            node = act;
        }
    }

    return node;
}

//mete elemento no final da queue
void delay_order(int id, q_node lista)
{
    q_node node = search_order(id, lista);
    pop_node(node,lista);
    insert_q(node->order,lista);
    free(node);
    print_q(lista);
}
