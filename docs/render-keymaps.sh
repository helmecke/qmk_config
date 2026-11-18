#!/usr/bin/env bash
# Render the Kyria keymap layers to SVG.
#
#   docs/render-keymaps.sh            # draw all layers into docs/keymaps/
#   docs/render-keymaps.sh MOUSE      # draw a single layer
#
# It only draws; docs/kyria_helmecke.yaml is edited by hand because custom
# keycodes, mod-taps and the German-US punctuation handling have no faithful
# `qmk c2json` representation. Requires keymap-drawer (`pip install --user
# keymap-drawer`); set KEYMAP to override the executable.
set -euo pipefail

cd "$(dirname "$0")"

if [[ $# -gt 0 ]]; then
    layers=("$@")
else
    layers=(QWERTY NAV NUM SYM MOUSE FUN ADJUST)
fi

if [[ -n ${KEYMAP:-} ]]; then
    keymap=("$KEYMAP")
elif command -v keymap >/dev/null 2>&1; then
    keymap=(keymap)
else
    # pip --user installs the console script outside PATH on Windows.
    keymap=(python -m keymap_drawer)
fi

mkdir -p keymaps
for layer in "${layers[@]}"; do
    out="keymaps/${layer,,}.svg"
    "${keymap[@]}" -c keymap_drawer.config.yaml draw \
        kyria_helmecke.yaml \
        -j kyria_rev2_layout.json \
        -s "$layer" \
        -o "$out"
    echo "wrote $out"
done
