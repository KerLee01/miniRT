/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:42:54 by kerlee            #+#    #+#             */
/*   Updated: 2026/01/15 18:38:42 by kerlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define STASH_SIZE 4096

typedef struct s_data
{
	char	stash[STASH_SIZE];
	bool	write_failed;
	bool	if_positive_space;
	bool	show_sign;
	bool	hex_hash;
	bool	left_align;
	bool	precision_set;
	char	width_padding;
	long	total_bytes;
	int		current_byte;
	int		width;
	int		precision;
	char	specifier;
}			t_data;

int			ft_printf(const char *format, ...);

void		c_handler(t_data *data, va_list *ap);
void		s_handler(t_data *data, va_list *ap);
void		p_handler(t_data *data, va_list *ap);
void		x_handler(t_data *data, va_list *ap);
void		u_handler(t_data *data, va_list *ap);
void		i_d_handler(t_data *data, va_list *ap);
void		precision_pad(t_data *data, long num);

void		check_flush_insert(t_data *data, char c);

bool		is_flag(char c, t_data *data);
bool		is_specifier(char s);
void		set_format_data(t_data *data);
int			add_number(const char **format);

#endif
