```bash
qmk compile -kb keebio/iris/rev1 -km helmecke
qmk flash -kb keebio/iris/rev1 -km helmecke -bl avrdude-split-left
qmk flash -kb keebio/iris/rev1 -km helmecke -bl avrdude-split-right
```
