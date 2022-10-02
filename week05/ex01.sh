gcc -Wall publisher.c -o /tmp/publisher
gcc -Wall subscriber.c -o /tmp/subscriber

tmux new-session -d -s mysession
tmux send-keys -t mysession "/tmp/publisher $1" ENTER
for i in $(seq $1)
do
    tmux split-window -d -h "/tmp/subscriber"
done
tmux a
