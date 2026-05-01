#include <linux/module.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

static struct timer_list my_timer;

static void timer_callback(struct timer_list *t)
{
	pr_info("My Driver WHHS : Timer interrupt handles!\n");
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000)); // timer restart

}

static int __init driver_init(void)
{
	pr_info("My driver WHHS : INIALIZED!\n");
	timer_setup(&my_timer, timer_callback,0);
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000));
	return 0;
}

static void __exit driver_exit(void)
{
	timer_shutdown_sync(&my_timer);
	pr_info("Timer Deleted!\n");
}


module_init(driver_init);
module_exit(driver_exit);
MODULE_LICENSE("GPL");
