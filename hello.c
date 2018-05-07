#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/net.h>
#include <linux/socket.h>
#include <linux/sockios.h>
#include <linux/in.h>
#include <linux/inet.h>
#include <linux/inetdevice.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <net/snmp.h>
#include <net/ip.h>
#include <net/protocol.h>
#include <net/route.h>
#include <linux/skbuff.h>
#include <net/sock.h>
#include <net/arp.h>
#include <net/icmp.h>
#include <net/raw.h>
#include <net/checksum.h>
#include <net/inet_ecn.h>
#include <linux/netfilter_ipv4.h>
#include <net/xfrm.h>
#include <linux/mroute.h>
#include <linux/netlink.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/string.h>
#include <linux/errno.h>

static int hello_value = 0;
static struct kobject *helloworld_kobj;

static ssize_t hello_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf,"%d\n",hello_value);
}

static ssize_t hello_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	if (count > sizeof(hello_value))
		return -ETOOSMALL;
	sscanf(buf,"%d",&hello_value);

	return count;
}

static struct kobj_attribute hello_value_attribute = __ATTR(hello_value,
										0644, hello_show, hello_store);

static int __init helloworld_init(void)
{
	int retval;
	helloworld_kobj = kobject_create_and_add("helloworld",kernel_kobj);

	if (!helloworld_kobj)
		return -ENOMEM;

	retval = sysfs_create_file(helloworld_kobj, (struct attribute*)&hello_value_attribute);

	if (retval)
		kobject_put(helloworld_kobj);

	return retval;
}

static void __exit helloworld_exit(void)
{
	kobject_put(helloworld_kobj);
}

module_init(helloworld_init);
module_exit(helloworld_exit);
MODULE_LICENSE("GPL");

