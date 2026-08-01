*This project has been created as part of the 42 curriculum by malebrun, edi-maio.*

# ft_irc

## Description

`ft_irc` is an IRC (Internet Relay Chat) server written from scratch in C++98, following
the behaviour described by the IRC protocol specifications (RFC 1459 / RFC 2812).

IRC is a text-based communication protocol that provides real-time public and private
messaging. Clients connect to a server over TCP/IP, register with a nickname and a
username, and can then exchange private messages or join channels where every message is
broadcast to all members.

This project implements the **server side only**: no client is provided, and
server-to-server communication is not implemented. Any standard IRC client can connect to
it — our reference client is **HexChat** — as well as raw tools such as `nc`.

The server is fully **single-threaded and non-blocking**. All sockets — the listening
socket and every client socket — are monitored by a single `poll()` call. No `fork()`, no
threads, and no blocking I/O are used anywhere in the project.

Both bonus features are implemented: **file transfer** and a **bot**.

## Instructions

### Requirements

- A C++ compiler supporting C++98 (`c++` / `clang++` / `g++`)
- `make`
- A POSIX system (Linux or macOS)

### Compilation

```bash
make        # builds ./ircserv (mandatory part)
make bonus  # builds the server with the bonus features
make clean  # removes object files
make fclean # removes object files and the binary
make re     # fclean + all
```

The project is compiled with `-Wall -Wextra -Werror -std=c++98`.

### Execution

```bash
./ircserv <port> <password>
```

- `port`: the TCP port the server listens on (e.g. `6667`)
- `password`: the connection password every client must provide with the `PASS` command

Example:

```bash
./ircserv 6667 mypassword
```

### Connecting with HexChat

1. *Network List* → **Add**, name the network (e.g. `ft_irc`), then **Edit**.
2. Set the server to `localhost/6667`.
3. Set the **Password** field to the password given to `./ircserv`.
4. Uncheck *Use SSL for all servers on this network*.
5. **Connect**, then `/join #general`.

### Connecting with `nc` (raw protocol)

```bash
nc -C 127.0.0.1 6667
PASS mypassword
NICK alice
USER alice 0 * :Alice
JOIN #general
PRIVMSG #general :hello world
```

Commands sent in several fragments are buffered per client and only processed once a
complete line (`\r\n` or `\n`) has been received.

## Features

### Registration

| Command | Description |
| --- | --- |
| `PASS` | Provide the server connection password |
| `NICK` | Set or change the nickname |
| `USER` | Set the username and real name |
| `QUIT` | Disconnect from the server |

Registration is only complete once `PASS`, `NICK` and `USER` have all been received; until
then, any other command is rejected.

### Messaging and channels

| Command | Description |
| --- | --- |
| `JOIN` | Join a channel (creating it if needed) |
| `PART` | Leave a channel |
| `PRIVMSG` | Send a message to a user or to a channel |

Every message sent to a channel is forwarded to all its other members.

### Channel operator commands

| Command | Description |
| --- | --- |
| `KICK` | Eject a client from the channel |
| `INVITE` | Invite a client to a channel |
| `TOPIC` | View or change the channel topic |
| `MODE` | Change the channel modes |

Supported channel modes:

- `i` — invite-only channel
- `t` — restrict `TOPIC` to channel operators
- `k` — set/remove the channel key (password)
- `o` — give/take channel operator privilege
- `l` — set/remove the user limit

The client who creates a channel becomes its first operator.

## Bonus

### File transfer

Clients can send files to each other through the server. The transfer is negotiated with
the usual IRC mechanism, the server relaying the negotiation between the two clients so
that a standard client such as HexChat can accept the file without any custom setup.

### Bot

A bot is connected to the server and answers commands sent to it in a channel or in
private. It behaves like a regular client from the server's point of view: it registers,
joins channels, and reacts to `PRIVMSG`.

Both are built with `make bonus`.

## Technical choices

### Event loop

A single `poll()` call monitors every file descriptor: the listening socket and all client
sockets. `POLLIN` on the listening socket means a new connection to `accept()`; `POLLIN` on
a client socket means data to `recv()`. Nothing is ever read or written outside of this
loop, and `errno` is never used to decide what to do after a `recv()`/`send()`.

### Partial data handling

TCP is a stream protocol: a single `recv()` may return half a command, or several commands
at once. Each client therefore owns an input buffer. Received bytes are appended to it, and
only complete lines are extracted and executed; the remainder stays buffered for the next
read.

### Command architecture

Commands are implemented as classes deriving from a common `Command` base class
(`JoinCommand`, `PassCommand`, `NickCommand`, `UserCommand`, `QuitCommand`,
`PrivmsgCommand`, `ModeCommand`, `TopicCommand`, `PartCommand`, `KickCommand`,
`InviteCommand` in `srcs/Commands/`). `Server::handle_input` parses the raw line into a
prefix, a command name and its parameters, then dispatches it to the matching command
object. Adding a new command means adding a class, not extending a growing `if/else`
chain.

### Replies

Server responses follow the standard IRC numeric replies (`001 RPL_WELCOME`,
`403 ERR_NOSUCHCHANNEL`, `433 ERR_NICKNAMEINUSE`, `482 ERR_CHANOPRIVSNEEDED`, ...). A
helper, `Server::sendError(fd, code, nickname, arg)`, formats and sends them consistently.

### Project structure

```
.
├── Makefile
├── includes/     # headers (Server, Client, Channel, Command, ...)
└── srcs/
    ├── main.cpp
    ├── Commands/ # one class per IRC command
    └── ...
```

## Resources

### Documentation

- [RFC 1459 — Internet Relay Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC 2812 — IRC Client Protocol](https://datatracker.ietf.org/doc/html/rfc2812)
- [Modern IRC Client Protocol](https://modern.ircdocs.horse/) — a readable, up-to-date
  consolidation of the RFCs
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/) — sockets, `poll()`,
  and TCP basics
- `man` pages: `socket(2)`, `bind(2)`, `listen(2)`, `accept(2)`, `poll(2)`, `recv(2)`,
  `send(2)`, `fcntl(2)`

### Use of AI

AI tools were used as a documentation and explanation aid, never as a code generator. The
implementation was written by hand by both authors.

Specifically, AI was used to:

- clarify parts of the IRC protocol (registration order, numeric reply codes, message
  format) when the RFCs were ambiguous;
- explain socket and `poll()` semantics, in particular non-blocking I/O and partial reads;
- help diagnose C++ compilation and design problems, such as circular include chains
  between headers and the choice between storing references and pointers in containers;
- review and rephrase parts of this README.

## Authors

- malebrun
- edi-maio
