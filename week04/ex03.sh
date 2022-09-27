gcc ex03.c -o main
echo "Let us conduct an experiment for n = 3"
./main 3 &
for i in {1..3}
do
    pstree $$
    sleep 5
done
echo 
echo "Now, let us conduct it for n = 5"
./main 5 &
for i in {1..5}
do
    pstree $$
    sleep 5
done
