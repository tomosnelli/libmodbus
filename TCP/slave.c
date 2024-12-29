#include <stdio.h>
#include <modbus/modbus.h>

int main() {
    modbus_t *ctx;
    modbus_mapping_t *mb_mapping;
    int socket;

    ctx = modbus_new_tcp("0.0.0.0", 8080);
    mb_mapping = modbus_mapping_new(2, 2, 2, 2);

    // init mb register
    mb_mapping->tab_registers[0] = 1000;
    mb_mapping->tab_registers[1] = 2000;
    mb_mapping->tab_input_registers[0] = 3000;
    mb_mapping->tab_input_registers[1] = 4000;
    mb_mapping->tab_bits[0] = 1;
    mb_mapping->tab_bits[1] = 0;
    mb_mapping->tab_input_bits[0] = 1;
    mb_mapping->tab_input_bits[1] = 0;

    socket = modbus_tcp_listen(ctx, 1);
    if (socket == -1) {
        fprintf(stderr, "Unable to listen TCP connection\n");
        modbus_free(ctx);
        return -1;
    }

    printf("Listening on port 8080...\n");

    for (;;) {
        modbus_tcp_accept(ctx, &socket);
        uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
        int rc = modbus_receive(ctx, query);
        if (rc > 0) {
            modbus_reply(ctx, query, rc, mb_mapping);
        } else if (rc == -1) {
            // Handle error
            break;
        }
    }

    modbus_mapping_free(mb_mapping);
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}

