stage1exe: stack.c driver.c lexer.c parser.c
	gcc -g -o stage1exe stack.c driver.c lexer.c parser.c 