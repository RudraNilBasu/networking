# Concurrent server

### Usage

```
gcc server.c -o _server
./_server 6000
```

From another terminal

```
gcc client.c -o _client
./_client 127.0.0.1 6000
```

Run the `./_client 127.0.0.1 6000` command from as many terminals parallely
