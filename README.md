# LCD_ESP32

Projet réalisé sur 3 jours de "parcours" avec comme objectif de faire une manette avec son pcb<br/>
Le projet aura eu plusieurs variations.<br/>

L'objectif qu'on c'était fixé initialement c'était de réalisé une machine qui permet de jouer à doom !<br/>
Cependant en utilisant les librairies :<br/>
https://github.com/nathalislight/NCAT/tree/main/NCAT_ESP32<br/>
https://github.com/ducalex/retro-go/tree/master<br/>

Aucune des deux n'a reussit a fonctioné malgrès les modifs.<br/>

Dans la phase la plus avancée du projet nous avions : <br/>

1ère bread board -<br/>
1 carte XIAO Seeed Studio ESP32 S3<br/>
1 module joystick arduino<br/>
2 module led rgb<br/>
1 button<br/>

2ème bread board -<br/>
1 carte ESP32 WROOM devkit<br/>
1 lecteur carte sd<br/>
1 2" pouce LCD Module<br/>

La première bread board pouvait communiquer avec la seconde en utilisant le protocole 
ESP-NOW et envoyer ses inputs pour que la deuxieme bread board puisse les affichers a l'écran

Le code utilise les libs : 
Adafruit_ST7735_and_ST7789_Library et 
Adafruit_GFX_Library
