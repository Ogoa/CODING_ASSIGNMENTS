#!/usr/bin/env python3
'''Defines the client Q with 3 procedures'''
from xmlrpc.client import ServerProxy

# Create server proxy
server = ServerProxy("http://localhost:8000/RPC2")

# Procedure 1
result_1 = server.increment_integer(5)
print("Procedure 1 result: {}".format(result_1))

# Procedure 2
result_2 = server.square_and_add(2.5, 3)
print("Procedure 2 result: {}".format(result_2))

# Procedure 3
result_3 = server.reverse_string("Hello, World!")
print("Procedure 3 result: {}".format(result_3))
