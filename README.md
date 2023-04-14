# Subrute
![alt text](https://i.imgur.com/TJzT3ED.png)

- Supports all kinds of proxies
- Works with http https
- Can save results to txt
- Runs very fast

- [Video test - open](https://www.youtube.com/watch?v=YwNBTRjlamE&feature=youtu.be&ab_channel=lomasterlive)

## Using
```
Subrute: bruteforce URL.

usage: ./sbrute [TARGETS (1,2,3) ] [ARGUMENTS]


arguments main:
  -h, --help            Show this help message and exit.
  -v, --version         Display version information and dependencies.
  --db, --debug         Saving and outputting even pages that are not working.
  -T, --timeout<MS>     Set a delay when receiving a page.
  --protocol <PROTOCOL> Set custom web protocol.
  --error               Display errors.
  
arguments save:
  --txt <FILE>          Save output to txt.

arguments user:
  --set <MODE>          Set style link (see github).
  --base <PATH>         Specify your file with links.
  --user-agent <agent>  Set your user-agent.
```
## Proxy using
```
--proxy http://ip:port
      HTTP Proxy.

--proxy https://ip:port
      HTTPS Proxy.

--proxy socks4://ip:port
      SOCKS4 Proxy.

--proxy socks4a://ip:port
      SOCKS4a Proxy.

--proxy socks5://ip:port
      SOCKS5 Proxy.

--proxy socks5h://ip:port
      SOCKS5 Proxy.
```
## Modes
```
  MODE - a
    prtcl://dns + paths
      Suitable for searching the admin panel.
      
  MODE - b
    prtcl://paths + dns
      Suitable for finding hidden dns, such as cloudflare.
```
## Example
```
./sbrute google.com,yandex.ru --db --txt out.txt

    Specifies two targets for Brutforce, enabled debug mode, -
    which allows you to save even if the links do not work. 
    And the save to the file out.txt is enabled
    
./sbrute google.com --db --set b --base sub.txt

  Bruteforces additional domains (dns)
  by google.com domain, shows even unsuccessful 
  results, uses bypass mode and database with 
  additional domains (sub.txt).
    
```

## Compile
-  ARCH & MANJARO  
        **sudo pacman -S curl**
       
- DEBIAN      
        **sudo apt install curl**

- git clone https://github.com/Lomasterrrr/subrute.git
- cd subrute
- make

#### Dependencies:
- gcc
- libcurl
