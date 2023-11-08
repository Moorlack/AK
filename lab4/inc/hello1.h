// SPDX-License-Identifier: GPL-2.0

#ifndef HELLO1_H
#define HELLO1_H

#include <linux/list.h>
#include <linux/ktime.h>

struct datastr {
	struct list_head list;
	ktime_t time;
	ktime_t duration;
}; //структура даних

void print_hw(unsigned int msg_count);

#endif
