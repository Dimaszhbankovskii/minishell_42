#include "../includes/minishell.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

char	**malloc_two_array_char(int len)
{
	char	**array;
	int		i;

	array = (char **)malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i <= len)
		array[i++] = NULL;
	return (array);
}

void	free_two_array_char(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		free (array[i++]);
	free (array);
	array = NULL;
}

void	add_back_elem_two_array_char(char **array, char *elem, int len)
{
	int	i;

	i = 0;
	while (array && i < len && array[i])
		i++;
	if (i < len)
		array[i] = ft_strdup(elem);
	if (!array[i])
		end_program(ERROR_ADD_ELEM_TWO_ARR, 1, END1);
}

char	*find_str(char **array, char *str)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		if (!ft_strncmp(array[i], str, ft_strlen(str)))
			return (array[i]);
		i++;
	}
	return (NULL);
}

int	size_two_array_char(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

int	ft_is_num(char *str)
{
	long long  sum;
	int sign;

	sum = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = 0;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		if(!sign)
    {
      if ((sum * (-1) == -922337203685477580LL && *str > '8') || sum * (-1) < -922337203685477580LL)
        return (0);
    }
    else if ((sum == 922337203685477580LL && *str > '7') || (sum > 922337203685477580LL))
      return (0);
    sum = sum * 10 + (*str - '0');
    str++;
  }
  return (1);
}
