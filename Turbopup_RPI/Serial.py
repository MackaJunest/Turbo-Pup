import serial

port="COM13"
baudrate=115200

def COM_INIT():
    global ser
    ser=serial.Serial(port,baudrate,timeout=1)
    print("connected to port:"+port)

def Commander_send(DATA):
    # Create a string with comma-separated values
    data_string = ','.join(str(value) for value in DATA)
    data_string += '\n'  # Add a newline at the end
    
    # Encode the string to bytes and send over serial
    ser.write(data_string.encode())
