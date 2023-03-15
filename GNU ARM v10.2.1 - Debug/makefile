################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/subdir.mk
-include gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_protocol_crypto/src/subdir.mk
-include gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_mbedtls_support/src/subdir.mk
-include gecko_sdk_4.1.2/util/third_party/crypto/sl_component/se_manager/src/subdir.mk
-include gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/subdir.mk
-include gecko_sdk_4.1.2/util/silicon_labs/silabs_core/memory_manager/subdir.mk
-include gecko_sdk_4.1.2/protocol/bluetooth/src/subdir.mk
-include gecko_sdk_4.1.2/platform/service/system/src/subdir.mk
-include gecko_sdk_4.1.2/platform/service/sleeptimer/src/subdir.mk
-include gecko_sdk_4.1.2/platform/service/power_manager/src/subdir.mk
-include gecko_sdk_4.1.2/platform/service/mpu/src/subdir.mk
-include gecko_sdk_4.1.2/platform/service/iostream/src/subdir.mk
-include gecko_sdk_4.1.2/platform/service/hfxo_manager/src/subdir.mk
-include gecko_sdk_4.1.2/platform/service/device_init/src/subdir.mk
-include gecko_sdk_4.1.2/platform/radio/rail_lib/plugin/rail_util_rf_path/subdir.mk
-include gecko_sdk_4.1.2/platform/radio/rail_lib/plugin/rail_util_pti/subdir.mk
-include gecko_sdk_4.1.2/platform/radio/rail_lib/plugin/pa-conversions/subdir.mk
-include gecko_sdk_4.1.2/platform/emlib/src/subdir.mk
-include gecko_sdk_4.1.2/platform/emdrv/nvm3/src/subdir.mk
-include gecko_sdk_4.1.2/platform/emdrv/gpiointerrupt/src/subdir.mk
-include gecko_sdk_4.1.2/platform/driver/leddrv/src/subdir.mk
-include gecko_sdk_4.1.2/platform/driver/debug/src/subdir.mk
-include gecko_sdk_4.1.2/platform/driver/button/src/subdir.mk
-include gecko_sdk_4.1.2/platform/common/toolchain/src/subdir.mk
-include gecko_sdk_4.1.2/platform/common/src/subdir.mk
-include gecko_sdk_4.1.2/platform/bootloader/app_properties/subdir.mk
-include gecko_sdk_4.1.2/platform/bootloader/api/subdir.mk
-include gecko_sdk_4.1.2/platform/Device/SiliconLabs/EFR32MG21/Source/subdir.mk
-include gecko_sdk_4.1.2/hardware/driver/configuration_over_swo/src/subdir.mk
-include gecko_sdk_4.1.2/hardware/board/src/subdir.mk
-include gecko_sdk_4.1.2/app/common/util/app_log/subdir.mk
-include gecko_sdk_4.1.2/app/bluetooth/common/simple_timer/subdir.mk
-include autogen/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := conn_interval_central_CI
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: conn_interval_central_CI.axf

