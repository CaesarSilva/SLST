# SLST

  SLST stands for Soldat Lobby Spying Tool  
It's not an actual spying tool, it only reads the information that is already available for everyone else.

  What it basically does is to check the information on api.soldat.pl , and analyze it, if there's a server that matches certain criteria, it creates a notification.  
So for example, if you like coops, rambomatch, SLST can notify you whenever there's a player online in the rambomatch server, or if there are at least 2 players playing a coop map on a climb server

Currently the user needs to edit the INI file manually for automatic notifications. A notification can be triggered when there's a minimum ammount of players and/or when the server's current map belongs to a map list. So for example you can set notifications when 5 or more people are playing one of your favorite maps in a specific CFT server.  
In order to set these events, edit ServerSearch.INI. In the [Info] section, the variable NumberOfEntries must contain the exact ammount of servers, or entries and the server's ip and port must be included in the [info] section in the format ipX= and portX=, where X is the server's index, the first server is the server 0. A section [X] must be created(X is the server's index) with the filters and the description and title of the notification. $p and $m will be replaced with the ammount of players and map's name. In the future, i might add a window to set these notifications, but that requires  some work, and editting the INI file shouldn't be too hard. If anyone is struggling to set the notifications, please, create an issue, and I will create some "presets", these files will be public.

The user can see the lobby, and if SLST can communicate with the server's fileserver, it also shows who's in the server. This feature doesn't use soldat lobby api, it takes the information straight from the server using sockets.

Due to the extremelly low ammount of users(I believe I'm SLST's only user), i've not been working hard on it. If someone actually uses it, feel free to create issues, if there are issues. Feel free to create issues for feature requests.

Due to the low ammount of active soldat players, I didn't add features like filters and search function in the lobby. Usually, the servers with players in it will always fit the screen. If someone likes a certain server that is usually empty, adding servers as favorite servers would be useful, this feature has not been implemented. If someone wants it, create an issue or pull request adding that.  
SLST works on windows and on linux. It works better on linux because it can be used as a launcher for soldat's linux version, that requires a launcher. The notifications on linux are also better, because it uses libnotify, and these notifications are customizable. Maybe on Windows 10 or 11 the notifications are better than windows 7, I haven't tested that. That's the whole reason I use libnotify for linux, wxWidgets' system notifications on linux are even worse than the notifications on windows.  
SLST possibly works on MacOS, but I won't test that, if someone has an issue with it, I can try to make changes that will make it more compatible with Mac, I believe the notifications might not work.

# Dependencies:
  SLST depends on:
  - wxWidgets  
  - rapidson (header only library that is already included)
  - INIReader(header only library that is already included) https://github.com/jtilly/inih
  - libnotify and it's dependencies(for linux only)
  

  
  
