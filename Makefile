.PHONY: install
install:
	ln -sf ../../../../../../helmecke/qmk_config/keyboards/keebio/iris/keymaps/helmecke ../../qmk/qmk_firmware/keyboards/keebio/iris/keymaps
	ln -sf ../../../../../../helmecke/qmk_config/keyboards/splitkb/kyria/keymaps/helmecke ../../qmk/qmk_firmware/keyboards/splitkb/kyria/keymaps
	ln -sf ../../../../../helmecke/qmk_config/layouts/community/split_3x5_3/helmecke ../../qmk/qmk_firmware/layouts/community/split_3x5_3
	ln -sf ../../../../../helmecke/qmk_config/layouts/community/split_3x6_3/helmecke ../../qmk/qmk_firmware/layouts/community/split_3x6_3
	ln -sf ../../../helmecke/qmk_config/users/helmecke ../../qmk/qmk_firmware/users

.PHONY: uninstall
uninstall:
	rm ../../qmk/qmk_firmware/keyboards/keebio/iris/keymaps/helmecke
	rm ../../qmk/qmk_firmware/keyboards/splitkb/kyria/keymaps/helmecke
	rm ../../qmk/qmk_firmware/layouts/community/split_3x5_3/helmecke
	rm ../../qmk/qmk_firmware/layouts/community/split_3x6_3/helmecke
	rm ../../qmk/qmk_firmware/users/helmecke
