#!/usr/bin/env python3
'''Defines the request handler class that handles the server role'''
from xmlrpc.server import SimpleXMLRPCServer
from xmlrpc.server import SimpleXMLRPCRequestHandler


class RequestHandler(SimpleXMLRPCRequestHandler):
    rpc_paths = ('/RPC2',)

# Create server
with SimpleXMLRPCServer(('localhost', 8000),
                        requestHandler=RequestHandler) as server:
    server.register_introspection_functions()

    # Procedure 1
    def increment_integer(value):
        return value + 1
    server.register_function(increment_integer, 'increment_integer')

    # Procedure 2
    def square_and_add(floating_point, integer):
        return floating_point ** 2 + integer
    server.register_function(square_and_add, 'square_and_add')

    # Procedure 3
    def reverse_string(input_string):
        return input_string[::-1]
    server.register_function(reverse_string, 'reverse_string')

    print("Server ready to accept requests on port 8000...")
    # Run the server's main loop
    server.serve_forever()