# Tool invocations
conn_interval_central_CI.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -T "/Users/clfilho/SimplicityStudio/C-32CON/conn_interval_central_CI/autogen/linkerfile.ld" -Xlinker --gc-sections -Xlinker -Map="conn_interval_central_CI.map" -mfpu=fpv5-sp-d16 -mfloat-abi=hard --specs=nano.specs -o conn_interval_central_CI.axf -Wl,--start-group "./app.o" "./main.o" "./autogen/gatt_db.o" "./autogen/sl_bluetooth.o" "./autogen/sl_board_default_init.o" "./autogen/sl_device_init_clocks.o" "./autogen/sl_event_handler.o" "./autogen/sl_iostream_handles.o" "./autogen/sl_iostream_init_usart_instances.o" "./autogen/sl_power_manager_handler.o" "./autogen/sl_simple_button_instances.o" "./autogen/sl_simple_led_instances.o" "./gecko_sdk_4.1.2/app/bluetooth/common/simple_timer/sl_simple_timer.o" "./gecko_sdk_4.1.2/app/common/util/app_log/app_log.o" "./gecko_sdk_4.1.2/hardware/board/src/sl_board_control_gpio.o" "./gecko_sdk_4.1.2/hardware/board/src/sl_board_init.o" "./gecko_sdk_4.1.2/hardware/driver/configuration_over_swo/src/sl_cos.o" "./gecko_sdk_4.1.2/platform/Device/SiliconLabs/EFR32MG21/Source/startup_efr32mg21.o" "./gecko_sdk_4.1.2/platform/Device/SiliconLabs/EFR32MG21/Source/system_efr32mg21.o" "./gecko_sdk_4.1.2/platform/bootloader/api/btl_interface.o" "./gecko_sdk_4.1.2/platform/bootloader/api/btl_interface_storage.o" "./gecko_sdk_4.1.2/platform/bootloader/app_properties/app_properties.o" "./gecko_sdk_4.1.2/platform/common/src/sl_assert.o" "./gecko_sdk_4.1.2/platform/common/src/sl_slist.o" "./gecko_sdk_4.1.2/platform/common/toolchain/src/sl_memory.o" "./gecko_sdk_4.1.2/platform/driver/button/src/sl_button.o" "./gecko_sdk_4.1.2/platform/driver/button/src/sl_simple_button.o" "./gecko_sdk_4.1.2/platform/driver/debug/src/sl_debug_swo.o" "./gecko_sdk_4.1.2/platform/driver/leddrv/src/sl_led.o" "./gecko_sdk_4.1.2/platform/driver/leddrv/src/sl_simple_led.o" "./gecko_sdk_4.1.2/platform/emdrv/gpiointerrupt/src/gpiointerrupt.o" "./gecko_sdk_4.1.2/platform/emdrv/nvm3/src/nvm3_default_common_linker.o" "./gecko_sdk_4.1.2/platform/emdrv/nvm3/src/nvm3_hal_flash.o" "./gecko_sdk_4.1.2/platform/emdrv/nvm3/src/nvm3_lock.o" "./gecko_sdk_4.1.2/platform/emlib/src/em_burtc.o" "./gecko_sdk_4.1.2/platform/emlib/src/em_cmu.o" "./gecko_sdk_4.1.2/platform/emlib/src/em_core.o" "./gecko_sdk_4.1.2/platform/emlib/src/em_emu.o" "./gecko_sdk_4.1.2/platform/emlib/src/em_gpio.o" "./gecko_sdk_4.1.2/platform/emlib/src/em_msc.o" "./gecko_sdk_4.1.2/platform/emlib/src/em_prs.o" "./gecko_sdk_4.1.2/platform/emlib/src/em_rtcc.o" "./gecko_sdk_4.1.2/platform/emlib/src/em_se.o" "./gecko_sdk_4.1.2/platform/emlib/src/em_system.o" "./gecko_sdk_4.1.2/platform/emlib/src/em_usart.o" "./gecko_sdk_4.1.2/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.o" "./gecko_sdk_4.1.2/platform/radio/rail_lib/plugin/pa-conversions/pa_curves_efr32.o" "./gecko_sdk_4.1.2/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.o" "./gecko_sdk_4.1.2/platform/radio/rail_lib/plugin/rail_util_rf_path/sl_rail_util_rf_path.o" "./gecko_sdk_4.1.2/platform/service/device_init/src/sl_device_init_emu_s2.o" "./gecko_sdk_4.1.2/platform/service/device_init/src/sl_device_init_hfrco.o" "./gecko_sdk_4.1.2/platform/service/device_init/src/sl_device_init_hfxo_s2.o" "./gecko_sdk_4.1.2/platform/service/device_init/src/sl_device_init_lfxo_s2.o" "./gecko_sdk_4.1.2/platform/service/device_init/src/sl_device_init_nvic.o" "./gecko_sdk_4.1.2/platform/service/hfxo_manager/src/sl_hfxo_manager.o" "./gecko_sdk_4.1.2/platform/service/hfxo_manager/src/sl_hfxo_manager_hal_s2.o" "./gecko_sdk_4.1.2/platform/service/iostream/src/sl_iostream.o" "./gecko_sdk_4.1.2/platform/service/iostream/src/sl_iostream_retarget_stdio.o" "./gecko_sdk_4.1.2/platform/service/iostream/src/sl_iostream_stdlib_config.o" "./gecko_sdk_4.1.2/platform/service/iostream/src/sl_iostream_uart.o" "./gecko_sdk_4.1.2/platform/service/iostream/src/sl_iostream_usart.o" "./gecko_sdk_4.1.2/platform/service/mpu/src/sl_mpu.o" "./gecko_sdk_4.1.2/platform/service/power_manager/src/sl_power_manager.o" "./gecko_sdk_4.1.2/platform/service/power_manager/src/sl_power_manager_debug.o" "./gecko_sdk_4.1.2/platform/service/power_manager/src/sl_power_manager_hal_s2.o" "./gecko_sdk_4.1.2/platform/service/sleeptimer/src/sl_sleeptimer.o" "./gecko_sdk_4.1.2/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.o" "./gecko_sdk_4.1.2/platform/service/sleeptimer/src/sl_sleeptimer_hal_prortc.o" "./gecko_sdk_4.1.2/platform/service/sleeptimer/src/sl_sleeptimer_hal_rtcc.o" "./gecko_sdk_4.1.2/platform/service/system/src/sl_system_init.o" "./gecko_sdk_4.1.2/platform/service/system/src/sl_system_process_action.o" "./gecko_sdk_4.1.2/protocol/bluetooth/src/sl_bt_stack_init.o" "./gecko_sdk_4.1.2/protocol/bluetooth/src/sli_bt_advertiser_config.o" "./gecko_sdk_4.1.2/protocol/bluetooth/src/sli_bt_channel_sounding_config.o" "./gecko_sdk_4.1.2/protocol/bluetooth/src/sli_bt_connection_config.o" "./gecko_sdk_4.1.2/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.o" "./gecko_sdk_4.1.2/protocol/bluetooth/src/sli_bt_l2cap_config.o" "./gecko_sdk_4.1.2/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.o" "./gecko_sdk_4.1.2/protocol/bluetooth/src/sli_bt_periodic_adv_config.o" "./gecko_sdk_4.1.2/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.o" "./gecko_sdk_4.1.2/protocol/bluetooth/src/sli_bt_sync_config.o" "./gecko_sdk_4.1.2/util/silicon_labs/silabs_core/memory_manager/sl_malloc.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/cipher.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/cipher_wrap.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/constant_time.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/platform.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/platform_util.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/psa_crypto.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/psa_crypto_aead.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/psa_crypto_cipher.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/psa_crypto_client.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/psa_crypto_driver_wrappers.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/psa_crypto_ecp.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/psa_crypto_hash.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/psa_crypto_mac.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/psa_crypto_rsa.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/psa_crypto_se.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/psa_crypto_slot_management.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/psa_crypto_storage.o" "./gecko_sdk_4.1.2/util/third_party/crypto/mbedtls/library/threading.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/se_manager/src/sl_se_manager.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/se_manager/src/sl_se_manager_attestation.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/se_manager/src/sl_se_manager_cipher.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/se_manager/src/sl_se_manager_entropy.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/se_manager/src/sl_se_manager_hash.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/se_manager/src/sl_se_manager_key_derivation.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/se_manager/src/sl_se_manager_key_handling.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/se_manager/src/sl_se_manager_signature.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/se_manager/src/sl_se_manager_util.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_mbedtls_support/src/sl_mbedtls.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_radioaes.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_protocol_crypto/src/sli_radioaes_management.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sl_psa_its_nvm3.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_psa_driver_common.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_psa_driver_init.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_psa_trng.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_driver_aead.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_driver_builtin_keys.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_driver_cipher.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_driver_key_derivation.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_driver_key_management.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_driver_mac.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_driver_signature.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_opaque_driver_aead.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_opaque_driver_cipher.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_opaque_driver_mac.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_opaque_key_derivation.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_transparent_driver_aead.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_transparent_driver_cipher.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_transparent_driver_hash.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_transparent_driver_mac.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_transparent_key_derivation.o" "./gecko_sdk_4.1.2/util/third_party/crypto/sl_component/sl_psa_driver/src/sli_se_version_dependencies.o" "/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_4_1_2//protocol/bluetooth/lib/EFR32MG21/GCC/libbluetooth.a" "/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_4_1_2//platform/emdrv/nvm3/lib/libnvm3_CM33_gcc.a" "/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_4_1_2//platform/radio/rail_lib/autogen/librail_release/librail_efr32xg21_gcc_release.a" -lgcc -lc -lm -lnosys -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: conn_interval_central_CI.hex'
	arm-none-eabi-objcopy -O ihex "conn_interval_central_CI.axf" "conn_interval_central_CI.hex"
	@echo ' '

	@echo 'Building bin file: conn_interval_central_CI.bin'
	arm-none-eabi-objcopy -O binary "conn_interval_central_CI.axf" "conn_interval_central_CI.bin"
	@echo ' '

	@echo 'Building s37 file: conn_interval_central_CI.s37'
	arm-none-eabi-objcopy -O srec "conn_interval_central_CI.axf" "conn_interval_central_CI.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "conn_interval_central_CI.axf" -A
	@echo ' '

# Other Targets
clean:
	-@$(foreach FILE, $(EXECUTABLES), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(OBJS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C_DEPS), $(shell $(RM) $(FILE)) )
	-$(RM) conn_interval_central_CI.axf
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
