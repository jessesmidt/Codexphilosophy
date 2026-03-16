/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heap.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsmidt <jsmidt@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/13 18:02:26 by jsmidt        #+#    #+#                 */
/*   Updated: 2026/03/16 17:39:22 by jsmidt        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

// parent is always smaller than its children (min-heap)
// parent of node i = (i - 1) / 2
// left child of i  = 2 * i + 1
// right child of i = 2 * i + 2

void	heap_push(t_dongle *dongle, t_waiter waiter)
{
	int	i;
	int	parent;
	
	dongle->queue[dongle->queue_size] = waiter;
	i = dongle->queue_size;
	dongle->queue_size++;
	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (dongle->queue[parent].priority <= dongle->queue[i].priority)
			break;
		t_waiter tmp = dongle->queue[parent];
		dongle->queue[parent] = dongle->queue[i];
		dongle->queue[i] = tmp;
		i = parent;
	}
}

void	heap_pop(t_dongle *dongle)
{
	int	i;
	int	left;
	int	right;
	int	smallest;
	
	dongle->queue_size--;
	dongle->queue[0] = dongle->queue[dongle->queue_size];
	i = 0;
	while (1)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		smallest = i;
		if (left < dongle->queue_size &&
			dongle->queue[left].priority < dongle->queue[smallest].priority)
			smallest = left;
		if (right < dongle->queue_size &&
			dongle->queue[right].priority < dongle->queue[smallest].priority)
			smallest = right;
		if (smallest == i)
			break;
		t_waiter tmp = dongle->queue[smallest];
		dongle->queue[smallest] = dongle->queue[i];
		dongle->queue[i] = tmp;
		i = smallest;
	}
}

void heap_remove(t_dongle *dongle, pthread_cond_t *cond)
{
	int	i;

	i = 0;
	while (i < dongle->queue_size)
	{
		if (dongle->queue[i].cond == cond)
		{
			dongle->queue_size--;
			dongle->queue[i] = dongle->queue[dongle->queue_size];
			int	left;
			int	right;
			int	smallest;
			while (1)
			{
				left = 2 * i + 1;
				right = 2 * i + 2;
				smallest = i;
				if (left < dongle->queue_size &&
					dongle->queue[left].priority < dongle->queue[smallest].priority)
					smallest = right;
				if (smallest == i)
					break;
				t_waiter	tmp;
				tmp = dongle->queue[smallest];
				dongle->queue[smallest] = dongle->queue[i];
				dongle->queue[i] = tmp;
				i = smallest;
			}
			return ; 
		}
		i++ ;
	}
}

t_waiter	heap_peek(t_dongle *dongle)
{
	return (dongle->queue[0]);
}