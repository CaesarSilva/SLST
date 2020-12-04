# SLST

  SLST stands for Soldat Lobby Spying Tool
It's not an actual spying tool, it only reads the information that is already available for everyone else.

  What it basically does is to check the information on api.soldat.pl , and analyze it, if there's a server that matches certain criteria, it creates a notification.  
So for example, if you like coops, rambomatch, SLST can notify you whenever there's a player online in the rambomatch server, or if there are at least 2 players playing a coop map on a climb server.  

Currently the user needs to edit the INI file manually for automatic notifications.  
Currently the user can see the lobby manually, but there's no way to see who's in the server. This feature will be added later.


# Dependencies:
  SLST depends on:
  - wxWidgets  
  - rapidson (header only library that is already included)
  - INIReader(header only library that is already included)
  - libnotify and it's dependencies(for linux only)
  
  
  
