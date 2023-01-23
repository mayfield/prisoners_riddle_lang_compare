build: prisoners_riddle

prisoners_riddle: prisoners_riddle.c
	gcc -O2 -Wall -Werror prisoners_riddle.c -o $@

prisoners_riddle_alt: prisoners_riddle.c
	gcc -O2 -Wall -Werror prisoners_riddle.c -o $@

run: prisoners_riddle
	time -v ./prisoners_riddle 3000
