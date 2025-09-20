# Tutoriel : Développer en C/C++ sous Windows avec VSCode, MSYS2, CMake et Git

## 1. Installer Visual Studio Code

1. Rendez-vous sur la page officielle de téléchargement :  
   [https://code.visualstudio.com/](https://code.visualstudio.com/)
2. Téléchargez la version Windows et installez-la en suivant les instructions. **Bien choisir "User Installer" pour une installation sans droits administrateur.**

---

## 2. Installer MSYS2

1. Accédez au site officiel :  
   [https://www.msys2.org/](https://www.msys2.org/)  
2. Téléchargez l'installateur adapté à votre architecture (x86_64 pour la plupart des PC récents).  
3. MSYS2 doit être installé dans `C:\Info\msys64`. Lancez l’installateur et suivez les instructions.  
4. Ouvrez le terminal **MSYS2 UCRT64** (icône "MSYS2 UCRT64").

---

## 3. Mettre à jour MSYS2 et installer les outils nécessaires

Dans le terminal MSYS2, exécutez les commandes suivantes :

```sh
# Mettre à jour le système
pacman -Syu
# Fermez le terminal si demandé, puis relancez-le et continuez :
pacman -Su

# Installer les outils de développement C/C++, CMake et Git
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-cmake git
```

---

## 4. Ajouter MSYS2 au PATH pour VSCode

> **Pourquoi choisir ucrt64 ?**
> La variante **ucrt64** de MSYS2 utilise l’Universal C Runtime de Microsoft (UCRT), ce qui garantit une meilleure compatibilité avec les applications Windows modernes, Visual Studio, et les bibliothèques récentes. Elle est recommandée pour les nouveaux projets C/C++ sous Windows car elle facilite l’interopérabilité, la portabilité et la gestion des encodages de caractères.

Pour que VSCode détecte les outils MSYS2 UCRT64, ajoutez le chemin `C:\Info\msys64\ucrt64\bin` à la variable d’environnement `PATH` de Windows.

1. Ouvrez les Paramètres système avancés → Variables d’environnement.
2. Modifiez la variable `Path` de votre utilisateur.
3. Ajoutez :  
  `C:\Info\msys64\ucrt64\bin`
4. Monter ce nouveau chemin en premier dans la liste.  
5. Validez et redémarrez votre ordinateur pour que les changements soient pris en compte.


> **Remarque importante :**
> Sous MSYS2 UCRT64, le binaire de make fourni par le paquet `mingw-w64-ucrt-x86_64-make` s'appelle `mingw32-make.exe` (et non `make.exe`).
> Pour compiler vos projets, utilisez donc la commande `mingw32-make` dans le terminal, ou laissez CMake Tools le détecter automatiquement.
> Si la commande `which make` retourne `/usr/bin/make`, c'est le make de l'environnement MSYS2 POSIX, qui n'est pas compatible avec la toolchain UCRT64.
---


## 5. Installer Git for Windows et les extensions VSCode recommandées

Avant d’installer les extensions, installez **Git for Windows** :

1. Téléchargez l’installateur officiel depuis [https://git-scm.com/](https://git-scm.com/).
2. Lors de l’installation, choisissez le dossier `C:\Info\Git` comme chemin d’installation personnalisé.
3. Laissez toutes les autres options par défaut.
4. Une fois l’installation terminée, redémarrez VSCode pour qu’il détecte Git automatiquement.

Ouvrez ensuite VSCode et installez les extensions suivantes :

- **C/C++ Extension Pack** (Microsoft, recommandé)  
  [Lien direct](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
    - Ce pack inclut : C/C++, CMake Tools, CMake, Clang-Format, Clangd, Include Autocomplete, etc.
- **Project Templates** (pour créer des projets rapidement), acceptez de faire confiance à l'éditeur Cantonios.    
  [Lien direct](https://marketplace.visualstudio.com/items?itemName=cantonios.project-templates)
- **Git History** (pour visualiser l'historique Git)  
  [Lien direct](https://marketplace.visualstudio.com/items?itemName=donjayamanne.githistory)
- **French Language Pack for Visual Studio Code** (pour une interface en français), acceptez la proposition d'installation automatique de VSCode après le redémarrage.    
  [Lien direct](https://marketplace.visualstudio.com/items?itemName=MS-CEINTL.vscode-language-pack-fr)

---

## 6. Configurer VSCode pour MSYS2


Dans VSCode, ouvrez les paramètres (`Ctrl+,`) et recherchez `terminal.integrated.profiles.windows`.
Ajoutez un profil pour MSYS2 **en veillant à l’ajouter à la liste déjà existante** (séparez chaque profil par une virgule).

```json
"terminal.integrated.profiles.windows": {
  "MSYS2 UCRT64": {
    "path": "C:\\Info\\msys64\\usr\\bin\\bash.exe",
    "args": ["--login", "-i"],
    "icon": "terminal-bash",
    "env": {
      "MSYSTEM": "UCRT64"
    }
  }
}
```

> **Remarque :** Ce profil démarre directement l'environnement UCRT64 en passant la variable d'environnement `MSYSTEM=UCRT64`, ce qui correspond au comportement de l'icône "MSYS2 UCRT64" du menu Démarrer. 

Vous pourrez alors ouvrir un terminal MSYS2 directement dans VSCode.

Pour cela, ouvrez un terminal intégré (`Ctrl+ù` ou menu Terminal > Nouveau terminal), puis cliquez sur la flèche à droite du bouton “+” du terminal et sélectionnez le profil **MSYS2 UCRT64** dans la liste proposée. Si besoin, refermez et rouvrez le terminal pour que le bon profil soit utilisé.

---



## 7. Créer, compiler et déboguer un projet d'exemple avec Project Templates

### Avant de commencer : organiser vos dépôts dans un dossier `src`

1. Dans l’Explorateur de fichiers Windows, créez un dossier `src` à l’emplacement de votre choix (par exemple `C:\Users\<votre-nom>\src`).
2. Tous vos dépôts (templates, TP, etc.) seront placés dans ce dossier pour une organisation claire.

### 7.1. Cloner le dépôt de templates

Dans VSCode, ouvrez la palette de commandes (`Ctrl+Shift+P`) et tapez `Git: Clone`. Collez l'URL suivante :

```
https://github.com/epsilonrt/vscode-project-templates.git
```

Quand VSCode demande le dossier de destination, sélectionnez le dossier `src` que vous venez de créer (`C:\Users\<votre-nom>\src`).
Ouvrez ensuite le dossier cloné dans VSCode si ce n'est pas déjà fait.


### 7.2. Paramétrer l'extension Project Templates

1. Dans VSCode, ouvrez les paramètres (`Ctrl+,`) et recherchez `projectTemplates.templatesDirectory`.
2. Ajoutez ou modifiez la ligne suivante (Adaptez le chemin à votre organisation.)  
3. Enregistrez le fichier settings.json.

```json
"projectTemplates.templatesDirectory": "C:/Users/<votre-nom>/src/vscode-project-templates"
```  


### 7.3. Créer un nouveau projet à partir du modèle 'MSys2 CMake C Project'

1. Dans l’Explorateur de fichiers, créez un dossier `vscode-labs` dans `src` pour regrouper tous vos TP :
  - `C:\Users\<votre-nom>\src\vscode-labs`
2. À l’intérieur de `vscode-labs`, créez un sous-dossier pour le projet Hello (par exemple `Hello`).
  - `C:\Users\<votre-nom>\src\vscode-labs\Hello`
3. Dans VSCode, ouvrez le dossier `Hello` (`Fichier > Ouvrir le dossier...` ou faites glisser le dossier dans la fenêtre VSCode).
4. Ouvrez la palette de commandes (`Ctrl+Shift+P`).
5. Tapez `Project Templates: Create Project from Template`.
6. Sélectionnez le modèle **MSys2 CMake C Project** et donnez un nom au projet (par exemple `Hello`).
7. Validez pour générer le projet dans le dossier `Hello`.


### 7.4. Configurer et compiler le projet avec CMake Tools

1. Cliquez sur l'icône CMake dans la barre latérale gauche de VSCode (ou utilisez la commande `CMake: Configure`) pour configurer le projet.
2. Choisissez le kit correspondant à **MSYS2 UCRT64** (le nom peut varier selon l'installation).
3. Cliquez sur l'icône "Générer" (Roue dentée) dans la barre de statut pour compiler le projet.

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
5. Le débogueur s’attachera automatiquement à l’exécutable généré par CMake, en utilisant gdb fourni par MSYS2 UCRT64.


Vous pouvez placer des points d’arrêt, inspecter les variables, et utiliser toutes les fonctionnalités de débogage de VSCode.

> **Remarque :**
> Si le débogueur ne s'arrête pas automatiquement au lancement, placez un point d'arrêt (clic gauche dans la marge) sur la ligne du `printf` dans le fichier source principal avant de démarrer le débogage. Cela permet de vérifier que l'exécution s'arrête bien sur votre code.

Pour aller plus loin, consultez le guide officiel sur le débogage C/C++ dans VSCode :
[https://code.visualstudio.com/docs/cpp/debugging](https://code.visualstudio.com/docs/cpp/debugging)

---

## 8. Profiter de GitHub et GitHub Copilot dans VSCode

### 8.1. Créer un compte GitHub et Connecter VSCode à votre compte GitHub

1. Rendez-vous sur [https://github.com/](https://github.com/) et inscrivez-vous avec votre adresse mail étudiante.  
2. Cliquez sur l’icône de compte en bas à gauche de VSCode, puis sur "Se connecter à GitHub pour profiter de l'IA".  
3. Suivez les instructions pour autoriser VSCode à accéder à votre compte GitHub.

### 8.2. Créer un dépôt GitHub pour vos TP

1. Dans VSCode, ouvrez le dossier de votre projet (par exemple, vscode-labs).
2. Ouvrez l’onglet Source Control (icône branche Git à gauche ou `Ctrl+Shift+G`).
3. Cliquez sur "Publier sur GitHub" ou "Publish to GitHub".
4. Donnez un nom à votre dépôt, par exemple `vscode-labs`.
5. Choisissez la visibilité (privé ou public) puis validez.

### 8.3. Versionner et pousser votre projet sur GitHub

1. Dans l’onglet Source Control, saisissez un message de commit (ex : `Premier commit du projet TP1`).
2. Cliquez sur l’icône de validation (✓) pour committer.
3. Cliquez sur "Synchroniser les modifications" ou "Push" pour envoyer votre commit sur GitHub.

Votre projet est maintenant versionné et sauvegardé sur votre dépôt GitHub personnel !

### 8.4. Utiliser Copilot pour modifier main.c

Vous pouvez demander à GitHub Copilot de modifier le fichier `main.c` pour afficher 10 fois le message "Hello World!".

**Exemple de prompt à saisir dans Copilot Chat ou dans la palette de commandes Copilot :**

> Modifie main.c pour qu'il affiche 10 fois "Hello World!" à l'exécution.

Copilot proposera alors le code adapté, généralement une boucle `for` avec un `printf`. Validez la suggestion ou copiez-la dans votre fichier.

---

## 9. Ressources

- [Documentation officielle MSYS2](https://www.msys2.org/docs/)
- [Documentation CMake](https://cmake.org/cmake/help/latest/)
- [Documentation VSCode C/C++](https://code.visualstudio.com/docs/languages/cpp)

---


*Ce guide a été rédigé avec l’aide de GitHub Copilot.*
