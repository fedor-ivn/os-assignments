gcc ex03.c -o main -g -Wall -fsanitize=address -fsanitize=undefined -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow
./main
