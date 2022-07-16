# Todo
- Finish remote server listener command execution
- Parsing error for multiple requests
- Caching for remote data requests
Just beware of cache invalidation with SET and DELETE commands

# Concept
- Remote data storage interface
- Proxy for the data storage will work as a remote and caching proxy
- The client will only store and retrieve some data: GET, SET, DELETE
