# Deluge Community Firmware — Akai Style Fork

## Dear Deluge owners
If you want to start using the community firmware please visit https://delugecommunity.com/ for all relevant details.

## About
The [Deluge](https://synthstrom.com/product/deluge/) from [Synthstrom Audible](https://synthstrom.com/) is a portable sequencer, synthesizer and sampler. Synthstrom Audible decided to [open source](https://synthstrom.com/open/) the firmware application that runs on the Deluge to allow the community to customize and extend the capabilities of the device. 

The hardware is built around a Renesas RZ/A1L processor with an Arm® Cortex®-A9 core running at 400MHz and 3MB of on-chip SRAM. Connected to that is a 64MB SDRAM chip, a PIC for button handling and either a 7-Segment array or an OLED screen. The application is written in C and C++ and some occasional assembly in bare metal style without an operating system.

## Akai-style time stretch

This fork adds an opt-in Akai S950/S1000-inspired realtime time-stretch engine on top of Deluge Community Firmware 1.3. It is designed for stretched and pitched-down sample material, with a short-cycle "chatter" at one end and a wide, smeared S1000-style sound at the other.

The stock Deluge workflow is preserved:

* Sample sources using **LINKED** pitch/speed keep the stock Deluge stretcher, decimation, and BITCRUSH behavior exactly as before.
* Sample sources using **Independent** pitch/speed, or **STRETCH** repeat mode, use the Akai engine when time stretching is actually active.
* The Akai engine uses fixed grain cycles with cyclic crossfades; it does not apply extra bit reduction to the stretched sound.

### Global engine switch

Choose the time-stretch engine globally in:

**SHIFT + SELECT-encoder → Community Features → Time Stretch Engine**

* OLED: `Time Stretch Engine`; 7SEG: `TSTR`
* `Akai` / `AKAI` — Akai grain engine. This is the default in this fork.
* `Deluge` / `DLG` — stock Community Firmware 1.3 time stretcher.

Setting the engine to **Deluge** restores the stock 1.3 time-stretch and BITCRUSH behavior.

### Grain-length control

While the Akai engine is active, the normal **BITCRUSH** shortcut controls the grain window instead:

* OLED: `Akai grain`; 7SEG: `GRAIN`
* Range: 8–50 ms
* Default: 24 ms
* Short grains give tight cyclic chatter; long grains give a wide S1000-style smear.

GRAIN can still be automated, but only through Deluge’s normal pad/note-held step automation. Turning the knob while the sequence plays is a live-only edit and is not recorded.

The real BITCRUSH setting is stored separately and returns automatically when the sample is switched back to **LINKED** or the global engine is set to **Deluge**. Decimation is bypassed only while Akai mode is active.

### Shortcut pad lighting

Community Firmware 1.3 includes a **Shortcut Overlay** feature that lights relevant pads while SHIFT is held. If you want the 1.2-like behavior, set:

**SHIFT + SELECT-encoder → Community Features → Shortcut Overlay → Off**

The 7SEG label is `OVER`, and the options are `OFF`, `MENU`, and `FULL`.

## Building and flashing

Build the release firmware with:

```sh
./dbt build release
```

The firmware image is written to `build/Release/deluge.bin`. Copy that file to the root of an SD card as the only `.bin` file, then boot the Deluge while holding SHIFT to flash it.

For USB RAM loading and other development workflows, see [development/deluge/tools.md](website/src/content/docs/development/deluge/tools.md).

## Important links
* For acquiring and using the firmware visit the [community firmware website](https://delugecommunity.com/)
* Once you have the firmware, consult our detailed [update guide](https://github.com/SynthstromAudible/DelugeFirmware/wiki/Update-guide) for instructions on how to install it
* To contribute to the project with code, bug reports, suggestions, and feedback see: [How to contribute to Deluge Firmware](https://github.com/SynthstromAudible/DelugeFirmware/blob/main/docs/CONTRIBUTING.md)
* To learn about the toolchain, application, and to start working on the code continue with: [Getting Started with Deluge Development](https://delugecommunity.com/development/deluge/getting_started/)
* Please also visit the [Synthstrom Forum](https://forums.synthstrom.com/) and the community [Discord](https://discord.gg/BnRcyFSgaT) to interact with other users and the developers
* You can donate to the project using the [Synthstrom Patreon](https://www.patreon.com/Synthstrom)
