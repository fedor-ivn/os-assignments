gcc $1 -o main -g -Wall -fsanitize=address -fsanitize=undefined -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow
./main
# rm ./main
