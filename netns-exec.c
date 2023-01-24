#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "namespace.h"

#define die(fmt, ...) do { \
    fprintf(stderr, "netns-exec: " fmt "\n", ##__VA_ARGS__); \
    exit(1); \
} while(0)

inline static
void drop_privileges() {
    int gid = getgid();
    int uid = getuid();

    if (setgid(gid) < 0)
        die("setgid: %s\n", strerror(errno));
    if (setuid(uid) < 0)
	die("setuid: %s\n", strerror(errno));
}

inline static void usage() {
    fprintf(stderr, "usage: netns-exec <namespace> <executable> [args...]\n");
    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc < 3)
        usage();

    if (geteuid() != 0)
        die("this program doesn't have root permissions! (are you sure SUID bit is set?)");

    char* ns = argv[1];
    if (netns_switch(ns) == -1)
        exit(1);

    drop_privileges();

    char** args = argv + 2;
    execvp(args[0], args);

    die("failed to execute: %s", strerror(errno));
    return 1;
}
