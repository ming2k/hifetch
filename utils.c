#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to execute a command and return the output
char* execute_command(const char* cmd) {
    char buffer[128];
    char* result = malloc(1024 * sizeof(char));
    result[0] = '\0';

    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        strcat(result, buffer);
    }
    pclose(pipe);

    return result;
}

// Display operating system information
void display_os_info() {
    char* os_info = execute_command("lsb_release -a 2>/dev/null | grep 'Description' | cut -f2");
    printf("OS: %s", os_info);
    free(os_info);
}

// Display kernel information
void display_kernel_info() {
    char* kernel_info = execute_command("uname -r");
    printf("Kernel: %s", kernel_info);
    free(kernel_info);
}

// Display CPU information
void display_cpu_info() {
    char* cpu_info = execute_command("lscpu | grep 'Model name' | cut -d ':' -f2 | tr -d '\\n' | sed 's/^ *//'");
    printf("CPU: %s\n", cpu_info);
    free(cpu_info);
}

// Display GPU information
void display_gpu_info() {
    char* gpu_info = execute_command("lspci | grep -i 'vga' | cut -d ':' -f3 | tr -d '\\n' | sed 's/^ *//'");
    if (gpu_info && strlen(gpu_info) > 0) {
        printf("GPU: %s\n", gpu_info);
    } else {
        printf("GPU: Unknown\n");
    }
    free(gpu_info);
}

// Display memory usage information
void display_memory_usage() {
    char* mem_info = execute_command("free -h | grep 'Mem:' | awk '{print $3\"/\"$2}' | tr -d '\\n'");
    printf("Memory Usage: %s\n", mem_info);
    free(mem_info);
}

// Display disk usage information
void display_disk_usage() {
    char* disk_info = execute_command("df -h | awk '$NF==\"/\"{printf \"%s/%s\", $3, $2}'");
    printf("Disk Usage: %s\n", disk_info);
    free(disk_info);
}

// Function to detect the desktop environment and its version
void display_desktop_env_and_version() {
    char* desktop_env = execute_command("echo $XDG_CURRENT_DESKTOP");

    if (desktop_env && strlen(desktop_env) > 0) {
        if (strstr(desktop_env, "GNOME") != NULL) {
            char* gnome_version = execute_command("gnome-shell --version");
            printf("Desktop: %s\n", gnome_version);
            free(gnome_version);
        } else if (strstr(desktop_env, "KDE") != NULL || strstr(desktop_env, "Plasma") != NULL) {
            char* kde_version = execute_command("plasmashell --version");
            printf("Desktop: %s\n", kde_version);
            free(kde_version);
        } else {
            printf("Desktop: Unknown\n");
        }
    } else {
        printf("Desktop: Unknown\n");
    }

    free(desktop_env);
}
