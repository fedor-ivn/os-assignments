gcc -Wall -pthread ex04.c -o /tmp/main;

N=10000000;
FILE="ex04.txt";

> $FILE;
for i in 1 2 4 10 100;
do
    echo "Computation in #$i threads" >> $FILE;
    (time /tmp/main $N $i) 2>> $FILE;
    echo "" >> $FILE;
done

