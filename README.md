# circ
IRC server written in C (project to get hands on C networking) using sqlite

# Test Clients
I'm currently using [Colloquy](http://colloquy.info/) to test connecting to the server.

### Currently Supported Commands
* `PASS secretpass` [Password message](https://tools.ietf.org/html/rfc1459#section-4.1.1)
* `NICK tehcyx [ <hopcount> ]` [Nick message](https://tools.ietf.org/html/rfc1459#section-4.1.2) - hopcount actually not yet supported
* more coming soon...

### Upcoming Features
* `USER <username> <hostname> <servername> <realname>` [User message](https://tools.ietf.org/html/rfc1459#section-4.1.3)

### Far Future
* `SERVER <servername> <hopcount> <info>` [Server message](https://tools.ietf.org/html/rfc1459#section-4.1.4)

# RFCs used
* [RFC1459](https://tools.ietf.org/html/rfc1459)
