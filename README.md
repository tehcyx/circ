# circ
IRC server written in C (project to get hands on C networking) using sqlite

# Test Clients
I'm currently using [Colloquy](http://colloquy.info/) to test connecting to the server.

### Currently Supported Commands
* Connection registration [Connection registration](https://tools.ietf.org/html/rfc1459#section-4.1)
  * `PASS secretpass` [Password message](https://tools.ietf.org/html/rfc1459#section-4.1.1)
  * `NICK tehcyx [ <hopcount> ]` [Nick message](https://tools.ietf.org/html/rfc1459#section-4.1.2) - hopcount actually not yet supported
  * `QUIT [<Quit message>]` [Quit](https://tools.ietf.org/html/rfc1459#section-4.1.6) - Quit message not supported
  * more coming soon...

### Upcoming Features
* Connection registration [Connection registration](https://tools.ietf.org/html/rfc1459#section-4.1)
  * `USER <username> <hostname> <servername> <realname>` [User message](https://tools.ietf.org/html/rfc1459#section-4.1.3)
  * `OPER <user> <password>` [Oper](https://tools.ietf.org/html/rfc1459#section-4.1.5)
* Channel operations [Channel operations](https://tools.ietf.org/html/rfc1459#section-4.2)
  * `JOIN <channel>{,<channel>} [<key>{,<key>}]` [Join message](https://tools.ietf.org/html/rfc1459#section-4.2.1)
  * `PART <channel>{,<channel>}` [Part message](https://tools.ietf.org/html/rfc1459#section-4.2.2)
  * `MODE` [Mode message](https://tools.ietf.org/html/rfc1459#section-4.2.3)
    * `<channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]` [Channel modes](https://tools.ietf.org/html/rfc1459#section-4.2.3.1)
    * `<nickname> {[+|-]|i|w|s|o}` [User modes](https://tools.ietf.org/html/rfc1459#section-4.2.3.2)
  * `TOPIC <channel> [<topic>]` [Topic message](https://tools.ietf.org/html/rfc1459#section-4.2.4)

### Far Future
* `SERVER <servername> <hopcount> <info>` [Server message](https://tools.ietf.org/html/rfc1459#section-4.1.4)
* `SQUIT <server> <comment>` [Server quit message](https://tools.ietf.org/html/rfc1459#section-4.1.7)

# RFCs used
* [RFC1459](https://tools.ietf.org/html/rfc1459)
