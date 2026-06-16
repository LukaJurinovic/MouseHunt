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
