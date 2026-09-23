# 🎮 Moteur de Jeu 2D – Suivi de Progression
**Auteur** : Morphée Sevestre
**Date de début** : 10/09/2026
**Date de fin** : En cours
**Lien GitHub** : [À compléter]
**Documentation** : [Moteur de jeu.pdf](lien_vers_ton_pdf)

---

## 📚 Contexte et Objectifs

Ce projet s'inscrit dans le cadre d'un **TP de mathématiques appliquées à l'informatique**, visant à développer un **moteur de jeu 2D** en C++ avec la bibliothèque **Qt**. L'objectif principal est de **modéliser des mouvements physiques** (vitesse, accélération, forces) et de les intégrer dans un environnement interactif.

### 🎯 Objectifs clés (d'après le [PDF du TP](#)) :
- **Séparation des responsabilités** :
  - **Bibliothèque graphique** (Qt) : Affichage, événements clavier/souris.
  - **Moteur physique** : Gestion du temps, des déplacements, des collisions.
  - **Logique du jeu** : Règles, scénarios, interactions.

---

## 🗂️ Architecture du Projet

### 📁 Structure des Fichiers
```
📂 Projet/
├── main.cpp                  # Point d'entrée de l'application
├── GameWindow.h/.cpp         # Fenêtre principale (Qt) + gestion des mises à jour
├── Controller.h/.cpp         # Gestion des entrées clavier et contrôle des objets physiques
├── Rigidbody.h/.cpp          # Classe représentant un objet physique (masse, position, vitesse, accélération)
└── [Autres fichiers à ajouter]
```

---

### 🧱 Classes Implémentées

