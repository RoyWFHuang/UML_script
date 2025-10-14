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
    ptr = (ptr - 5);
    ptr[0] = 'a';
    printk(KERN_ALERT "dup str = %s\n", ptr);
}

static int Kasan_init(void)
{
    kasan_heap_underflow();
    kasan_leak_test();
    return 0;
}

static void Kasan_exit(void)
{
    printk(KERN_ALERT "exit\n");
}

module_init(Kasan_init);
module_exit(Kasan_exit);
