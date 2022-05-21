filepath = input('What file: ')
lines = []

with open(filepath, "r") as f:
    lines = f.readlines()

out_file = open("rom.bin", "wb")

for line in lines:
    command = line.split(" ")[0]
    params = int(line.split(" ")[1]).to_bytes(length=1, byteorder='big')

    if command.startswith("LDA"):
        out_file.write(0xA1.to_bytes(length=1, byteorder='big'))
    elif command.startswith("LDX"):
        out_file.write(0xA2.to_bytes(length=1, byteorder='big'))
    elif command.startswith("LDY"):
        out_file.write(0xA3.to_bytes(length=1, byteorder='big'))
    elif command.startswith("PTS"):
        out_file.write(0x8B.to_bytes(length=1, byteorder='big'))
    elif command.startswith("ADD"):
        out_file.write(0xE4.to_bytes(length=1, byteorder='big'))
    elif command.startswith("INC"):
        out_file.write(0x5A.to_bytes(length=1, byteorder='big'))
    elif command.startswith("END"):
        out_file.write(0xFF.to_bytes(length=1, byteorder='big'))

    out_file.write(params)