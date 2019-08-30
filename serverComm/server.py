import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
name = socket.gethostname()
ip = socket.gethostbyname(name)
port = 80 

address = (ip, port)

server.bind(address)
server.listen(1) # 1 = one client can connect only
print "server started" + str(ip) + ":" + str(port)
client, clienAaddress = server.accept()
while True:
    data = client.recv(1024)
    print data
