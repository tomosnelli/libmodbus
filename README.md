# Compiling and linking libmodbus on MacOS
For libmodbus installations via homebrew...
```bash
gcc modbus_client.c -o master -I/opt/homebrew/Cellar/libmodbus/3.1.11/include -L/opt/homebrew/Cellar/libmodbus/3.1.11/lib -lmodbus
```

for linux installations...
```bash
gcc modbus_client.c -o slave -lmodbus
```