# pokeplatinum (modified fork)

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

### Quality of life

| Change | Details |
| --- | --- |
| Egg steps | Both **egg creation** and **egg hatching** step requirements are cut in half. |
| HM moves | **No Pokémon needs to know an HM move** to use it in the field. Only the matching badge is required. |
| Repel | When a Repel runs out, the game **prompts you to use another one**. |
| Poké Radar | **More lenient chain continuation rates**, so chains are easier to keep going. |

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
- Regigigas / the Regi event

## Building

Build instructions are unchanged from upstream. See the [pret/pokeplatinum](https://github.com/pret/pokeplatinum) README for setup, dependencies, and how to provide your own ROM.

## AI disclosure

AI (Claude, by Anthropic) was used to help write and review some of the code changes in this fork. All changes were tested and applied by me.

## Credits

- [pret](https://github.com/pret) and all contributors to [pokeplatinum](https://github.com/pret/pokeplatinum)
- Fork changes by the maintainer of this repository
