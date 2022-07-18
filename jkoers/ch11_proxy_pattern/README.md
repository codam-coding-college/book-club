# The proxy pattern

As exercise I'll build a RPC(Remote procedure call) system in c++

## Usage
```bash
make
./rpc server 4242

# in different terminal run client
./rpc client 172.0.0.1 4242
```

## Goals
- Making it as universal as possible, so it can be used in as many scenarios as possible
- Type safe
- Super fast

### Bonus goals
- Some kind of async
- Make it a library
