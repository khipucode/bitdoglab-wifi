#ifndef _LWIPOPTS_H
#define _LWIPOPTS_H

// Sem RTOS — polling mode
#define NO_SYS                      1
#define LWIP_SOCKET                 0
#define LWIP_NETCONN                0

// IPv4 apenas
#define LWIP_IPV4                   1
#define LWIP_IPV6                   0

// ARP + DHCP
#define LWIP_ARP                    1
#define LWIP_DHCP                   1
#define LWIP_AUTOIP                 0

// DNS (opcional mas recomendado)
#define LWIP_DNS                    1

// Tamanhos de memória
#define MEM_SIZE                    4000
#define MEMP_NUM_TCP_SEG            16
#define MEMP_NUM_ARP_QUEUE          10
#define PBUF_POOL_SIZE              24
#define LWIP_ARP_TABLE_SIZE         10

// TCP/UDP básico
#define LWIP_TCP                    1
#define LWIP_UDP                    1
#define LWIP_ICMP                   1

// Callbacks e timers
#define LWIP_TIMERS                 1
#define LWIP_TIMERS_CUSTOM          0

// Checksum via hardware quando disponível
#define CHECKSUM_BY_HARDWARE        0

// Stats desabilitados para economizar memória
#define LWIP_STATS                  0
#define LWIP_STATS_DISPLAY          0

// Netif
#define LWIP_NETIF_HOSTNAME         1
#define LWIP_NETIF_STATUS_CALLBACK  1
#define LWIP_NETIF_LINK_CALLBACK    1

// Sem loopback
#define LWIP_HAVE_LOOPIF            0
#define LWIP_LOOPBACK_MAX_PBUFS     0

// SYS_ARCH — sem RTOS
#define SYS_LIGHTWEIGHT_PROT        0

#endif // _LWIPOPTS_H
