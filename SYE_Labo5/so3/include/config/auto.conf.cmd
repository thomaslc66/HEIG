deps_config := \
	ipc/Kconfig \
	fs/Kconfig \
	apps/Kconfig \
	drivers/mmc/Kconfig \
	drivers/Kconfig \
	mm/Kconfig \
	arch/arm/devices/Kconfig \
	arch/arm/vexpress/Kconfig \
	arch/arm/Kconfig \
	Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
