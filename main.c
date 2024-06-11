#include <stdio.h>
#include "utils.h"

int main() {
    printf("Distro Information\n\n");

    // Display system information
    display_os_info();
    display_kernel_info();
    display_cpu_info();
    display_gpu_info();
    display_memory_usage();
    display_disk_usage();
    display_desktop_env_and_version();
    return 0;
}
