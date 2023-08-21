add_custom_target(mcuboot_shared_property_target)
set_property(TARGET mcuboot_shared_property_target  PROPERTY KERNEL_HEX_NAME;zephyr.hex)
set_property(TARGET mcuboot_shared_property_target  PROPERTY ZEPHYR_BINARY_DIR;D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/mcuboot/zephyr)
set_property(TARGET mcuboot_shared_property_target  PROPERTY KERNEL_ELF_NAME;zephyr.elf)
set_property(TARGET mcuboot_shared_property_target  PROPERTY BUILD_BYPRODUCTS;D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/mcuboot/zephyr/zephyr.hex;D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/mcuboot/zephyr/zephyr.elf)
set_property(TARGET mcuboot_shared_property_target  PROPERTY SIGNATURE_KEY_FILE;root-rsa-2048.pem)
set_property(TARGET mcuboot_shared_property_target APPEND PROPERTY PM_YML_DEP_FILES;D:/nordicsemi/v2.4.0/bootloader/mcuboot/boot/zephyr/pm.yml)
set_property(TARGET mcuboot_shared_property_target APPEND PROPERTY PM_YML_FILES;D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/mcuboot/zephyr/include/generated/pm.yml)
