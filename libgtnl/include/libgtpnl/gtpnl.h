#ifndef _LIBGTPNL_H_
#define _LIBGTPNL_H_

#include <stdint.h>

struct mnl_socket;
struct nlmsghdr;

struct mnl_socket *genl_socket_open(void);
struct nlmsghdr *genl_nlmsg_build_hdr(char *buf, uint16_t type, uint16_t flags,
				      uint32_t seq, uint8_t cmd);
int genl_socket_talk(struct mnl_socket *nl, struct nlmsghdr *nlh, uint32_t seq,
		     int (*cb)(const struct nlmsghdr *nlh, void *data),
		     void *data);
int genl_lookup_family(struct mnl_socket *nl, const char *family);

struct in_addr;

int gtp_dev_create(const char *gtp_ifname, const char *real_ifname,
		   int fd0, int fd1);
int gtp_dev_config(const char *iface, struct in_addr *net, uint32_t prefix);
int gtp_dev_destroy(const char *gtp_ifname);

struct gtp_tunnel;

int gtp_add_tunnel(int genl_id, struct mnl_socket *nl, struct gtp_tunnel *t);
int gtp_del_tunnel(int genl_id, struct mnl_socket *nl, struct gtp_tunnel *t);
int gtp_list_tunnel(int genl_id, struct mnl_socket *nl);

#endif
