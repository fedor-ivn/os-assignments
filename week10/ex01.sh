echo "Fedor Ivanov" > _ex1.txt
ln _ex1.txt _ex1_1.txt
ln _ex1.txt _ex1_2.txt
for FILENAME in ./_ex1*.txt; do
    stat -c %i $FILENAME | tee -a ex1.txt
done

