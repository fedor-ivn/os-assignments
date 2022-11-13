mkdir tmp
touch tmp/file1 tmp/file2
ln tmp/file1 tmp/link1
gcc ex04.c -o main -g -Wall -fsanitize=address -fsanitize=undefined -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow
./main | tee ex04.txt
rm -rf tmp
