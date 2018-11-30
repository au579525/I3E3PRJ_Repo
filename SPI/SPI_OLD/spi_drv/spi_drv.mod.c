#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x83f9a31d, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xf2a33d1c, __VMLINUX_SYMBOL_STR(spi_bus_type) },
	{ 0x4724de41, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0x6bc3fbc0, __VMLINUX_SYMBOL_STR(__unregister_chrdev) },
	{ 0x9b62a035, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0xca37bda2, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x2927758, __VMLINUX_SYMBOL_STR(__spi_register_driver) },
	{ 0x3ff2e168, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0xf13781a7, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xc31596a7, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0xb52aa66f, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0xcbdbb617, __VMLINUX_SYMBOL_STR(spi_setup) },
	{ 0xc783e105, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x9912916d, __VMLINUX_SYMBOL_STR(spi_sync) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "1BD57F2A27B9B897AF40EDB");
