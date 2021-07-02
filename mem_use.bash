#/bin/bash


ps_mem() {
    free -b | grep "Mem" | tr -s " " "\012" | sed '4q;d'
}

ps_cmd() {
    free -b | grep "Mem" | tr -s " " "\012" | sed '4q;d'
}



while true; do
mem="$(ps_cmd)"
echo "1 $mem 1" >> mem.log 
gnuplot show_mem.plt
sleep 1
done

