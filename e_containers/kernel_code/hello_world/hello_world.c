#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Prerit Oberai");

int init_module(void) {
  printk("\n Hello World \n");
  return 0;
}

void cleanup_module(void) {
  printk("\n Bye! \n");
} 

