flex lexer.l
bison -d parser2.y -Wother -Wcounterexamples
g++ parser2.tab.c lex.yy.c 
./a.out

echo -e "\e[32mCOMPILED SUCCESSFULLY!\e[0m"
echo -e "\e[35mCheck log.txt for SymbolTable entry and log_error.txt for logs and errors\e[0m"