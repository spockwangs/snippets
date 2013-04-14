#!/bin/bash
#
# color.sh -- print all colors supported by terminals

for ((fore = 29; fore <= 37; fore += 1)) ; do
    if [ "$fore" -eq 29 ]; then
        # print header
        echo -n "   "
        for ((i = 40; i <= 47; i++)); do
            echo -n "   $i   "
        done
    else
        # print normal texts
        echo -n "${fore} "
        for ((back = 40; back <= 47; back += 1)) ; do
            echo -e -n "\e[${back};${fore}m Normal \e[0m"
        done
        echo
        # print bold texts
        echo -n "   "
        for ((back = 40; back <= 47; back += 1)) ; do
            echo -e -n "\e[01;${back};${fore}m  Bold  \e[0m"
        done
    fi
    echo
done
        
