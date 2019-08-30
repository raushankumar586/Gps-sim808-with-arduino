import socket
client = socket.socket(socket.AF_INET,socket.SOCK_STREAM) # need to read about these two argument
#ip=socket.gethostbyname(socket.gethostname())
ip1 = '172.31.32.26'
ip2 = '127.0.1.1'
port = 80
address  = (ip2, port)
client.connect(address)
while True:
    client.send("hello raushan\r\n")

