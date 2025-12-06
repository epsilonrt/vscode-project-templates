# Instructions pour ajouter le support des cartes ESP32-C6 à PlatformIO

PlatfromIO ne supporte pas nativement les cartes ESP32-C6. 
En effet, le framework ESP32 de PlatformIO utilise un core Arduino en version 2.
Pour utiliser les cartes ESP32-C6 avec PlatformIO, et donc le Zigbee, il est nécessaire d'avoir un core Arduino en version 3.
Dans L'IDE Arduino, cela est maintenant pris en charge nativement via la plateforme [`espressif32`](https://espressif.github.io/arduino-esp32/package_esp32_index.json), mais pas encore dans PlatformIO.

## Utilisation de la plateforme ESPressif32 du projet PioArduino

Pour utiliser les cartes ESP32-C6 avec PlatformIO, il est nécessaire d'utiliser la plateforme `espressif32` du projet [PioArduino](https://github.com/pioarduino).

Il suffit pour cela de modifier le fichier `platformio.ini` de votre projet en remplaçant la ligne :

```ini
platform = espressif32
```
par :

```ini  
platform = https://github.com/pioarduino/platform-espressif32.git#55.03.34
```

> Si vous avez déjà utilisé PlatformIO avec des cartes ESP32, il sera nécessaire de supprimer le dossier `~/.platformio/platforms/espressif32` (ou sous Windows `C:\Users\VotreNom\.platformio\platforms\espressif32`) ainsi que le dossier `~/.platformio/packages/framework-arduinoespressif32` (ou sous Windows `C:\Users\VotreNom\.platformio\packages\framework-arduinoespressif32`) avant de poursuivre (il faut fermer VSCode avant de supprimer ces dossiers).

Le sous-dossier Blink contient un projet PlatformIO pour tester l'installation.

Après avoir installé l'extension PlatformIO dans VSCode, ouvrez le dossier Blink avec PlatformIO et cliquez sur "Build" (l'icône avec une coche à côté de l'icône en forme de maison dans la barre du bas) pour compiler le projet:

![Compilation réussie](images/build_xiao.png)

La première compilation peut prendre un certain temps car PlatformIO va télécharger et configurer les nouvelles plateformes et frameworks. 

![Téléchargement des plateformes](images/platform_installing.png)

**REMARQUE IMPORTANTE**
Lors de l'ouverture du projet dans PlatformIO, il est possible que vous receviez un avertissement vous proposant l'installation de l'extension PioArduino. **Il est important de ne pas installer cette extension**, car elle n'est pas nécessaire et pourrait interférer avec le fonctionnement de PlatformIO. La petite roue dentée à côté de l'avertissement permet de masquer ce message à l'avenir.

![Avertissement PlatformIO](images/pioarduino_warning.png)

Par défaut, le projet est configuré pour la carte _Seed XIAO ESP32-C6_ qui est prise en charge par la plateforme `espressif32` du projet PioArduino. Par contre, les cartes _Waveshare ESP32-C6 Zero_ et _MakerGO ESP32-C6 SuperMini_ ne sont pas encore prises en charge nativement. Il est nécessaire d'appliquer des patchs pour ajouter le support de ces cartes.

## Ajout de la prise en charge des cartes Waveshare ESP32-C6 Zero et MakerGO ESP32-C6 SuperMini

Le sous-dossier `esp32c6-cn` contient les patchs nécessaires pour ajouter le support des cartes _Waveshare ESP32-C6 Zero_ et _MakerGO ESP32-C6 SuperMini_. Il est nécessaire d'installer Git Bash (inclus avec [Git pour Windows](https://git-scm.com/download/win)) pour appliquer les patchs.

Voilà la procédure à suivre pour appliquer les patchs :

- Ouvrir le dossier `~/.platformio` ou sous Windows  `C:\Users\VotreNom\.platformio`  
- Copier le dossier `esp32c6-cn` (contenant les patchs) dans le dossier `.platformio`.  
- Avant d'appliquer les patchs, il est faut vérifier que le dossier `.platformio/platforms`  contient bien **un seul** dossier `espressif32`  et que le dossier `.platformio/packages` contient bien **un seul** dossier `framework-arduinoespressif32`. Si ce n'est pas le cas, fermer VSCode et supprimer toues les dossiers `espressif32` et `framework-arduinoespressif32` présents dans ces dossiers avant de relancer VSCode et de recompiler le projet pour que PlatformIO télécharge les bonnes versions.   
- Faire un clic droit **dans** le dossier `.platformio` et sélectionner `Git Bash Here` pour ouvrir un terminal **Git Bash**.  
- Appliquer les patchs afin d'ajouter le support des cartes ESP32-C6 à l'aide de la commande suivante :  

```bash
patch -p0 < esp32c6-cn/patches/espressif32.patch
patch -p0 < esp32c6-cn/patches/framework-arduinoespressif32.patch
```

![Application des patchs](images/gitbash_patch.png)

**Notes importantes**  
- Les patchs ajoutent ou modifient uniquement les lignes nécessaires, ils ne remplacent pas les fichiers entiers.  
- Si une erreur apparaît lors de l’application (Hunk FAILED), cela signifie que la version installée a évolué. Dans ce cas, il faudra régénérer les patchs à partir des nouvelles versions originales.
- Les patchs doivent toujours être stockés en dehors des dossiers modifiés (bonne pratique).


Une fois les patchs appliqués, il est possible de configurer le projet PlatformIO pour utiliser les cartes _Waveshare ESP32-C6 Zero_ ou _MakerGO ESP32-C6 SuperMini_ en modifiant basculant de configuration dans la barre inférieure de PlatformIO, on peut alors compiler le projet pour ces cartes:  

![Compilation MakerGO ESP32-C6 SuperMini](images/build_makergo.png)

On peut alors sélectionner l'onglet du moniteur série pour voir les messages de debug:

![Moniteur série](images/serial_monitor.png)

_A noter, que ces cartes ne sont pas non plus supportées nativement par l'IDE Arduino, mais il est possible d'installer le package [esp32c6-cn-package](https://github.com/epsilonrt/esp32c6-cn-package)._