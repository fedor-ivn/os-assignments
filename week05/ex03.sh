gcc -Wall -pthread ex03.c -o /tmp/main;

> ex03.txt;
n=10000000;
for i in 1 2 4 10 100;
do
    echo "Computation in #$i threads" >> ex03.txt;
    (time /tmp/main $n $i) 2>> ex03.txt;
    echo "" >> ex03.txt;
done

