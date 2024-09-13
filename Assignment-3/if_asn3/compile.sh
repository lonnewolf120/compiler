flex lexer.l
bison -d parser.y
g++ -std=c++11 -o if_asn3 parser.tab.c lex.yy.c -lfl
./if_asn3 < input.txt

echo -e "\e[32mCOMPILED SUCCESSFULLY!\e[0m"
echo -e "\e[35mCheck log.txt for SymbolTable entry and log_error.txt for logs and errors\e[0m"