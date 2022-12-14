/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation_for_big_sort.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 01:26:25 by numussan          #+#    #+#             */
/*   Updated: 2022/11/08 10:25:11 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	final_sorting(t_stack **a)
{
	t_stack	*tmp;
	int		min;
	int		max;
	int		med;
	int		steps;

	tmp = *a;
	find_min_max_med(a, &min, &max, &med);
	steps = 0;
	while (tmp->nbr != min)
	{
		steps++;
		tmp = tmp->next;
	}
	if (steps <= op_stack_size(a) / 2)
	{
		while (steps-- > 0)
			ra(a, 1);
	}
	else
	{
		while (steps++ < op_stack_size(a))
			rra(a, 1);
	}
}

void	determine_position(t_stack **head, int *arr)
{
	int		i;
	t_stack	*tmp;

	tmp = *head;
	while (tmp)
	{
		i = 0;
		while (arr[i] != tmp->nbr)
			i++;
		tmp->pos = i;
		tmp = tmp->next;
	}
}

int	*insertion_sort_array(t_stack **a, int *arr)
{
	int	i;
	int	key;
	int	j;

	i = 1;
	while (i < op_stack_size(a))
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j -= 1;
		}
		arr[j + 1] = key;
		i++;
	}
	return (arr);
}

int	*fill_array(t_stack **a, int *arr)
{
	int		i;
	t_stack	*tmp;

	i = 0;
	tmp = *a;
	while (i < op_stack_size(a))
	{
		arr[i++] = tmp->nbr;
		tmp = tmp->next;
	}
	return (arr);
}

void	find_min_max_med(t_stack **a, int *min, int *max, int *med)
{
	int	*arr;
	int	size;

	size = op_stack_size(a);
	arr = malloc(sizeof(int) * size);
	if (!arr)
		ft_error("<<<<< ERROR! Memmory didn`t allocate! >>>>>\n");
	arr = insertion_sort_array(a, fill_array(a, arr));
	*min = arr[0];
	*max = arr[size - 1];
	*med = arr[size / 2];
	determine_position(a, arr);
	free(arr);
	arr = NULL;
}

void	transfer_to_stack_b(t_stack **a, t_stack **b)
{
	int		min;
	int		max;
	int		med;
	int		size;

	size = op_stack_size(a);
	find_min_max_med(a, &min, &max, &med);
	while (size > 3)
	{
		if ((*a)->nbr == min || (*a)->nbr == max || (*a)->nbr == med)
			ra(a, 1);
		else
		{
			pb(a, b);
			size--;
		}
	}
}

void	preparation_for_big_sorting(t_stack **a, t_stack **b)
{
	if (op_check_sorted_or_presorted(a) == 1)
	{
		// ft_printf("not presort!\n"); // remove it before submit
		transfer_to_stack_b(a, b);
		presort_3(a);
		while (*b)
			transfer_to_stack_a(a, b);
	}
	ft_free_stack(b);
	if (op_check_sorted_or_presorted(a) == 2)
	{
		// ft_printf("presort!\n"); // remove it before submit
		final_sorting(a);
	}
// 	if (!op_check_sorted_or_presorted(a))
// 		ft_printf("NUMBERS SORTED!!!\n"); // remove it before submit
}
