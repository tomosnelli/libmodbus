from pymodbus.server.async_io import StartTcpServer
from pymodbus.datastore import ModbusSequentialDataBlock, ModbusSlaveContext, ModbusServerContext
import random

# Define the Modbus registers
coils = ModbusSequentialDataBlock(1, [False] * 100)
discrete_inputs = ModbusSequentialDataBlock(1, [False] * 100)
holding_registers = ModbusSequentialDataBlock(1, [0] * 100)
input_registers = ModbusSequentialDataBlock(1, [0] * 100)

# Simulate some temperature and flow values
temperature_values = [random.uniform(4, 15) for _ in range(7)]
flow_values = [random.uniform(-1, 1) for _ in range(2)]

# Set the simulated values in holding registers
holding_registers.setValues(0, temperature_values)
holding_registers.setValues(10, flow_values)

# Create the Modbus slave context
slave_context = ModbusSlaveContext(
    di=discrete_inputs,
    co=coils,
    hr=holding_registers,
    ir=input_registers
)

# Create the Modbus server context
server_context = ModbusServerContext(slaves=slave_context, single=True)

# Run the server
StartTcpServer(context=server_context, address=("localhost", 5020))

