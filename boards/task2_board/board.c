#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

static int custom_board_early_init(void) {
  printk("Board Initialized\n");
  return 0;
}

SYS_INIT(custom_board_early_init, POST_KERNEL,
         CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);