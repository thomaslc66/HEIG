# RES_TE2
## Application Apache php Dockerisée avec DockerFile

Toutes les commandes ci-dessous ont été réalisée arpès l'installation et le lancement de Docker ToolBox pour windows

[Installation de Docker ToolBox](https://download.docker.com/win/stable/DockerToolbox.exe)

Utiliser le lien Docker QuickStart pour lancer les commandes Docker
![enter image description here](https://i.imgur.com/rg0JQjh.png)

Le lancement de docker terminé, noté l'adresse Ip donnée.
Dans notre cas 192.168.99.100
![Docker is running](https://i.imgur.com/cvzLl7C.png)


## Création du fichier DockerFile
```` 
$ mkdir Docker-images 
$ cd Docker-images
$ touch Dockerfile
$ mkdir src
````

#### Contenu du dossier après exécution des commandes
![Contenu du dossier après exécution des commandes](https://i.imgur.com/BrFlQbF.png)

Ouvrir le fichier Dockerfile avec un éditeur de code (SublimeText / NotePad++ / Atom). Ajouter le code suivant
````
FROM php:5.6-apache         //Cette ligne indique l'image voulue
COPY src/ /var/www/html		//Cette ligne copie src dans le container à l'emplacement var/www/html
````

Afin de vérifier que notre application fonctionne correctement nous allons ajouter du code dans le dossier src, car ce dernier sera copier dans le dossier /var/www/html qui est le dossier principal d'apache et qui contient notre site web.

Pour cela nous avons copié un template de site web statique trouvé sur Github.com
 [Lien vers le repository git du template](https://github.com/BuckyMaler/global)

````
$ docker build -t nom_de_mon_appli .         //Attention à ne pas oublier le point
$ docker run -d -p 9090:80 nom_de_mon_appli  
````

La commande `docker run` possède les attributs suivant:

 - -d : lance l'application en background
 - -p : effectue le port mapping (ici redirection du port 9090 vers le port 80 du container)
 - Le nom de l'application buildé lors de la commande précédente

Vous pouvez vérifier que la commande c'est exécutée correctement grace à la commande `$ docker ps` qui vous affichera la liste des containers.

![Docker ps commande](https://i.imgur.com/3aJfEHG.png)

Le container tourne correctement si sous image vous avez le nom de votre application choisie lors de la commande `docker build`

Pour tester que notre application fonctionne, il faut nous rendre à l'adresse donnée par Docker Toolbox sur le port 9090 (192.168.99.100:9090)

Le lien et le container fonctionnent car il nous délivre le template du site web que nous avons choisi.

![template du site web](https://i.imgur.com/GjFuynC.png)




<!--stackedit_data:
eyJoaXN0b3J5IjpbMTA4MTU5NTcwOCwyMTE2MDExNDM4LDk3OT
k2MzE5Nl19
-->