#include "corewar.h"

static void	st_set_value(t_vm *vm, t_proc *proc)//si le segond param est in IND, on stock la val la-bas
{
	unsigned int addr;

	addr = (proc->op.pos_opcode + (proc->op.ar[1] % IDX_MOD));

	addr = modulo(addr, MEM_SIZE);
	vm->ram[addr].mem = proc->reg[proc->op.ar[0]] >> 24;

	addr = modulo(addr + 1, MEM_SIZE);
	vm->ram[addr].mem = proc->reg[proc->op.ar[0]] >> 16;

	addr = modulo(addr + 1, MEM_SIZE);
	vm->ram[addr].mem = proc->reg[proc->op.ar[0]] >> 8;

	addr = modulo(addr + 1, MEM_SIZE);
	vm->ram[addr].mem = proc->reg[proc->op.ar[0]];
}

void	st(t_vm *vm, t_proc *proc)
{
	if (!check_params(&proc->op))
		return ;
	//test si arg0 est pas un registre?
	//

	if (proc->op.ar_typ[1] == REG_CODE)//si c'est un registre,
	{
		if (proc->op.ar[1] >= 1 && proc->op.ar[1] <= 16)
			//le reg de l'arg 1 = reg de l'arg 2
			proc->reg[proc->op.ar[1]] = proc->reg[proc->op.ar[0]];//on a le droit
	}
	else
		st_set_value(vm, proc);
	if (0x4 & vm->verbosity)
	{
		show_operations(proc);
		printf("\n");//
	}
}
