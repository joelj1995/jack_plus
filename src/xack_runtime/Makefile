parser: jack_vm.l jack_vm.y jack_vm.imp.c jack_vm.h compiler.c compiler.h chunk.c chunk.h common.h debug.c debug.h memory.h memory.c vm.h vm.c xack_native.c xack_native.h parser.c
	bison -d jack_vm.y
	flex -ojack_vm.lex.c jack_vm.l
	${CC} -o $@ jack_vm.tab.c jack_vm.lex.c jack_vm.imp.c chunk.c compiler.c debug.c memory.c vm.c xack_native.c parser.c

host: jack_vm.l jack_vm.y jack_vm.imp.c jack_vm.h compiler.c chunk.c chunk.h common.h debug.c debug.h memory.h memory.c vm.h vm.c xack_native.c xack_native.h host.c
	bison -d jack_vm.y
	flex -ojack_vm.lex.c jack_vm.l
	${CC} -DDEBUG_LOGGING -o $@ jack_vm.tab.c jack_vm.lex.c jack_vm.imp.c compiler.c chunk.c debug.c memory.c vm.c xack_native.c host.c