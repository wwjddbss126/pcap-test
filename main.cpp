#include <pcap.h>
#include <stdbool.h>
#include <stdio.h>
#include <netinet/ether.h> // for ether_header
#include <netinet/ip.h> // for ip
#include <netinet/tcp.h> // for tcphdr

void usage() {
    printf("syntax: pcap-test <interface>\n");
    printf("sample: pcap-test wlan0\n");
}

typedef struct {
    char* dev_;
} Param;

Param param  = {
    .dev_ = NULL
};

bool parse(Param* param, int argc, char* argv[]) {
    if (argc != 2) {
        usage();
        return false;
    }
    param->dev_ = argv[1];
    return true;
}

int main(int argc, char* argv[]) {
    if (!parse(&param, argc, argv))
        return -1;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* pcap = pcap_open_live(param.dev_, BUFSIZ, 1, 1000, errbuf);

    if (pcap == NULL) {
        fprintf(stderr, "pcap_open_live(%s) return null - %s\n", param.dev_, errbuf);
        return -1;
    }

    while (true) {
        struct pcap_pkthdr* header;
        const u_char* packet;
        int res = pcap_next_ex(pcap, &header, &packet);
        if (res == 0) continue;
        if (res == PCAP_ERROR || res == PCAP_ERROR_BREAK) {
            printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(pcap));
            break;
        }
        printf("%u bytes captured\n", header->caplen);
        // eth(ip(tcp))
        printf("\n=========* [%u BYTES PACKET CAPTURED] *=========\n", header->caplen);

        printf("------------* 1. ETH.SRC & ETH.DST *------------\n");
//        00479 struct libnet_ethernet_hdr
//        00480 {
//        00481     u_int8_t  ether_dhost[ETHER_ADDR_LEN];/* destination ethernet address */
//        00482     u_int8_t  ether_shost[ETHER_ADDR_LEN];/* source ethernet address */
//        00483     u_int16_t ether_type;                 /* protocol */
//        00484 };
        struct ether_header* eth;
        eth = (struct ether_header*)(packet);
        printf("eth.src: %02x:%02x:%02x:%02x:%02x:%02x\neth.dst: %02x:%02x:%02x:%02x:%02x:%02x\n",
            eth->ether_shost[0], eth->ether_shost[1], eth->ether_shost[2], eth->ether_shost[3], eth->ether_shost[4], eth->ether_shost[5],
            eth->ether_dhost[0], eth->ether_dhost[1], eth->ether_dhost[2], eth->ether_dhost[3], eth->ether_dhost[4], eth->ether_dhost[5]);

        printf("-------------* 2. IP.SRC & IP.DST *-------------\n");
//        00647 struct libnet_ipv4_hdr
//        00648 {
//        00688     struct in_addr ip_src, ip_dst; /* source and dest address */
//        00689 };
        struct ip* ip;
        ip = (struct ip*)(packet + sizeof(ether_header));
        printf("ip.src: %s\nip.dst: %s\n", inet_ntoa(ip->ip_src), inet_ntoa(ip->ip_dst));

        printf("-----------* 3. PORT.SRC & PORT.DST *-----------\n");
//        01519 struct libnet_tcp_hdr
//        01520 {
//        01521     u_int16_t th_sport;       /* source port */
//        01522     u_int16_t th_dport;       /* destination port */
        struct tcphdr* tcp;
        tcp = (struct tcphdr*)(packet + sizeof(ether_header) + ip->ip_hl * 4);

        printf("port.src: %d\nport.dst: %d\n", ntohs(tcp->th_sport), ntohs(tcp->th_dport));

        printf("---------* 4. HEXA PAYLOAD (8 BYTES) *----------\n");
//        struct tcphdr {
//        #if BYTE_ORDER == LITTLE_ENDIAN
//            u_char	th_x2:4,		/* (unused) */
//                th_off:4;		/* data offset */
//        #endif
//        #if BYTE_ORDER == BIG_ENDIAN
//            u_char	th_off:4,		/* data offset */
//                th_x2:4;		/* (unused) */
//        #endif
//      };
        const u_char* data;
        data = (u_char*)tcp + tcp->th_off * 4; // 32 bit words = 4 bytes // unsigned int th_off:4;
        for (int i = 0; i < 8; i++) {
            printf("0x%02x ", data[i]);
        }

        printf("\n================================================\n");
    }

    pcap_close(pcap);
}
