/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_check_line_test.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 11:32:51 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/15 14:01:15 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	display_check_line_test(void)
{
	size_t	a;
	size_t	cases;
	int		result;
	char	*str;

	dprintf(1, "\n\nDISPLAY CHECK LINE PARSING\n\n");
	a = 0;
	cases = 42;
	str = NULL;
	result = 0;
	while (a <= cases)
	{
		dprintf(1, "\n");
		switch (a)
		{
			case 0:
				str = ft_strdup("bonjour"); break ;
			case 1:
				str = ft_strdup("cat | ouaf"); break ;
			case 2:
				str = ft_strdup("echo (salut)"); break ;
			case 3:
				str = ft_strdup(""); break ;
			case 4:
				str = ft_strdup("{errorlol"); break ;
			case 5:
				str = ft_strdup("error}not made yet"); break ;
			case 6:
				str = ft_strdup("[errorlol"); break ;
			case 7:
				str = ft_strdup("error]not made yet"); break ;
			case 8:
				str = ft_strdup("(errorlol"); break ;
			case 9:
				str = ft_strdup("error)not made yet"); break ;
			case 10:
				str = ft_strdup("this is a simple quote '"); break ;
			case 11:
				str = ft_strdup("another simple ' quote"); break ;
			case 12:
				str = ft_strdup("good 'test'"); break ;
			case 13:
				str = ft_strdup("\"good test\""); break ;
			case 14:
				str = ft_strdup("there is a semi colon ; here"); break ;
			case 15:
				str = ft_strdup("there is a backslash \\ here"); break ;
			case 16:
				str = ft_strdup("[{(\"'oskour'\")}]"); break ;
			case 17:
				str = ft_strdup("[[[aled]]]"); break ;
			case 18:
				str = ft_strdup("{{{sérieux?}}}"); break ;
			case 19:
				str = ft_strdup("(((la bonne blague)))"); break ;
			case 20:
				str = ft_strdup("syntax ([lol)]"); break ;
			case 21:
				str = ft_strdup("recursive 'test\"'\""); break ;
			case 22:
				str = ft_strdup("recursive ({test2)}"); break ;
			case 23:
				str = ft_strdup("lol && bonjour"); break ;
			case 24:
				str = ft_strdup("ouaf || miaou"); break ;
			case 25:
				str = ft_strdup("ouaf | miaou"); break ;
			case 26:
				str = ft_strdup("lol & bonjour"); break ;
			case 27:
				str = ft_strdup("this is a &| problem"); break ;
			case 28:
				str = ft_strdup("this is a |& syntax problem"); break ;
			case 29:
				str = ft_strdup("lol"); break ;
			case 30:
				str = ft_strdup("this one is not an error '&&'"); break ;
			case 31:
				str = ft_strdup("this one \"&&\" and this \"||\" should work"); break ;
			case 32:
				str = ft_strdup("is there a crash there \\\"\'ouaf\'\"\\"); break ;
			case 33:
				str = ft_strdup("((([[[{{{\"\"\"'''angry && || &| |& test'''\"\"\"}}}]]])))"); break ;
			case 34:
				str = ft_strdup("echo                     oskour"); break ;
			case 35:
				str = ft_strdup("echo '''''''''''ouaf'''''''''''"); break ;
			case 36:
				str = ft_strdup("echo \"\"\"\"\"ouaf\"\"\"\"\""); break ;
			case 37:
				str = ft_strdup("export SAMER=MDR"); break ;
			case 38:
				str = ft_strdup("Give up is okay, no need to be ashamed about it"); break ;
			case 39:
				str = ft_strdup("C'est un test qui doit être géré correctement"); break ;
			case 40:
				str = ft_strdup("test()()()()()()()()()test[][][][][][][][]test{}{}{}{}{}{}{}{}test""""""""""test''''''test"); break ;
			case 41:
				str = ft_strdup("(){}[]oskour\"\"''"); break ;
			case 42:
				str = ft_strdup("export OUAF=ouaf"); break ;
		}
		dprintf(1, "\nCHECKLINE %zu/%zu | size = %zu\nstr :%s\n", a, cases, ft_strlen(str), str);
		result = mini_check_line(str);
		dprintf(1, "result = %d\n", result);
		free (str);
		a++;
	}
}
