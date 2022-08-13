# Socket
Streaming interface for socket connections

- listening for incoming connections
- connecting to an address

### Example
```C++
// server side, accept connections
TcpListener listener;
listener.init("127.0.0.1", 3000);
TcpStream stream = listener.accept();
...

// client side, connect to server
TcpStream stream = net::connect("127.0.0.1", 3000);
...
```

## TcpListener
- Class for binding to a socket and accepting connections from it
- Blocking accept function that returns a TcpStream instance

## TcpStream
- Stream class wrapper around a socket connection

# Todo
- TcpListener:
	- Options struct/flags for binding and accepting
- Socket:
	- make reference counted fd using fd table for cheap cloning/copying, splitting socket into r/w halves, etc
