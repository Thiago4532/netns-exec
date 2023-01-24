// This code was based on "namespace.h" from iproute2
// The license of the original code is GPL-2.0

#ifndef _NETNS_EXEC_NAMESPACE_H_
#define _NETNS_EXEC_NAMESPACE_H_

#include <sched.h>
#include <sys/mount.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

#ifndef NETNS_RUN_DIR
#define NETNS_RUN_DIR "/var/run/netns"
#endif

#ifndef NETNS_ETC_DIR
#define NETNS_ETC_DIR "/etc/netns"
#endif

#ifndef CLONE_NEWNET
#define CLONE_NEWNET 0x40000000	/* New network namespace (lo, device, names sockets, etc) */
#endif

#ifndef MNT_DETACH
#define MNT_DETACH	0x00000002	/* Just detach from the tree */
#endif /* MNT_DETACH */

/* sys/mount.h may be out too old to have these */
#ifndef MS_REC
#define MS_REC		16384
#endif

#ifndef MS_SLAVE
#define MS_SLAVE	(1 << 19)
#endif

#ifndef MS_SHARED
#define MS_SHARED	(1 << 20)
#endif

int netns_switch(char *netns);
int netns_get_fd(const char *netns);
int netns_foreach(int (*func)(char *nsname, void *arg), void *arg);

struct netns_func {
	int (*func)(char *nsname, void *arg);
	void *arg;
};

#endif
