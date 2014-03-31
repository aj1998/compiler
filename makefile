stage1exe: stack.c driver.c lexer.c parser.c
	gcc -o stage1exe stack.c driver.c lexer.c parser.c 