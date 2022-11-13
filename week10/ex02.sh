export SOURCE_PATH=../week01/file.txt
export LINK_PATH=_ex2.txt
echo "Fedor Ivanov" > $SOURCE_PATH
link $SOURCE_PATH $LINK_PATH
export INODE=$(stat -c %i $SOURCE_PATH)
find ../ -inum $INODE > ex02.txt
find ../ -inum $INODE -exec rm {} \;
