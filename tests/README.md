# Fixtures for the Kyria helmecke configuration

These are focused regression fixtures for the parts of the configuration that
QMK does not cover on its own: the German-aware Caps Word policy, the shared
German/US punctuation handler, key overrides and the debounced host OS
application. They run inside upstream QMK's gtest harness, not in this
repository, because the harness and the quantum sources live there.

Tested with QMK master `8252b6309752f0be6882c387e15989ba51323d8f` and container
image `ghcr.io/qmk/qmk_cli:latest`, digest
`sha256:b7d7fa8fb4432b569931de5ad59098cb788f440ed61a62c5126746b71aee0f4a`.

## Fixtures

| Folder                 | Covers                                                                                                                                                                                          |
| ---------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `helmecke_caps_word/`  | Both-Shifts activation (plain Shift and the D/K home-row mod-taps, both press/release orders), D/K taps and holds, German minus/underscore, digits, AltGr umlauts, the dedicated corner keys (`ä`/`ü`/`ß`/`ö`, with `SS` for ß in mode), AltGr+S as SS, AltGr `!`/`?`, plain comma (single, rapid double and triple, held, interrupted, Shift+comma, Caps Word exit on the press), consumed punctuation, Space/Shift/shortcut exits, layer-tap access, quote/GUI mod-tap, the 5000 ms timeout. |
| `helmecke_os/`         | Debounced application of Windows/Linux/macOS/iOS detection, iOS as Apple, unknown hosts, changes between hosts, and operation without `CONSOLE_ENABLE`.                                            |

The two folders are real QMK full tests: `test.mk` enables the same feature
flags as the keymap, the shared userspace sources are compiled from
`users/helmecke`, and `keymap.c` defines the key override table exactly as the
Kyria keymap does. The tests drive matrix key events, so mod-tap resolution, key
overrides and Caps Word run through QMK's real event processing rather than
through copied mocks.

## Run

1. Initialize the QMK submodules the test and RP2040 builds need (once per
   checkout):

   ```bash
   git submodule update --init --recursive \
       lib/chibios lib/chibios-contrib lib/pico-sdk lib/lufa lib/googletest lib/printf
   ```

2. Stage this repository into the checkout:

   ```bash
   bash tests/stage-into-qmk.sh /path/to/qmk_firmware
   ```

3. Run the fixtures, either natively inside the checkout:

   ```bash
   cd /path/to/qmk_firmware
   make test:helmecke_caps_word
   make test:helmecke_os
   ```

   or in the QMK container on Windows, from the checkout:

   ```bash
   docker run --rm \
     -v "C:/path/to/qmk_firmware:/qmk_firmware" \
     -w /qmk_firmware -e SKIP_GIT=yes \
     ghcr.io/qmk/qmk_cli:latest \
     make test:helmecke_caps_word
   ```

   Use a `sh -c "..."` wrapper only if a login shell is avoided; the image
   provides `make` and the compilers on the default `PATH`.

## Notes

- The test platform emulates only 32 bytes of EEPROM and the harness's
  `TestDriver` must exist for the duration of the scan loops: `keyboard_task()`
  reads the host LED state through it. Both facts are harness behaviour, not
  configuration bugs.
- `helmecke_os` is built without `CONSOLE_ENABLE` on purpose; the test source
  fails to compile if console support is added, so OS application cannot
  silently depend on logging.
- Hardware behaviour (both USB orientations, Cirque, OLED, underglow, host
  input methods) is not covered by these fixtures. See the checklist in the
  repository `README.md`.
