// SPDX-License-Identifier: GPL-2.0

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_AUTHOR("Oleksandr Vasiytynskyi <sych.worker@gmail.com>");
MODULE_DESCRIPTION("hello1 module");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(event_list);
//Статична змінна голови списку

void print_hw(unsigned int msg_count)
{

	int i;

	for (i = 0; i < msg_count; i++) {
		struct datastr *event = kmalloc(sizeof(struct datastr),
							GFP_KERNEL);
		//Занесення у структуру
		//поточного часу ядра
		event->time = ktime_get();
		list_add_tail(&event->list, &event_list);

		pr_info("Hello, world!\n");

		ktime_t time_end = ktime_get();

		event->duration = ktime_sub(time_end, event->time);
	} //Цикл для виведення прінтів
}
EXPORT_SYMBOL(print_hw);

static int __init hello1_init(void)
{
	pr_info("Load hello1 module\n");

	return 0;
}

static void __exit hello1_exit(void)
{
	struct datastr *event, *tmp;
	//Виведення часу подій, очищення
	//структури та звільнення пам'яті
	pr_info("Events:\n");
	list_for_each_entry_safe(event, tmp, &event_list, list) {
		pr_info("Event time: %lld ns. Print duration: %lld ns",
				 ktime_to_ns(event->time),
				 ktime_to_ns(event->duration));
		list_del(&event->list);
		kfree(event);
	}
	pr_info("Remove hello1 module\n");
}


module_init(hello1_init);
module_exit(hello1_exit);
MODULE_ALIAS("hello1");
