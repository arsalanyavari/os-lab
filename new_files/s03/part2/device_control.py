#!/bin/python3

import os
import sys

def read_from_file(fd: int):
    init_data = os.read(fd, 1024)
    print(init_data.decode())

def write_to_file(fd: int, cmd: str):
    os.write(fd, cmd.encode())

def main():
    fd = os.open("/dev/iut_device", os.O_RDWR)
    buffer = sys.argv[1] + "," + sys.argv[2] + "," + sys.argv[3] + "," + sys.argv[4]
    print(buffer)
    write_to_file(fd, buffer)
    read_from_file(fd)
    os.close(fd)

if __name__ == "__main__":
    main()
