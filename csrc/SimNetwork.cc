#include <vpi_user.h>
#include <svdpi.h>

#include "network.h"

class NetworkDevice *netdev = NULL;

extern "C" void network_tick(
        unsigned char out_valid,
        unsigned char *out_ready,
        long long     out_data,
        unsigned char out_last,

        unsigned char *in_valid,
        unsigned char in_ready,
        long long     *in_data,
        unsigned char *in_last)
{
    if (!netdev) {
        netdev = new NetworkDevice();
    }

    netdev->tick(out_valid, out_data, out_last, in_ready);
    netdev->switch_to_host();

    *out_ready = netdev->out_ready();
    *in_valid = netdev->in_valid();
    *in_data = netdev->in_data();
    *in_last = netdev->in_last();
}
