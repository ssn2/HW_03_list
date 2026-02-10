/*
 *
 *
 *
 *
 */

#define pr_fmt(fmt) KBUILD_MODNAME ":" fmt

#include "../inc/kernel_stack.h"


ssize_t push_show(struct device *dev,
		struct device_attribute *attr, 
		char *buf){
    static int k = 0;
    return sprintf(buf, "УУУУУУРРРРАААА!  %d\n", k++);
}


ssize_t push_store(struct device *dev, struct device_attribute *attr, 
                    const char *buf, size_t count){
    int new_value;
    if (kstrtoint(buf, 10, &new_value))
        return -EINVAL;

    printk(KERN_INFO "Got new value: %d\n", new_value);
    return count;
}







