# 2D Shooter

A small top-down arcade shooter built with **Qt 6** (C++17, Qt Widgets + Qt
Multimedia). You play an evil cat defending the bottom of the screen against
waves of incoming mice and rats — each enemy type has to be dealt with using the
matching weapon.

## Gameplay

Enemies spawn from the top and edges of the screen and move toward you. Shoot
them before they reach you; every enemy that slips past or collides with you
costs a life. Picking off enemies raises your score, shown in the HUD along with
your remaining health and the currently equipped weapon.

The twist is that **each weapon only damages its matching enemy**, so you have to
switch weapons to match whatever is on screen:

| Weapon       | Key | Effective against            |
| ------------ | --- | ---------------------------- |
| Gun          | `1` | basic mice / rats            |
| Cheese       | `2` | fat mice (also puts them to sleep) |
| Mouse Trap   | `3` | caster mice (also puts them to sleep) |

Enemy types include basic mice that drift straight down, heavier fat mice, rats
that streak across the screen horizontally, and caster mice that hang back and
fire magic projectiles at you.

## Controls

- **Arrow keys** — move
- **Space** — shoot
- **1 / 2 / 3** — switch weapon
- **X button** (top-right) — quit

## Build

Open `Shooter2D.pro` in Qt Creator and run, or build from the command line:

```sh
qmake Shooter2D.pro
make
```

Requires a Qt 6 installation with the **Multimedia** module available.

## Project layout

Source code is grouped by responsibility, roughly following the class hierarchy:

```
src/
  main.cpp              entry point; owns the global Game instance
  core/                 Game (the QGraphicsView), HUD, enemy spawner, screen config
  base/                 Object2D (scene-object base), Health, SoundEffect helper
  entities/             Entity base class
    enemies/            Enemy and its variants (fat, horizontal, caster)
  player/               Player and Score
  weapons/              Weapon strategy, Projectile base, concrete projectiles

assets/images/          sprites and backgrounds (.png)
assets/sounds/          sound effects and music (.wav, .ogg)
res.qrc                 Qt resource manifest (maps assets into :/images, :/sounds)
Shooter2D.pro           qmake project file
```

### Architecture notes

- **`Object2D`** is the common base for everything that lives in the scene
  (entities and projectiles) and defines the shared `move()` / `destroy()`
  contract.
- **`Weapon`** is a strategy interface: each weapon knows how to create its
  projectile and how it should look in the HUD, so adding a weapon doesn't
  require touching the player or HUD code.
- **`Projectile`** uses a template-method `move()`; subclasses customize only the
  collision/effect behaviour.
- **`SoundEffect`** wraps Qt Multimedia playback so audio objects are owned and
  cleaned up consistently.
