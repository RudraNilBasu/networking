# Math Server using TCP

### Usage

From first terminal

```
gcc server.c -o _server
./_server 8000
```

From another terminal

```
gcc client.c -o _client
./_client 127.0.0.1 8000
```

### Example usage

```
Please enter the message: 2
Recieved
Please enter the message: +
Recieved
Please enter the message: 2
Result: 4.000000
```
