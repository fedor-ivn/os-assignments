export FILENAME=_ex3.txt
export OUTPUT_FILENAME=ex03.txt

rm $FILENAME
echo "Fedor Ivanov" > $FILENAME

chmod a-x $FILENAME
stat --printf "Bits, after removing the execute permission from everyone: %A\n\n" $FILENAME > $OUTPUT_FILENAME
chmod uo+rwx $FILENAME
stat --printf "Bits, after granting all permissions to only the owner and others: %A\n\n" $FILENAME >> $OUTPUT_FILENAME
chmod g+rwx $FILENAME
stat --printf "Bits, after making group permissions equal to user permissions: %A\n\n" $FILENAME >> $OUTPUT_FILENAME

echo "Questions:
1. What does 660 mean?
    * owner and owner's group have read + write permissions.
        * r + w = 0b100 + 0b010 = 0b110 = 6.
2. What does 775 mean?
    * owner and owner's group have read + write + execute permissions.
        * r + w + x = 0b100 + 0b010 + 0b001 = 0b111 = 7.
    * everyone else has read + execute permission.
        * r + x = 0b100 + 0b001 = 0b101 = 5.
3. What does 777 mean?
    * owner, owner's group, and everyone else have read + write + execute
      permissions.
" >> $OUTPUT_FILENAME

