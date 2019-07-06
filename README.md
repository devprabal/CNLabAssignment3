# CNLabAssignment3
## Socket Programming

I started doing my Computer Networks Assignment on socket programming in C. It’s tough believe me. I think it’s one of the toughest things I have taken up. It’s not completed yet and I don’t believe it will in anytime near. I felt good yesterday that I have finally started studying. I sat for an hour 5:30 pm to 6:30 pm continuous and read Socket programming introduction text from [Computer Networking: A Top-Down Approach](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=3&cad=rja&uact=8&ved=2ahUKEwiw_ee-n43eAhWKvI8KHbfgBrIQFjACegQIBxAB&url=https%3A%2F%2Fwww.pearson.com%2Fus%2Fhigher-education%2Fprogram%2FKurose-Computer-Networking-A-Top-Down-Approach-7th-Edition%2FPGM1101673.html&usg=AOvVaw0-V5o0VDnk7n3vD0h9TolM) written by Kurose and Ross. It was a good read after so long break from reading textbooks.

Next, I searched the Internet to implement the same \[**a multithreaded web server that implements a subset of HTTP/1.0 in the GET and HEAD response it sends to the client**\]  in C. So, there are several resources but for a beginner as me, it’s not only tough to comprehend some of the advanced topics but tougher it is to segregate the advanced stuffs apart. I came across [geeksforgeeks.org’](https://www.geeksforgeeks.org/socket-programming-cc/)s article that formed the basis of my assignment. However, I still have to incorporate many changes into it.

In order to understand that small piece of code (nearly 30 lines each for server and client side), I had to surf several Internet webpages and pdf guides. To cut the chase, some of the most important and relevant guides are -

1.  [Beej’s guide](https://beej.us/guide/bgnet/) -> Please do read it!
2.  [Kameswari Chebrolu, IIT Kanpur](http://home.iitk.ac.in/~chebrolu/ee673-f06/sockets.pdf) -> Really good!
3.  Your Linux machine’s man pages like - `man 7 socket` -> Please don't google stuffs that are already documented in man pages. These documents will save your time and keep you away from turning every google search link to purple.
4.  [Tutorialspoint.com](https://www.tutorialspoint.com/c_standard_library/c_function_strchr.htm) - for C functions and libraries description
5.  [Stackoverflow](https://stackoverflow.com/questions/39674720/implementing-head-and-get-requests-simple-web-server-in-c) - (do I need to say any description for this?)   

So I only could understand server.c before dinner. 

---

At many times during your coding, it will occur to you that everything is going down the hill. But believe me, don’t quit. Codes will run in small parts but when combined together, they will break. Then you should take a break, come back, you will find some way, you will get some new ideas in your head and finally you will make it. 2 times, I wished to quit. Luckily, I am sane and telling you that my code worked!

Multithreading will take another week, if I start doing, perhaps. But for now, **single threaded (serving only one client) web server implementing a subset of HTTP/1.0 for GET and HEAD requests** is fine.

### Let’s quickly review the concepts for it (I’m telling what I did).


1.  We need two codes – one for server, other for client
2.  We will work in Linux system (I used Ubuntu 18.04.1)
3.  We will not be scared of data types – POSIX has some weird [data types](http://man7.org/linux/man-pages/man0/sys_types.h.0p.html) (I don’t know the details or the differences, just know that your gcc compiler will tell which identifier format ‘`%d`’ or ‘`%lu`’ etc, to use)
4.  [Linux man pages](http://man7.org/linux/man-pages/man2/socket.2.html) should be referred to for your system specific parameters to functions (system calls). Example, `man 7 socket` [link to all manuals needed](https://github.com/devprabal/CNLabAssignment3/blob/master/manual_for_sockets)
5.  Strictly don’t know everything. You are advised to only know how to implement most things, what parameters to pass, what the function returns and type of those parameters.
6.  C `struct sockaddr_in` is your tool to play with, however, system call functions like `struct sockaddr`. So, the former should be type casted into the later. Don’t worry about the fields of sockaddr.
7.  File handle and socket handle are analogous.
8.  For server – create socket, set socket options, initialize sockadddr_in members, bind socket to a specific port number, listen, accept new connections and assign them a new socket, send/write/rcv/read from new socket.
9.  For client – create socket, initialize  sockadddr_in members including the conversion of IP address to binary form, connect, send/write/rcv/read from socket.
10.  Rest is file handling and handling of buffers.
11.  Sometimes or more often, `send()` will work better than `write()`
12.  `\r` `\n` and `EOF` characters are crucial and should be handled with care.
13.  You can implement better and efficient string reader/ parser/ splitter with regular expression, or other functions but I have used `strtok()`.
14.  If you see `segmentation fault (core dumped)` that means your char buffer arrays are messed up. Program is doing some invalid/unallowed memory access.
15. Two links - [geeksforgeeks](https://www.geeksforgeeks.org/socket-programming-cc/)(connection setup) and [stackexchange](https://codereview.stackexchange.com/questions/43914/client-server-implementation-in-c-sending-data-files/43918#43918)(Josay's answer on file handling).

![enter image description here](https://lh3.googleusercontent.com/KTE9X339Vovq-bAnSZyvExUnaIcNjtWjpWEzIzHk_vhCLsPqKy9iaC5sRi7nczrufqBFtaGKwr-M "socket programming algo")

Okay, more details and code stuffs will be in my code repository.
