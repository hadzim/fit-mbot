#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x84b3ef83, "module_layout" },
	{ 0x6d044c26, "param_ops_uint" },
	{ 0x1976aa06, "param_ops_bool" },
	{ 0xb05f0bc4, "usb_deregister" },
	{ 0x8c03d20c, "destroy_workqueue" },
	{ 0x70e316b2, "usb_register_driver" },
	{ 0x43a53735, "__alloc_workqueue_key" },
	{ 0x17b518f, "dev_warn" },
	{ 0x446d3b08, "release_firmware" },
	{ 0xcf63860d, "request_firmware" },
	{ 0x91715312, "sprintf" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xd0d8621b, "strlen" },
	{ 0x30cc3746, "usb_control_msg" },
	{ 0xfe31e381, "sysfs_create_group" },
	{ 0x387cccbe, "__mutex_init" },
	{ 0x43ff78f1, "kmem_cache_alloc_trace" },
	{ 0x1cb9af37, "kmalloc_caches" },
	{ 0x2732f360, "netdev_info" },
	{ 0x8834396c, "mod_timer" },
	{ 0x16a858c1, "netif_carrier_off" },
	{ 0x37fda87b, "alloc_can_err_skb" },
	{ 0x374dbb72, "netif_device_detach" },
	{ 0xa14651f1, "can_free_echo_skb" },
	{ 0xa23fb771, "consume_skb" },
	{ 0xdefe6d6e, "can_put_echo_skb" },
	{ 0xcbcafc1b, "kfree_skb" },
	{ 0xa65c873b, "close_candev" },
	{ 0x170c5fbe, "netdev_warn" },
	{ 0x679bb247, "netdev_err" },
	{ 0xd9adb844, "usb_alloc_coherent" },
	{ 0x5412e3e, "usb_alloc_urb" },
	{ 0x360f39d5, "open_candev" },
	{ 0x8c4db1b5, "usb_kill_anchored_urbs" },
	{ 0xd02297c6, "usb_free_urb" },
	{ 0x52367d6a, "usb_kill_urb" },
	{ 0x1493e20, "__netif_schedule" },
	{ 0x7d11c268, "jiffies" },
	{ 0xe05260e5, "usb_free_coherent" },
	{ 0x9d2c73d9, "usb_unanchor_urb" },
	{ 0x93f14fff, "netif_rx" },
	{ 0x2a63437b, "alloc_can_skb" },
	{ 0x9c08276, "usb_submit_urb" },
	{ 0xa3503bfc, "usb_anchor_urb" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x1ebfee02, "can_get_echo_skb" },
	{ 0x54a9db5f, "_kstrtoul" },
	{ 0xcd76c5bb, "mutex_unlock" },
	{ 0x60e7fafc, "usb_bulk_msg" },
	{ 0x2e60bace, "memcpy" },
	{ 0x1b8479a3, "mutex_lock" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x57ce975, "hex_dump_to_buffer" },
	{ 0x50eedeb8, "printk" },
	{ 0x43f032f, "netdev_printk" },
	{ 0x92c90e22, "queue_work" },
	{ 0xa9d60ffb, "dev_err" },
	{ 0xae7c44b6, "register_candev" },
	{ 0x68dfc59f, "__init_waitqueue_head" },
	{ 0xe6412060, "alloc_candev" },
	{ 0xb2c14c0, "dev_printk" },
	{ 0x37a0cba, "kfree" },
	{ 0xc02ad26, "dev_set_drvdata" },
	{ 0x3e4db22e, "sysfs_remove_group" },
	{ 0xaa9c5ee5, "free_candev" },
	{ 0xd5cac943, "unregister_netdev" },
	{ 0xcb420861, "_dev_info" },
	{ 0x7928e387, "dev_get_drvdata" },
	{ 0xb81960ca, "snprintf" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=can-dev";

MODULE_ALIAS("usb:v0878p1103d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0878p1104d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0878p1105d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0878p1121d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0878p1122d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0878p1144d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0878p1145d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0878p1101d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0878p1181d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "4D6AAC82090AD38BEC8B1CA");