#### 1. **`Rigidbody`** (Objet Physique)
- **Rôle** : Représente un objet physique avec une masse, une position, une vitesse et une accélération.
- **Fonctionnalités** :
  - `updatePosition(float deltaTime)` : Met à jour la position en fonction de la vitesse.
  - `updateVelocity(float deltaTime)` : Met à jour la vitesse en fonction de l'accélération.
  - `applyForce(float forceX, float forceY)` : Applique une force et calcule l'accélération résultante (`a = F/m`).
  - `update(float deltaTime)` : Met à jour la vitesse **puis** la position (méthode d'Euler explicite).
- **Données membres** :
  - `massTons` : Masse de l'objet (1 tonne par défaut).
  - `positionWorld` : Position dans le monde physique (coordonnées `x`, `y`).
  - `velocity` : Vitesse (`vx`, `vy`).
  - `acceleration` : Accélération (`ax`, `ay`).


---

#### 2. **`Controller`** (Contrôleur des Objets)
- **Rôle** : Gère les entrées clavier et applique des forces aux `Rigidbody` sélectionnés.
- **Fonctionnalités** :
  - `handleInput()` : Applique des forces aux `Rigidbody` en fonction des touches pressées (flèches directionnelles).
    - Force selon `x` : `(right - left) * base_acceleration`.
    - Force selon `y` : `(down - up) * base_acceleration`.
  - `update(float deltaTime)` : Met à jour les `Rigidbody` sélectionnés.
  - `selectRigidbody(Rigidbody* rb)` / `deselectRigidbody(Rigidbody* rb)` : Gestion des objets contrôlés.
- **Données membres** :
  - `base_acceleration` : Accélération de base (20.0 par défaut).
  - `up`, `down`, `left`, `right`, `stop` : États des touches.
  - `selectedRigidbodies` : Liste des `Rigidbody` contrôlés.


---

#### 3. **`GameWindow`** (Fenêtre de Jeu)
- **Rôle** : Fenêtre principale de l'application (héritée de `QMainWindow`).
- **Fonctionnalités** :
  - **Gestion du temps** :
    - `fps = 50` : Nombre de mises à jour par seconde.
    - `dt = 1.0f / fps` : Temps écoulé entre les mises à jour (0.02s).
    - `QTimer` : Déclenche `updateGame()` toutes les 20 ms.
  - **Conversion de coordonnées** :
    - `worldToScreen(WorldPoint, W, H, z)` : Convertit les coordonnées physiques (`x`, `y`) en coordonnées écran (`X`, `Y`).
    - `screentoWorld(ScreenPoint, W, H, z)` : Convertit les coordonnées écran en coordonnées physiques.
    - **Formules** :
      - `X = (x * z) + (W / 2)`
      - `Y = (y * z) + (H / 2)`
      - `x = (X - (W / 2)) / z`
      - `y = (Y - (H / 2)) / z`
  - **Affichage** (`paintEvent`) :
    - Dessine un cercle **rouge** au centre de l'écran (origine du monde physique).
    - Dessine un cercle **bleu** à la position du `Rigidbody` sélectionné.
  - **Gestion des entrées** (`keyPressEvent`, `keyReleaseEvent`) :
    - Met à jour les flags `up`, `down`, `left`, `right` du `Controller`.
    - La touche **Espace** arrête tous les mouvements.


---

#### 4. **`main.cpp`** (Point d'Entrée)
- **Rôle** : Initialise l'application Qt et affiche la fenêtre de jeu.

---

## 📅 Timeline des Commits

### 🔹 **Phase 1 : Initialisation du Projet**
| Date | Commit | Auteur | Description |
|------|--------|--------|-------------|
| 10/09/2026 | `Create Moteur de jeu.pdf` | Morphée Sevestre | Ajout du sujet du TP. |
| 10/09/2026 | `Add files via upload` | Morphée Sevestre | Ajout des fichiers initiaux (CMake, squelettes). |
| 10/09/2026 | `add void` | Morphée Sevestre | Ajout de fonctions vides pour tester la structure. |
| 10/09/2026 | `test ajout projet vide` | Morphée Sevestre | Test d'un projet vide (validation de la compilation). |
| 10/09/2026 | `Add project description to README` | Morphée Sevestre | Ajout d'une description du projet. |
| 10/09/2026 | `Add Visual Studio and X64 files to .gitignore` | Morphée Sevestre | Configuration de `.gitignore` pour éviter les fichiers IDE. |
| 10/09/2026 | `switch version` | Morphée Sevestre | Changement de version. |
| 10/09/2026 | `ajout ressources` | Morphée Sevestre | Ajout de ressources (assets). |
| 10/09/2026 | `Merge branch 'main' of https://github...` | Morphée Sevestre | Fusion avec la branche principale. |

---

### 🔹 **Phase 2 : Développement du Moteur Physique**
| Date | Commit | Auteur | Description |
|------|--------|--------|-------------|
| 14/09/2026 | `Update .gitignore` | Morphée Sevestre | Mise à jour de `.gitignore`. |
| 14/09/2026 | `check mathematical expression + changes` | Farah-Ali | Vérification des expressions mathématiques. |
| 14/09/2026 | `Merge branch 'main' of https://github...` | Farah-Ali | Fusion avec `main`. |
| 14/09/2026 | `Create reponse_sujet_du_projet.txt` | Farah-Ali | Création d'un fichier de réponses (questions théoriques). |
| 14/09/2026 | `ssrsrg` | alowen |  |

---

### 🔹 **Phase 3 : Implémentation des Fonctionnalités de Base**
| Date | Commit | Auteur | Description |
|------|--------|--------|-------------|
| 15/09/2026 | `fix petit bug` | Morphée Sevestre | Correction d'un bug mineur. |
| 15/09/2026 | `add base physics lib` | Morphée Sevestre | Ajout de la bibliothèque de base pour la physique (`Rigidbody.h/.cpp`). |
| 15/09/2026 | `okwhatever` | Morphée Sevestre | correction d'un bug mineur |
| 15/09/2026 | `temporaire ajout controller` | Morphée Sevestre | Ajout temporaire du `Controller` pour gérer les entrées clavier. |
| 15/09/2026 | `add basic rigidbody` | Morphée Sevestre | Implémentation de la classe `Rigidbody`. |
| 15/09/2026 | `Merge branch 'main' of https://github...` | Morphée Sevestre | Fusion avec `main`. |
| 15/09/2026 | `Update .gitignore` | Morphée Sevestre | Mise à jour de `.gitignore`. |
| 15/09/2026 | `check mathematical expression + changes` | Farah-Ali | Re-vérification des expressions mathématiques. |
| 15/09/2026 | `Merge branch 'main' of https://github...` | Farah-Ali | Fusion avec `main`. |

---

### 🔹 **Phase 4 : Intégration et Tests**
| Date | Commit | Auteur | Description |
|------|--------|--------|-------------|
| 18/09/2026 | `petite modif` | Morphée Sevestre | Modification mineure. |
| 18/09/2026 | `ajout inputs` | Morphée Sevestre | Ajout de la gestion des entrées clavier (`Controller`). |
| 18/09/2026 | `fix petit bug` | Morphée Sevestre | Correction d'un bug. |
| 23/09/2026 | `Proposition du vaisseau fonctionnelle...` | Morphée Sevestre | Proposition d'une implémentation fonctionnelle du joueur (`Rigidbody` + `Controller`). |

---

## ✅ Fonctionnalités Implémentées

### 1. **Affichage et Coordonnées**
- **Réalisé** :
  - Affichage d'un cercle **rouge** au centre de l'écran (origine du monde physique).
  - Affichage d'un cercle **bleu** pour le `Rigidbody` contrôlé.
  - Conversion entre **coordonnées physiques** (`x`, `y`) et **coordonnées écran** (`X`, `Y`).
- **Lien avec le TP** : **Partie 1.2** (Questions 1 à 8).

---

### 2. **Déplacements du Joueur**
- **Réalisé** :
  - Déplacements fluides avec les **touches directionnelles** (flèches).
  - Gestion des **mouvements simultanés** (ex: haut + droite).
  - Arrêt complet avec la touche **Espace**.
- **Implémentation** :
  - Le `Controller` applique des forces au `Rigidbody` en fonction des touches pressées.
  - Le `Rigidbody` met à jour sa vitesse et sa position avec la **méthode d'Euler explicite** :
    ```cpp
    velocity += acceleration * deltaTime;  // dv/dt = a
    position += velocity * deltaTime;       // dx/dt = v
    ```
- **Lien avec le TP** :
  - **Partie 1.3** : Déplacements basiques.
  - **Partie 1.4** : Déplacements fluides (interrogation régulière du clavier).

---

### 3. **Méthode d'Euler Explicite**
- **Réalisé** :
  - Discrétisation des équations différentielles pour la **vitesse** et la **position**.
  - Implémentation dans `Rigidbody::update(float deltaTime)` :
    ```cpp
    void Rigidbody::update(float deltaTime) {
        updateVelocity(deltaTime);  // v_{n+1} = v_n + a_n * Δt
        updatePosition(deltaTime);  // x_{n+1} = x_n + v_{n+1} * Δt
    }
    ```
- **Lien avec le TP** : **Partie 2.3** (Questions 1 à 7).

---

### 4. **Application de Forces**
- **Réalisé** :
  - Application de **forces constantes** via le `Controller` :
    ```cpp
    rb->applyForce(
        (right - left) * base_acceleration, 
        (down - up) * base_acceleration
    );
    ```
  - Calcul de l'**accélération** dans `Rigidbody::applyForce` :
    ```cpp
    acceleration[0] = forceX / massTons;  // a = F/m
    acceleration[1] = forceY / massTons;
    ```
- **Lien avec le TP** : **Partie 4.1** (Propulsion du joueur).

---

### 5. **Gestion du Temps**
- **Réalisé** :
  - Mise à jour du jeu à **50 FPS** (toutes les 20 ms).
  - Utilisation de `QTimer` pour déclencher `updateGame()` régulièrement.
  - `deltaTime = 1.0f / 50 = 0.02s` (pas de temps fixe).
- **Lien avec le TP** : **Partie 1.4** (FPS et `update()`).

---

## 📌 Annexes

### 🔹 Extraits de Code Clés

#### 1. **`Rigidbody::update` (Méthode d'Euler)**
```cpp
void Rigidbody::update(float deltaTime) {
    updateVelocity(deltaTime);  // v_{n+1} = v_n + a_n * Δt
    updatePosition(deltaTime);  // x_{n+1} = x_n + v_{n+1} * Δt
}

void Rigidbody::updateVelocity(float deltaTime) {
    velocity[0] += acceleration[0] * deltaTime;
    velocity[1] += acceleration[1] * deltaTime;
}

void Rigidbody::updatePosition(float deltaTime) {
    positionWorld[0] += velocity[0] * deltaTime;
    positionWorld[1] += velocity[1] * deltaTime;
}
```

---

#### 2. **`Controller::handleInput` (Gestion des Entrées)**
```cpp
void Controller::handleInput() {
    for (auto& rb : selectedRigidbodies) {
        rb->applyForce(
            (right - left) * base_acceleration, 
            (down - up) * base_acceleration
        );
    }
}
```

---

#### 3. **`GameWindow::worldToScreen` (Conversion de Coordonnées)**
```cpp
ScreenPoint worldToScreen(const WorldPoint& worldPt, double W, double H, double z) {
    double X = (worldPt.first * z) + (W / 2);
    double Y = (worldPt.second * z) + (H / 2);
    return ScreenPoint{ X, Y };
}

WorldPoint screentoWorld(const ScreenPoint& point, double W, double H, double z) {
    double x = (point.first - (W / 2)) / z;
    double y = (point.second - (H / 2)) / z;
    return WorldPoint{ x, y };
}
```

---

### 🔹 Ressources Utiles
- **Documentation Qt** : [https://doc.qt.io/](https://doc.qt.io/)
- **Méthode d'Euler** : [Wikipédia](https://fr.wikipedia.org/wiki/M%C3%A9thode_d%27Euler)

---

**Dernière mise à jour** : 23/09/2026