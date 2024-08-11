#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x367fcc51, "module_layout" },
	{ 0xc6e25dc2, "cdev_del" },
	{ 0xbe15ede5, "cdev_init" },
	{ 0x4ce2483a, "device_destroy" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x25ec772e, "kthread_create_on_node" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xdab7d900, "kthread_stop" },
	{ 0xfff45d34, "device_create" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x6bfecf8d, "cdev_add" },
	{ 0x800473f, "__cond_resched" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0x296695f, "refcount_warn_saturate" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x1000e51, "schedule" },
	{ 0x92997ed8, "_printk" },
	{ 0xf5a13889, "wake_up_process" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0xd595be2b, "__put_task_struct" },
	{ 0x7fbb56eb, "class_destroy" },
	{ 0x92540fbf, "finish_wait" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0xec8c17d0, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "D6DD99F0D79F1F6878BC834");
