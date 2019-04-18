import serial
from time import sleep

ser = serial.Serial('/dev/ttyUSB0', 9600)

def main():
    arduino('Drive,10')
    
    
def arduino(command):
    ser.write(str.encode(command))
    sleep(1)
    
    string = str(ser.readline());
    print(string)

if __name__ == "__main__" :
    main()