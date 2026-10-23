# 1. Skript mit absolutem Pfad erzeugen
echo -e "device XMC4700-2048\nspeed 4000\nconnect\nr\nh\nloadfile $(pwd)/build/xmclib-blinky.elf\nr\ng\nexit" > flash_final.jlink

# 2. Flashen ausführen
JLinkExe -if SWD -autoconnect 1 -CommanderScript flash_final.jlink

# 3. Aufräumen
rm flash_final.jlink
