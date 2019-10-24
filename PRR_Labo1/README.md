# PRR_Labo_1

## Instructions
Download the server(PTPServer-zip.zip) or the client(PTPClient-zip.zip) folder and unzip it. 

Use an zip editor to edit the config.properties in the .jar

### Configuration
config.properties : 
* multicastAddress : the multicast ipv4 address
* multicastPort : the common multicast port used between client and server
* multicastServerPort : the multicast server port
* unicastAddress : the unicast ipv4 address
* unicastPort : the common unicast port used between client and server
* messageSyncType : byte used to define Sync Message
* messageFollowUpType : byte used to define FollowUp Message
* messageDelayRequestType : byte used to define Delay Request Message
* messageDelayResponseType : byte used to define Delay Respond Message
* sleepTime : Sleep time before the server send a new Sync message
* debug : config to true if you need to display more information to debug