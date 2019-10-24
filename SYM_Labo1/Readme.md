  
Léchaire Thomas |  Kevin Pradervand | Micheal Brouchoud
23.09.2018  | SYM 2018  
  

# Laboratoire 1 - Connexion Email 

  

## Questions: 



### Question 1: Comment organiser les textes pour obtenir une application multi-langues (français, allemand, italien, langue par défaut : anglais) ? Que se passe-t-il si une traduction est manquante dans la langue par défaut ou dans une langue supplémentaire ?  

Réponse: L'editeur de texte présent dans Android Studio permet d'ajouter toutes les langues que l'on souhaite directement dans l'IDE. La traduction est alors possible, non pas de manirère automatique, mais en enregistrant soit même les phrases. Si la string n'est pas introduite dans la langue par défault cela produit un warning car la string n'est pas remplie, par contre si cela se produit pour une des traductions, l'application utilise la traduction par default. Si l'anglais est choisi, mais que la phrase n'est pas définie en anglais cela pose un warning, si la traduction en francais n'est pas remplie, l'application utilise la traduction en anglais.
  

### Question 2: . Dans l’exemple fourni, sur le dialogue pop-up, nous affichons l’icône android.R.drawable.ic_dialog_alert, disponible dans le SDK Android mais qui n’est pas très bien adapté visuellement à notre utilisation. Nous souhaitons la remplacer avec notre propre icône, veuillez indiquer comment procéder. Dans quel(s) dossier(s) devons-nous ajouter cette image ? Décrivez brièvement la logique derrière la gestion des ressources de type « image » sur Android.

Réponse: Sous Android, les images sont ce que android appelle des Drawable. La problèmatique android vient des différences entre les tailles des écrans. Chaque écran possède sa propre résolution et ses propres dimensions. Il faut utiliser une structure de dossier spéciale pour classer chaque image selon sa résolution. La principale problèmatique pour le développeur est de produire la même image dans toutes les résolutions. 
Les différents dossiers portent des noms différents selon leurs tailles: ldpi | mdpi | hdpi | xhdpi | xxhdpi | xxxhdpi (l = low, m = medium, h = high, etc...)

### Question 3: . Lorsque le login est réussi, vous êtes censé chaîner une autre Activity en utilisant un Intent. Si je presse le bouton "Back" de l'interface Android, que puis-je constater ? Comment faire pour que l'application se comporte de manière plus logique ? Veuillez discuter de la logique derrière les activités Android.

Réponse: L'application quitte, de la même manière lorsqu'on fait appelle à la méthode finish(). Pour qu'elle possède un comportement plus normal il faut implémenter la méthode onBackPressed() et définir dans cette méthode le comportement à adopter.

### Question 4: On pourrait imaginer une situation où cette seconde Activity fournit un résultat (par exemple l’IMEI ou une autre chaîne de caractères) que nous voudrions récupérer dans l'Activity de départ. Comment procéder ?

Réponse: Il faut utiliser une des méthodes permettant de passer un "Extra" entre deux Activité. Après avoir créer l'Intent il faut utiliser une méthode comme putExtra() et utiliser la méthode getExtra() dans le nouvel intent. Dans le template, l'email a été passé au l'intent suivant (Interface profil utilisateur).

### Question 5: Vous noterez que la méthode getDeviceId() du TelephonyManager, permettant d’obtenir l’IMEI du téléphone, est dépréciée depuis la version 26 de l’API. Veuillez discuter de ce que cela implique lors du développement et de présenter une façon d’en tenir compte avec un exemple de code.

Réponse: Cela implique d'ajouter des vérification d'API et de définir un code différent selon la version de l'api du téléphone. 
Exemple:    //Check differents api version and use the correct method
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                imeiStr = telephonyManager.getImei();
            }else{
                imeiStr = telephonyManager.getDeviceId();
            }

### Question 6: Dans l’activité de login, en plaçant le téléphone (ou l’émulateur) en mode paysage (landscape), nous constatons que les 2 champs de saisie ainsi que le bouton s’étendent sur toute la largeur de l’écran. Veuillez réaliser un layout spécifique au mode paysage qui permet un affichage mieux adapté et indiquer comment faire pour qu’il soit utilisé automatiquement à l’exécution.

Réponse: Réalise dans le projet android. Pour l'utiliser automatiquement, il faut soit ajouter une ligne de code ou on peut aller dans le manifest.xml pour ajouter le code suivant dans l'activité en question, forcant l'utilisation du layout en paysage: android:screenOrientation="landscape"

### Question 7: Le layout de l’interface utilisateur de l’activité de login qui vous a été fourni a été réalisé avec un LinearLayout à la racine. Nous vous demandons de réaliser un layout équivalent utilisant cette fois-ci un RelativeLayout

Réponse: Fait dans le projet.

### Question 8: Implémenter dans votre code les méthodes onCreate(), onStart(), onResume(), onPause(), onStop(), etc... qui marquent le cycle de vie d'une application Android, et tracez leur exécution dans le logcat. Décrivez brièvement à quelles occasions ces méthodes sont invoquées. Si vous aviez (par exemple) une connexion Bluetooth (ou des connexions bases de données, ou des capteurs activés) ouverte dans votre Activity, que faudrait-il peut-être faire, à votre avis (nous ne vous demandons pas de code ici) ?

Réponse: Pour la suite logique. onCreate() appelle onStart(), onStart() appelle onResume(). Si l'application passe au second plan onPause() est appelé puis onStop(). En imaginant que l'activité revienne au premier plan alors onRestart(), puis onStart() et enfin onResume() est appelé.
Enfin losrqu'on tue l'application, les méthodes onPause(), onStop() et onDestroy() sont appelés. La même séquence est effectuée lors de changement d'activités.
En imaginant l'utilisation d'une base de donnée on pourrait imaginer ajouter les appels à la DB dans la méthode onCreate() afin de les utiliser après dans la méthode onStart() ou pour l'affichage, pareil lorsque l'activité passe au second plan dans la méthode onPause() on sauvegarde ou restaure certainew valeurs importante pour l'application.

### Question 9: Facultatif – Question Bonus - S’il vous reste du temps, nous vous conseillons de le consacrer à mettre en place la résolution des permissions au runtime.

Réponse: Permissions au runtime mise en place
<!--stackedit_data:
eyJoaXN0b3J5IjpbMjAwMDkwMDQ2Ml19
-->
