/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:53:25 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/07 13:54:02 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define TEXT 00
# define PIPE 01
# define COMMA_S 21
# define COMMA_D 22
# define RDOUT 31 //>
# define RDAP 32  //>>
# define RDIN 41  //<
# define RDHD 42  //<<
# define EXP 05

# define SUCCESS 0
# define FALSE	 0
# define TRUE	 1
# define ERROR 	-1
# define E_EXIT  1

# define CMD_NOT_FOUND	127
# define SYNTAX_ERROR	258

typedef struct s_env
{
	char			*key;
	char			*value;
	int				equal;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	int				type;
	int				open;//serveix per infile, outfile, here doc, apendd
	char			*wrd;
	struct s_token	*next;
}	t_token;

typedef struct s_process
{
	// int					fd_pipe[2];
	// int					fd_trm[2];
	int					fd_read_hd;
	char				**args; //lo que ejecutaremos
	t_token				*rd; // la lista de redirecciones
	char				**routes;//trobat PATH al envaiorment, fa un split del path :
	char				*ruta;//on s'executa l'args, del array routes
	struct s_process	*next;
}	t_process;

typedef struct s_all
{
	char		*line;
	int			size;
	char		**env;
	t_token		*token;
	t_process	*prcs;
	t_env		*w_env;
	int			num_process;
	int			pos_process;
}	t_all;

#endif