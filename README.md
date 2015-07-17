# General Information

Quite long time ago I noticed that electronic parts that I buy are often duplicated in my "local storage" e.g. I buy the same resistors/cap/uCs and so on, that I have already in my desk. I decided then, that I will create an application to store my inventory state. There are lot of applications on the market to do this so why I decided to develop my own app?

## What the application is designer for

* Application should contain a list of available electronic elements, grouped in categories with all the parameters that can describe it
* Application should remember all the items user contains in his inventories, and allows basic operations like move/add/remove item from it
* Application should be able to save BOM of project designed by user, and if needed, check if user can put together this project with parts avalible in storage.
  * Also when some part is missing in inventory, server should give an hint with possible replacements
* And many more...

## Basic application assumptions 
* Postgres database and it's brilliant json fields, for saving a variable number or parameters to each element and, in the future, use GPU for more complicated queries http://www.slideshare.net/kaigai/gpgpu-accelerates-postgresql
* I use https://developers.google.com/protocol-buffers/ (can be used in embedded devices in simple way) as protocol, and QWebSocket for convenience

## Application dependencies

* Common
  * Boost libraries
  * QT5
  * cmake 3.0.2
  * protbuf 2.6.2

* Server
  * https://github.com/rbock/sqlpp11
  * https://github.com/cszawisza/sqlpp11-connector-postgresql It must be my fork of the connector library

* Client application
  * No extra dependencies
  
## Contribute

* Source Code: https://github.com/cszawisza/eedb

## Support

* In case of questions, please create an issue on github, or write me an email ( cszawisza(at)gmail.com )

## License

The project is licensed under the BSD license.
