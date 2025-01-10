parser: jack_vm.l jack_vm.y jack_vm.imp.c jack_vm.h
	bison -d jack_vm.y
	flex -ojack_vm.lex.c jack_vm.l
	${CC} -o $@ jack_vm.tab.c jack_vm.lex.c jack_vm.imp.c