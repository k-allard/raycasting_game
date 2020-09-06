#include "cub.h"
void    init_check_struct(t_all *all)
{
	if (!(all->ch = (t_checks *)malloc(sizeof(t_checks))))
		error("Structure of checks MALLOC ERROR!");
	all->ch->r = 0;
	all->ch->n = 0;
	all->ch->s = 0;
	all->ch->w = 0;
	all->ch->e = 0;
	all->ch->sp = 0;
	all->ch->f = 0;
	all->ch->c = 0;
	all->ch->map = 0;
	all->ch->pos_player = 0;
}

void    init_param_struct(t_all *all)
{
	if (!(all->p = (t_param *)malloc(sizeof(t_param))))
		error("Structure of parametres MALLOC ERROR!");
}