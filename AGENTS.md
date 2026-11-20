# Repository orientation

Personal QMK configuration, integrated into a separate `qmk_firmware` checkout.
The user owns a Kyria v2.1 with an Adafruit KB2040 (RP2040) controller in each
half. Hardware drivers, the scan loop, USB handling, and the build toolchain
live in external QMK, not here. The Kyria keymap is the only maintained
reachability root: anything not reachable from it is not part of this
configuration.

## Where to work

- Kyria layout, encoder mappings, and OLED rendering:
  `keyboards/splitkb/kyria/keymaps/helmecke/keymap.c`.
  Adjacent `config.h` and `rules.mk` configure board-specific features,
  including the KB2040/split settings and Caps Word enablement.
- Shared behavior: `users/helmecke/helmecke.c`; shared includes:
  `users/helmecke/helmecke.h`.
- Shared layer identifiers, custom keys, reusable row/thumb macros, and the
  key-override registration table: `users/helmecke/definitions/`.
  Editing `keymap_blocks.h` affects all consumers, whereas editing the Kyria
  keymap changes that board's arrangement. `keymap_tables.h` carries only the
  key-override table.
- Feature implementations: `users/helmecke/features/`. Their compilation is
  controlled by `users/helmecke/rules.mk`; shared timing settings are in
  `users/helmecke/config.h`.
- Fixtures for the userspace and Caps Word integration: `tests/`.
- Layer diagrams: `docs/kyria_helmecke.yaml` mirrors the keymap expansion by
  hand. Update it with any keymap or row-macro change and redraw with
  `bash docs/render-keymaps.sh`; `docs/README.md` carries the legend and the
  behaviour that has no key position (encoders, key overrides, Caps Word).

## Runtime conventions

QMK calls `process_record_user()` in `helmecke.c`. The local chain has a single
handler, German-US punctuation handling, compiled under
`GERMAN_US_ENABLE`. Its tri-state result distinguishes emitting and consuming
(`PROCESS_RECORD_RETURN_TRUE`), consuming without reaching the action layer
(`PROCESS_RECORD_RETURN_FALSE`), and continuing to the next QMK handler
(`PROCESS_RECORD_CONTINUE`); see `definitions/process_record.h`.

The layout uses German host-layout keycodes (`DE_*`) with a QWERTY-style
arrangement and custom punctuation/macOS handling. Preserve this distinction
when changing symbols. Key overrides use a registered table: the definitions
must be visible to `quantum/keymap_introspection.c`, so the table lives in
`definitions/keymap_tables.h` and is included by the keymap, while the override
definitions and callbacks stay in `features/key_override.c`.

QMK mod-tap keycodes store the tap keycode in the low eight bits. Never wrap a
custom (`>= SAFE_RANGE`) keycode in a mod-tap macro; the tap key would be
truncated. `HB_QUOT` uses a basic tap key and lets `features/german_us.c`
produce the German output.

Built-in Caps Word (Kyria only) is layered on top of this chain. Keys consumed
by the German-US handler terminate Caps Word before emitting; key-override
triggers are processed after core Caps Word; taps and holds come from QMK. The
comma is a plain `DE_COMM`: it ends Caps Word on the press, and AltGr+comma then
activates the `?` override.

Tap-hold edges (Kyria `config.h` defines `CHORDAL_HOLD` and
`PERMISSIVE_HOLD_PER_KEY`; the callbacks are in `helmecke.c`): Chordal Hold keeps
same-hand overlaps as taps, with the thumb clusters and the AltGr keys `HB_X` /
`HB_DOT` exempt (`'*'`), and Permissive Hold is enabled only for the home-row
mod-taps. Thumb layer-taps stay non-permissive, and the Caps Word Shift pair
still needs both taps held past the tapping term. `tests/helmecke_tap_hold`
pins these branches.

`process_detected_host_os_user()` in `helmecke.c` applies the host OS once, and
display, punctuation and modifier swapping read that applied value through
`definitions/host_os.h`. There is no Unicode input mode management.

## Build and verification

`tests/stage-into-qmk.sh` is the only integration path: it copies the keymap,
userspace and fixtures into an external checkout. Nothing is symlinked.

Build/flash through the external QMK toolchain. See `README.md` for the exact
KB2040 commands and the hardware checklist. In short:

```bash
git -C /path/to/qmk_firmware worktree add /path/to/worktree 8252b6309752f0be6882c387e15989ba51323d8f
git -C /path/to/worktree submodule update --init --recursive \
    lib/chibios lib/chibios-contrib lib/pico-sdk lib/lufa lib/googletest lib/printf
tests/stage-into-qmk.sh /path/to/worktree

make splitkb/kyria/rev2:helmecke CONVERT_TO=kb2040 -j2
make test:helmecke_caps_word
make test:helmecke_os
make test:helmecke_tap_hold
```

A worktree keeps the pinned revision out of the checkout's working tree; run
the commands inside it, in the QMK container on Windows.

### Build and test status (2026-11-18, cleanup run)

- QMK master `8252b6309752f0be6882c387e15989ba51323d8f` and container image
  `ghcr.io/qmk/qmk_cli:latest` (digest
  `sha256:b7d7fa8fb4432b569931de5ad59098cb788f440ed61a62c5126746b71aee0f4a`).
- Full-feature KB2040 build passes with no compiler warnings and produces
  `.build/splitkb_kyria_rev2_base_helmecke_kb2040.uf2` without disabling OLED,
  encoders, underglow or the Cirque. The console-disabled variant
  (`CONSOLE_ENABLE=no`) also builds without warnings.
- The staged gtest fixtures pass: `helmecke_caps_word` (18 tests) and
  `helmecke_os` (5 tests).
- Hardware pass for this image (both halves on the same firmware): both
  matrices, encoders on both halves, the OLED status screen, every remaining
  layer, the transparent former debug slot on `_ADJUST` typing `b`, multi-tap
  and hold commas, AltGr `?`/`!`, and the Caps Word character checks
  (`HELLO_WORLD123`, `ÄÖÜ`, `SS`, comma exit, 5 s timeout). Underglow, the
  Cirque, the USB-C dock, the 60 s OLED sleep/wake and macOS/Linux hosts are
  covered by the 2026-11-17 run only, because this change cannot affect them.

## Known integration gaps

These are source-inspection findings unless stated otherwise; recheck before
relying on them or changing behavior:

- Only the left half has an OLED, and it renders the status screen in both USB
  orientations. Layer and host lock state are synced for that; Caps Word state
  is not, so `CapsWord: on` shows only while the left half is the USB half.
- The Cirque is present but currently disconnected (missing connector and ribbon
  cable), so pointing device behaviour is unvalidated.
- macOS/Linux host behaviour and the USB-C dock are unverified.
- OS detection is a USB fingerprint heuristic. There is no manual OS selector,
  and QMK keeps its detection state across a USB reconnect at the pinned
  revision, so a host change may need a keyboard reset.

For changes, trace both feature compilation and runtime registration/call sites.
