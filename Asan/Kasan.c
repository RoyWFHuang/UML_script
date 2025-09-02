#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/kasan.h>
MODULE_LICENSE("GPL");

static char *leakptr = NULL;
static void kasan_leak_test(void)
{
    leakptr = kmalloc(16, GFP_KERNEL);
    strcpy(leakptr, "Leak");
    leakptr = kmalloc(32, GFP_KERNEL);
    leakptr = vmalloc(1024);
    strcpy(leakptr, "Leak2");
    printk(KERN_ALERT "leakptr = %s\n", leakptr);
}

static void kasan_heap_underflow(void)
{
    char *ptr = kmalloc(16, GFP_KERNEL);
    // printk(KERN_ALERT "ptr addr = %p\n", ptr);
    // printk(KERN_ALERT "ptr -10 addr = %p(%px)\n", (ptr - 10), ptr - 10);
    // printk(KERN_ALERT "ptr real addr = %px\n", kasan_reset_tag(ptr));
    // printk(KERN_ALERT "ptr -10 real addr = %px\n", kasan_reset_tag(ptr - 10));
    ptr = (ptr - 10);
    // printk(KERN_ALERT "ptr addr = %p\n", ptr);
    ptr[0] = 'a';
    char *dup = kstrdup(ptr, GFP_KERNEL);
    printk(KERN_ALERT "dup str = %s\n", dup);
}

static int Kasan_init(void)
{
    kasan_heap_underflow();
    kasan_leak_test();
    // kfree(freeptr);
    return 0;
}

static void Kasan_exit(void)
{
    printk(KERN_ALERT "exit\n");
}

module_init(Kasan_init);
module_exit(Kasan_exit);
