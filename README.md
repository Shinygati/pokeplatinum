# pokeplatinum

This is a fork of [pret/pokeplatinum](https://github.com/pret/pokeplatinum), the disassembly of Pokémon Platinum. It keeps the original decompilation intact and adds a set of gameplay changes aimed at making a playthrough faster, friendlier, and more rewarding.

All credit for the decompilation goes to the pret contributors. This fork only adds the changes listed below.

## Changes

### Shiny hunting

| Change | Details |
| --- | --- |
| Shiny odds | Increased to **1 in 4096** (from the vanilla 1 in 8192). |
| Egg shiny odds | **All eggs have 1 in 512** odds of being shiny. |
| Roamer shiny odds | Roaming Pokémon have **1 in 100** odds of being shiny. |

**Legality:** the shiny odds changes are built to stay legal. Pokémon are still generated the same way the game normally does it (nature, then PID, then IVs from the following RNG calls), so shiny Pokémon from this fork pass legality checks such as PKHeX and can be moved to Pokémon Bank / HOME without being flagged.

### Breeding

| Change | Details |
| --- | --- |
| Egg steps | Both **egg creation** and **egg hatching** step requirements are cut in half. |
| Egg IVs | Breeding eggs **guarantee a minimum of 15 IVs in every stat**. |
| Everstone | An Everstone on **either parent always** passes its nature (Gen 6 style). |
| Destiny Knot | A Destiny Knot on either parent passes **5 IVs** instead of 3. |
| Shiny Eggs | The summary screen shows the **shiny star on Eggs** that will hatch shiny. |

### Quality of life

| Change | Details |
| --- | --- |
| HM moves | **No Pokémon needs to know an HM move** to use it in the field. Only the matching badge is required. |
| Repel | When a Repel runs out, the game **prompts you to use another one**. |
| Poké Radar | **More lenient chain continuation rates**, so chains are easier to keep going. |
| Great Marsh | The Safari Game starts you with **50 Safari Balls and 1500 steps**. |
| Text speed | New **INST** text speed: each message box prints instantly. |
| Battle intro | New **BATTLE INTRO** option (replaces the CLOSE row; B or START closes the menu). **QUICK** makes the battle slide-in 4x faster. |
| HP / EXP bars | HP bars drain **2x** faster and EXP bars fill **3x** faster. |
| TMs | TMs are **reusable** and are not used up when a move is taught. |
| PC | A **PC** option in the start menu, **outdoors only**, once you have a Pokémon. When the menu is full it takes EXIT's place (B and X still close the menu). |
| Move Maniac | The Pastoria Move Maniac is **free**: no Heart Scale needed. |
| Fishing | Fishing **always hooks**, and a hooked Pokémon never gets away. |
| Poké Radar | The current **chain length** slides in on screen after each chained battle. |
| Honey trees | Trees are ready after **1 hour** instead of 6. |
| Starters | Starters are rolled when the briefcase opens, so a **shiny starter shows as shiny in the briefcase**. |

### Experience

| Change | Details |
| --- | --- |
| EXP. Share | **Enabled by default.** |
| EXP gain | Base EXP is multiplied by **1.2x**, rising to **2x** once the Elite Four has been beaten. |

### Event Pokémon

All of the Mystery Gift events are activated after beating the Elite Four, so no distribution is needed. This covers:

- Darkrai
- Shaymin
- Rotom
- Regigigas / the Regi trio

### Save compatibility

Saves stay compatible with unmodified Platinum. INST text is stored as FAST plus a spare bit in the options that vanilla ignores, BATTLE INTRO uses `FLAG_UNUSED_0x0168` (never touched by vanilla), and the start-menu PC uses a RAM-only flag that is never saved.

## Building

Build instructions are unchanged from upstream. See the [pret/pokeplatinum](https://github.com/pret/pokeplatinum) README for setup and dependencies.

## AI disclosure

AI (Claude, by Anthropic) was used to help write and review some of the code changes in this fork. All changes were tested and applied by me.

## Credits

- [pret](https://github.com/pret) and all contributors to [pokeplatinum](https://github.com/pret/pokeplatinum)
- Fork changes by the maintainer of this repository
