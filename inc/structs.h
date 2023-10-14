#ifndef STRUCTS_H
# define STRUCTS_H


# define TEXT 00
# define PIPE 01
# define COMMA_S 21
# define COMMA_D 22
# define RDOUT 31
# define RDAP 32
# define RDIN 41
# define RDHD 42
# define EXP 05

typedef struct s_token
{
	int				type;
	char			*wrd;
	// int				fd;
	struct s_token	*next;
}	t_token;

typedef struct s_process
{
	int					pos_process;
	int					fd[2];
	pid_t				pid_prc;
	char				**args; //lo que ejecutaremos
	t_token				*rd; // la lista de tokens de la ejecució
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
	int			num_process;
}	t_all;

#endif