/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourne <jjourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 15:04:17 by jjourne           #+#    #+#             */
/*   Updated: 2018/06/29 11:00:43 by jjourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	lld_get_value(t_vm *vm, t_proc *proc, int reg_nb)
{
	int addr;

	addr = 0;
	addr = proc->op.pos_opcode + proc->op.ar[0];
	proc->reg[reg_nb] = 0;
	proc->reg[reg_nb] = (unsigned char)vm->ram[modulo(addr, MEM_SIZE)].mem;
	proc->reg[reg_nb] <<= 8;
	proc->reg[reg_nb] |= (unsigned char)vm->ram[modulo((addr + 1),
			MEM_SIZE)].mem;
	proc->reg[reg_nb] <<= 8;
	proc->reg[reg_nb] |= (unsigned char)vm->ram[modulo((addr + 2),
			MEM_SIZE)].mem;
	proc->reg[reg_nb] <<= 8;
	proc->reg[reg_nb] |= (unsigned char)vm->ram[modulo((addr + 3),
			MEM_SIZE)].mem;
}

void	lld(t_vm *vm, t_proc *proc)
{
	int		reg_nb;

	if (!check_params(&proc->op))
		return ;
	reg_nb = proc->op.ar[1];
	if (proc->op.ar_typ[0] == IND_CODE)
	{
		lld_get_value(vm, proc, reg_nb);
		proc->op.ar[0] = proc->reg[reg_nb];
	}
	else
		proc->reg[reg_nb] = proc->op.ar[0];
	proc->carry = (proc->reg[reg_nb] == 0) ? 1 : 0;
	if (0x4 & vm->verbosity)
	{
		show_operations(proc);
		ft_printf("\n");
	}
}
