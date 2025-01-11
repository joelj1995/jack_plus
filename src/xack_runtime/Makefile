parser: jack_vm.l jack_vm.y jack_vm.imp.c jack_vm.h chunk.c chunk.h common.h debug.c debug.h memory.h memory.c vm.h vm.c parser.c
	bison -d jack_vm.y
	flex -ojack_vm.lex.c jack_vm.l
	${CC} -o $@ jack_vm.tab.c jack_vm.lex.c jack_vm.imp.c chunk.c debug.c memory.c parser.c

host: jack_vm.l jack_vm.y jack_vm.imp.c jack_vm.h chunk.c chunk.h common.h debug.c debug.h memory.h memory.c vm.h vm.c host.c
	bison -d jack_vm.y
	flex -ojack_vm.lex.c jack_vm.l
	${CC} -o $@ jack_vm.tab.c jack_vm.lex.c jack_vm.imp.c chunk.c debug.c memory.c vm.c host.c