# Tutoriel : Développer en C/C++ sous Windows avec VSCode, MSYS2, CMake et Git

## 1. Installer Visual Studio Code

1. Rendez-vous sur la page officielle de téléchargement :  
   [https://code.visualstudio.com/](https://code.visualstudio.com/)
2. Téléchargez la version Windows et installez-la en suivant les instructions.

---

## 2. Installer MSYS2

1. Accédez au site officiel :  
   [https://www.msys2.org/](https://www.msys2.org/)
2. Téléchargez l'installateur adapté à votre architecture (x86_64 pour la plupart des PC récents).
3. Lancez l’installateur et suivez les instructions.
4. Ouvrez le terminal MSYS2 (`MSYS2 MinGW 64-bit` recommandé).

---

## 3. Mettre à jour MSYS2 et installer les outils nécessaires

Dans le terminal MSYS2, exécutez les commandes suivantes :

```sh
# Mettre à jour le système
pacman -Syu
# Fermez le terminal si demandé, puis relancez-le et continuez :
pacman -Su

# Installer les outils de développement C/C++, CMake et Git
pacman -S --needed base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake git
```

---

## 4. Ajouter MSYS2 au PATH pour VSCode

Pour que VSCode détecte les outils MSYS2, ajoutez le chemin `C:\msys64\mingw64\bin` à la variable d’environnement `PATH` de Windows.

1. Ouvrez les Paramètres système avancés → Variables d’environnement.
2. Modifiez la variable `Path` de votre utilisateur.
3. Ajoutez :  
   `C:\msys64\mingw64\bin`

---


## 5. Installer les extensions VSCode recommandées

Ouvrez VSCode et installez les extensions suivantes :

- **C/C++ Extension Pack** (Microsoft, recommandé)  
  [Lien direct](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
    - Ce pack inclut : C/C++, CMake Tools, CMake, Clang-Format, Clangd, Include Autocomplete, etc.
- **Project Templates** (pour créer des projets rapidement)  
  [Lien direct](https://marketplace.visualstudio.com/items?itemName=cantonios.project-templates)
- **GitLens** (optionnel, pour Git)  
  [Lien direct](https://marketplace.visualstudio.com/items?itemName=eamodio.gitlens)

---

## 6. Configurer VSCode pour MSYS2

Dans VSCode, ouvrez les paramètres (`Ctrl+,`) et recherchez `terminal.integrated.profiles.windows`. Ajoutez un profil pour MSYS2 :

```json
"terminal.integrated.profiles.windows": {
  "MSYS2 MinGW64": {
    "path": "C:\\msys64\\usr\\bin\\bash.exe",
    "args": ["--login", "-i"],
    "icon": "terminal-bash"
  }
}
```

Vous pourrez alors ouvrir un terminal MSYS2 directement dans VSCode.

---

## 7. Compiler un projet C/C++ avec CMake

1. Ouvrez votre dossier de projet dans VSCode.
2. Ouvrez un terminal MSYS2 intégré.
3. Configurez et compilez avec CMake :

```sh
mkdir build
cd build
cmake ..
make
```

---

## 8. Utiliser Git

Dans le terminal MSYS2 ou via l’interface VSCode, vous pouvez utiliser Git :

```sh
git clone <url-du-repo>
git status
git add .
git commit -m "Votre message"
git push
```

---

## 9. Ressources

- [Documentation officielle MSYS2](https://www.msys2.org/docs/)
- [Documentation CMake](https://cmake.org/cmake/help/latest/)
- [Documentation VSCode C/C++](https://code.visualstudio.com/docs/languages/cpp)

---

N’hésitez pas à demander si vous souhaitez des captures d’écran ou des précisions sur une étape !
