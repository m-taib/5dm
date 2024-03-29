/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elemnts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:15:14 by mtaib             #+#    #+#             */
/*   Updated: 2023/10/03 17:39:29 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int	is_direction(char *str)
{
	if (!ft_strncmp("NO", str, -1))
		return (0);
	else if (!ft_strncmp("SO", str, -1))
		return (0);
	else if (!ft_strncmp("WE", str, -1))
		return (0);
	else if (!ft_strncmp("EA", str, -1))
		return (0);
	else if (!ft_strncmp("C", str, -1))
		return (0);
	else if (!ft_strncmp("F", str, -1))
		return (0);
	return (1);
}

int	check_duplicates(t_dirs *dirs, char *str)
{
	while (dirs)
	{
		if (!ft_strncmp(dirs->key, str, ft_strlen(str)))
			return (1);
		dirs = dirs->next;
	}
	return (0);
}

int	is_dirs(t_dirs *dirs, char *str)
{
	int	i;

	i = 0;
	while (dirs)
	{
		if (ft_strncmp("NO", str, ft_strlen(str)))
			return (1);
		else if (ft_strncmp("SO", str, ft_strlen(str)))
			return (1);
		else if (ft_strncmp("WE", str, ft_strlen(str)))
			return (1);
		else if (ft_strncmp("EA", str, ft_strlen(str)))
			return (1);
		i++;
		dirs = dirs->next;
	}
	if (i == 4)
		return (0);
	return (1);
}

int	check_params(char **params)
{
	if (is_direction(params[0]))
		return (print_error(0));
	if (params[0][0] == 'C' || params[0][0] == 'F')
		if (check_dirs(params[0][0], params[1]))
			return (1);
	if (params[0][0] != 'C' && params[0][0] != 'F')
		if (check_path(params[1]))
			return (1);
	if (check_duplicates(get_type()->directions, params[0]))
		return (print_error(3));
	get_type()->dirNbs++;
	lstadd_back(&get_type()->directions, lstnew(params[0], params[1]));
	return (0);
}

int	check_elements(char *str)
{
	int		i;
	char	**params;

	i = -1;
	if (str[0] == '\n')
		return (0);
	str = ft_strtrim(str, " \n\t");
	if (!str[0])
		return (print_error(0));
	while (str[++i])
		if (str[i] == ' ' || str[i] == '\t')
			break ;
	params = my_alloc(sizeof(char *) * 3);
	if (!params)
		return (1);
	params[0] = ft_substr(str, 0, i);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i] && params[0][0] != 'C' && params[0][0] != 'F')
		return (print_error(0));
	else if (!str[i] && (params[0][0] == 'C' || params[0][0] == 'F'))
		return (print_error(1));
	params[1] = ft_substr(str, i, ft_strlen(str));
	params[2] = NULL;
	return (check_params(params));
}
