import socket
client = socket.socket(socket.AF_INET,socket.SOCK_STREAM) # need to read about these two argument
#ip=socket.gethostbyname(socket.gethostname())
ec2_IP= '52.66.180.46'

port = 80
address  = (ec2_IP, port)
client.connect(address)
while True:
    client.send("hello raushan\r\n")

