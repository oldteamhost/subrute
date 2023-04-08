# Subrute
![alt text](https://i.imgur.com/TJzT3ED.png)

- Supports all kinds of proxies
- Works with http https
- Can save results to txt
- Runs very fast


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
  -s, --set <MODE>      Set style link (see github).
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

## Example
```
./lastn lomaster,lol --txt result.txt

    Searches for pages called lomaster and lol.
    And then saves (TXT).
    
./lastn lomaster --txt result.txt --db

    Searches for pages called lomaster.
    And then saves (even non-working ones) in txt.
```

## Compile
-  ARCH & MANJARO  
        **sudo pacman -S curl**
       
- DEBIAN      
        **sudo apt install curl**

- git clone https://github.com/Lomasterrrr/LastTrench.git
- cd LastTrench/5.7
- make

#### Dependencies:
- gcc
- libcurl
