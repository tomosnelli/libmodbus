#include <stdio.h>
#include <stdlib.h>
#include <modbus/modbus.h>
#include <errno.h>

int main() {
    modbus_t *ctx;
    uint16_t *reg_data;
    int rc;

    // Create a Modbus TCP context
    ctx = modbus_new_tcp("192.168.1.35", 8080);  // Replace with server IP and port

    if (ctx == NULL) {
        fprintf(stderr, "Failed to create Modbus context: %s\n", modbus_strerror(errno));
        return -1;
    }

    // Connect to the Modbus server
    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }

    // Allocate memory for reading registers
    reg_data = malloc(5 * sizeof(uint16_t));  // Reading 5 registers

    // Read 5 holding registers starting from address 0
    rc = modbus_read_registers(ctx, 0, 2, reg_data);

    if (rc == -1) {
        fprintf(stderr, "Failed to read registers: %s\n", modbus_strerror(errno));
    } else {
        printf("Read %d registers:\n", rc);
        for (int i = 0; i < rc; i++) {
            printf("Register %d: %d (0x%X)\n", i, reg_data[i], reg_data[i]);
        }
    }

    // Clean up
    free(reg_data);
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}

