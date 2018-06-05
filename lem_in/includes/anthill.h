#ifndef ANTHILL_H
# define ANTHILL_H

typedef struct s_path	t_path;
typedef struct s_room	t_room;
typedef struct s_rooms	t_rooms;
typedef struct s_ant	t_ant;
typedef struct s_env	t_env;
typedef struct s_link	t_link;

struct 			s_env
{
	t_room			*start;
	t_room			*end;
	t_path			*fastway;
	t_parsed_room	*parsed_room;
	t_parsed_link	*parsed_link;
	int				nb_rooms;
	int				nb_ants;
	t_ant			**colony;
};

struct			s_room
{
	char			id[256];
	int				x;
	int				y;
	t_ant			*ant;
	t_link			*link;
};

struct			s_parsed_room
{
	t_room			*room;
	t_parsed_room	*prev;
	t_parsed_room	*next;
};

struct			s_link
{
	t_room			*linked_room;
	t_link			*prev;
	t_link			*next;
};

struct			s_parsed_link
{
	t_room			*room1;
	t_room			*room2;
	t_parsed_link	*prev;
	t_parsed_link	*next;
};

struct			s_ant
{
	int				n;
	t_path			*path;
};

struct			s_path
{
	int				len;
	t_room			*prev;
	t_room			*current;
	t_room			*next;
};

#endif