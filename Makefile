.PHONY: install
install:
	ln -sf ../../../../../qmk_config/keyboards/keebio/iris/keymaps/helmecke ../qmk_firmware/keyboards/keebio/iris/keymaps
	ln -sf ../../../../../qmk_config/keyboards/splitkb/kyria/keymaps/helmecke ../qmk_firmware/keyboards/splitkb/kyria/keymaps
	ln -sf ../../../../qmk_config/layouts/community/split_3x5_3/helmecke ../qmk_firmware/layouts/community/split_3x5_3
	ln -sf ../../../../qmk_config/layouts/community/split_3x6_3/helmecke ../qmk_firmware/layouts/community/split_3x6_3
	ln -sf ../../qmk_config/users/helmecke ../qmk_firmware/users

.PHONY: uninstall
uninstall:
	rm ../qmk_firmware/keyboards/keebio/iris/keymaps/helmecke
	rm ../qmk_firmware/keyboards/splitkb/kyria/keymaps/helmecke
	rm ../qmk_firmware/layouts/community/split_3x5_3/helmecke
	rm ../qmk_firmware/layouts/community/split_3x6_3/helmecke
	rm ../qmk_firmware/users/helmecke
