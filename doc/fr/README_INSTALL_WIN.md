# Tutoriel : Développer en C/C++ sous Windows avec VSCode, MSYS2, CMake et Git

## 1. Installer Visual Studio Code

1. Rendez-vous sur la page officielle de téléchargement :  
   [https://code.visualstudio.com/](https://code.visualstudio.com/)
2. Téléchargez la version Windows et installez-la en suivant les instructions. ** Bien choisir "User Installer" pour une installation sans droits administrateur. **

---

## 2. Installer MSYS2

1. Accédez au site officiel :  
   [https://www.msys2.org/](https://www.msys2.org/)
2. Téléchargez l'installateur adapté à votre architecture (x86_64 pour la plupart des PC récents).
3. MSYS2 doit être installé dans `C:\Info\msys64`. Lancez l’installateur et suivez les instructions.
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

Pour que VSCode détecte les outils MSYS2, ajoutez le chemin `C:\Info\msys64\mingw64\bin` à la variable d’environnement `PATH` de Windows.

1. Ouvrez les Paramètres système avancés → Variables d’environnement.
2. Modifiez la variable `Path` de votre utilisateur.
3. Ajoutez :  
   `C:\Info\msys64\mingw64\bin`

---



## 5. Installer les extensions VSCode recommandées

Ouvrez VSCode et installez les extensions suivantes :

- **C/C++ Extension Pack** (Microsoft, recommandé)  
  [Lien direct](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
    - Ce pack inclut : C/C++, CMake Tools, CMake, Clang-Format, Clangd, Include Autocomplete, etc.
- **Project Templates** (pour créer des projets rapidement)  
  [Lien direct](https://marketplace.visualstudio.com/items?itemName=cantonios.project-templates)
- **Git History** (pour visualiser l'historique Git)  
  [Lien direct](https://marketplace.visualstudio.com/items?itemName=donjayamanne.githistory)
- **French Language Pack for Visual Studio Code** (pour une interface en français)  
  [Lien direct](https://marketplace.visualstudio.com/items?itemName=MS-CEINTL.vscode-language-pack-fr)

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


## 7. Créer, compiler et déboguer un projet d'exemple avec Project Templates

### 7.1. Cloner le dépôt de templates

Dans VSCode, ouvrez la palette de commandes (`Ctrl+Shift+P`) et tapez `Git: Clone`. Collez l'URL suivante :

```
https://github.com/epsilonrt/vscode-project-templates.git
```

Choisissez un dossier de destination sur votre disque. Ouvrez ensuite le dossier cloné dans VSCode si ce n'est pas déjà fait.

### 7.2. Paramétrer l'extension Project Templates

1. Ouvrez les paramètres de VSCode (`Ctrl+,`).
2. Recherchez `Project Templates: Templates Root`.
3. Indiquez le chemin du dossier cloné (par exemple : `C:\Users\<votre-nom>\vscode-project-templates`).

### 7.3. Créer un nouveau projet à partir du modèle 'MSys2 CMake C Project'

1. Ouvrez la palette de commandes (`Ctrl+Shift+P`).
2. Tapez `Project Templates: Create Project from Template`.
3. Sélectionnez le modèle **MSys2 CMake C Project**.
4. Choisissez un dossier de destination pour votre nouveau projet.
5. Ouvrez ce dossier dans VSCode.


### 7.4. Configurer et compiler le projet avec CMake Tools

1. Ouvrez le dossier du projet dans VSCode.
2. En bas à gauche de la barre de statut, cliquez sur le kit de compilation (souvent affiché comme "No Kit Selected" ou similaire).
3. Sélectionnez le kit correspondant à MSYS2, par exemple :
  - `GCC 64-bit for MSYS2` ou `MinGW GCC for MSYS2` (le nom peut varier selon l'installation).
4. Cliquez sur l'icône CMake (ou utilisez la commande `CMake: Configure`) pour configurer le projet.
5. Cliquez sur l'icône "Build" (marteau) dans la barre de statut pour compiler le projet.

### 7.5. Exécuter le programme avec CMake Tools

1. Cliquez sur l'icône "Play" (triangle) dans la barre de statut de VSCode pour exécuter le binaire compilé.
2. La sortie du programme s'affichera dans le terminal intégré ou dans le panneau de sortie CMake Tools.


### 7.6. Déboguer le projet avec la configuration fournie

Le modèle de projet contient déjà un fichier `.vscode/launch.json` avec une configuration de débogage nommée **Debug CMake Project (MSYS2 ucrt64)**.

Pour lancer le débogage dans VSCode :

1. Assurez-vous que le projet a bien été compilé (voir étape précédente).
2. Cliquez sur l’icône "Exécuter et déboguer" dans la barre latérale gauche de VSCode (ou utilisez `Ctrl+Shift+D`).
3. Dans le menu déroulant en haut, sélectionnez la configuration **Debug CMake Project (MSYS2 ucrt64)**.
4. Cliquez sur le bouton vert "Démarrer le débogage" (ou appuyez sur `F5`).
5. Le débogueur s’attachera automatiquement à l’exécutable généré par CMake, en utilisant gdb fourni par MSYS2.


Vous pouvez placer des points d’arrêt, inspecter les variables, et utiliser toutes les fonctionnalités de débogage de VSCode.

---

## 8. Profiter de GitHub et GitHub Copilot dans VSCode

### 8.1. Créer un compte GitHub étudiant

1. Rendez-vous sur [https://github.com/](https://github.com/) et inscrivez-vous avec votre adresse mail étudiante.
2. (Optionnel mais recommandé) Demandez le pack GitHub Student pour bénéficier d’avantages gratuits : [https://education.github.com/pack](https://education.github.com/pack)

### 8.2. Installer et activer GitHub Copilot dans VSCode

1. Ouvrez VSCode, allez dans l’onglet Extensions (`Ctrl+Shift+X`).
2. Recherchez **GitHub Copilot** et installez l’extension officielle ([lien direct](https://marketplace.visualstudio.com/items?itemName=GitHub.copilot)).
3. Connectez-vous à GitHub lorsque cela est demandé (une fenêtre de connexion s’ouvrira automatiquement).

### 8.3. Connecter VSCode à votre compte GitHub

1. Cliquez sur l’icône de compte en bas à gauche de VSCode, puis sur "Se connecter à GitHub".
2. Suivez les instructions pour autoriser VSCode à accéder à votre compte GitHub.

### 8.4. Créer un dépôt GitHub pour vos TP

1. Dans VSCode, ouvrez le dossier de votre projet (par exemple, le projet créé à l’étape 7).
2. Ouvrez l’onglet Source Control (icône branche Git à gauche ou `Ctrl+Shift+G`).
3. Cliquez sur "Publier sur GitHub" ou "Publish to GitHub".
4. Donnez un nom à votre dépôt, par exemple `vscode-labs`.
5. Choisissez la visibilité (privé ou public) puis validez.

### 8.5. Versionner et pousser votre projet sur GitHub

1. Dans l’onglet Source Control, saisissez un message de commit (ex : `Premier commit du projet TP1`).
2. Cliquez sur l’icône de validation (✓) pour committer.
3. Cliquez sur "Synchroniser les modifications" ou "Push" pour envoyer votre commit sur GitHub.

Votre projet est maintenant versionné et sauvegardé sur votre dépôt GitHub personnel !

---

## 9. Ressources

- [Documentation officielle MSYS2](https://www.msys2.org/docs/)
- [Documentation CMake](https://cmake.org/cmake/help/latest/)
- [Documentation VSCode C/C++](https://code.visualstudio.com/docs/languages/cpp)

---


*Ce guide a été rédigé avec l’aide de GitHub Copilot.*
