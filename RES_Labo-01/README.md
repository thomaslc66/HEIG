# Teaching-HEIGVD-RES-2017-Labo-01


### About the 2017 version of this lab

Before reading this documentation and diving into the code, you should watch [this webcast](https://www.youtube.com/watch?v=qgncWAUqcbY&index=1&list=PLfKkysTy70QYD00EqEabdwyDNTPwLcsFV), which shows a **demo** of the application that you will implement. Later on, you might also watch [this webcast](https://www.youtube.com/watch?v=v_ZpVgf0lGc&index=2&list=PLfKkysTy70QYD00EqEabdwyDNTPwLcsFV), which gives you some hints about the **code structure**.

If you watch carefully, you will see that in 2015, we were using a web service called [iheartquotes](http://www.iheartquotes.com/) to fetch dynamic text data. This service is now down, so this year we had to look for [a replacement](http://www.icndb.com/api/). We also had to adapt the code of the starter project a bit. You will see why and how when in the commented source code.

For this reason, there will be some differences in the console output, but nothing extraordinary.

![image](./diagrams/chuck.png)

### Introduction

The objective of this lab is to get familiar with the Java IO APIs and to interact with the file system. You will implement an application that performs the following tasks:

1. The user invokes the application on the **command line** and provides a numeric argument (*n*).
2. The application **uses a Web Service client** (which is provided to you) to fetch *n* **quotes** from the [Internet Chuck Norris Database](http://www.icndb.com/api/) online service.
3. The application stores the content of each quote in a **text file** (utf-8), on the local filesystem. It uses the *tags* associated to each quote to create a hierarchical structure of directories.
4. The application then **traverses the local file system** (depth-first) and applies a processing to each visited quote file.
5. The processing consists of 1) converting all characters to their **uppercase** value and 2) adding a **line number** (followed by a tab character) at the beginning of each line. This is achieved by combining sub-classes of the `FilterWriter` class.

If your application is fully implemented you should have the following result on your machine:

#### A. When building the application


```
HEIGVD $ mvn clean install
[INFO] Scanning for projects...
[INFO] ------------------------------------------------------------------------
[INFO] Reactor Build Order:
[INFO] 
[INFO] Lab01App-code
[INFO] Lab01App-tests
[INFO] Lab01App-build
[INFO]                                                                         
[INFO] ------------------------------------------------------------------------
[INFO] Building Lab01App-code 1.0-SNAPSHOT
[INFO] ------------------------------------------------------------------------

... (skipping some of the log output)

Results :

Tests run: 27, Failures: 0, Errors: 0, Skipped: 0

... (skipping some of the log output)

[INFO] ------------------------------------------------------------------------
[INFO] Reactor Summary:
[INFO] 
[INFO] Lab01App-code ..................................... SUCCESS [2.477s]
[INFO] Lab01App-tests .................................... SUCCESS [8.811s]
[INFO] Lab01App-build .................................... SUCCESS [0.004s]
[INFO] ------------------------------------------------------------------------
[INFO] BUILD SUCCESS
[INFO] ------------------------------------------------------------------------

```

#### B. When running the application

```
$ java -jar Lab01App-code/target/Lab01App-code-1.0-SNAPSHOT-launcher.jar 10
INFO: Received a new joke with 3 tags.
INFO: > popular
INFO: > movie
INFO: > hilarious
INFO: Received a new joke with 1 tags.
INFO: > hilarious
INFO: Received a new joke with 5 tags.
INFO: > hilarious
INFO: > funny
INFO: > joke
INFO: > geek
INFO: > internet
INFO: Received a new joke with 6 tags.
INFO: > geek
INFO: > movie
INFO: > internet
INFO: > popular
INFO: > hilarious
INFO: > joke
INFO: Received a new joke with 3 tags.
INFO: > funny
INFO: > joke
INFO: > hilarious
INFO: Received a new joke with 5 tags.
INFO: > hilarious
INFO: > joke
INFO: > movie
INFO: > geek
INFO: > funny
INFO: Received a new joke with 6 tags.
INFO: > joke
INFO: > movie
INFO: > internet
INFO: > popular
INFO: > hilarious
INFO: > funny
INFO: Received a new joke with 2 tags.
INFO: > popular
INFO: > geek
INFO: Received a new joke with 5 tags.
INFO: > hilarious
INFO: > popular
INFO: > internet
INFO: > movie
INFO: > geek
INFO: Received a new joke with 7 tags.
INFO: > geek
INFO: > hilarious
INFO: > movie
INFO: > joke
INFO: > internet
INFO: > funny
INFO: > popular
INFO: ./workspace/quotes
./workspace/quotes/funny
./workspace/quotes/funny/joke
./workspace/quotes/funny/joke/hilarious
./workspace/quotes/funny/joke/hilarious/quote-5.utf8
./workspace/quotes/geek
./workspace/quotes/geek/hilarious
./workspace/quotes/geek/hilarious/movie
./workspace/quotes/geek/hilarious/movie/joke
./workspace/quotes/geek/hilarious/movie/joke/internet
./workspace/quotes/geek/hilarious/movie/joke/internet/funny
./workspace/quotes/geek/hilarious/movie/joke/internet/funny/popular
./workspace/quotes/geek/hilarious/movie/joke/internet/funny/popular/quote-10.utf8
./workspace/quotes/geek/movie
./workspace/quotes/geek/movie/internet
./workspace/quotes/geek/movie/internet/popular
./workspace/quotes/geek/movie/internet/popular/hilarious
./workspace/quotes/geek/movie/internet/popular/hilarious/joke
./workspace/quotes/geek/movie/internet/popular/hilarious/joke/quote-4.utf8
./workspace/quotes/hilarious
./workspace/quotes/hilarious/quote-2.utf8
./workspace/quotes/hilarious/funny
./workspace/quotes/hilarious/funny/joke
./workspace/quotes/hilarious/funny/joke/geek
./workspace/quotes/hilarious/funny/joke/geek/internet
./workspace/quotes/hilarious/funny/joke/geek/internet/quote-3.utf8
./workspace/quotes/hilarious/joke
./workspace/quotes/hilarious/joke/movie
./workspace/quotes/hilarious/joke/movie/geek
./workspace/quotes/hilarious/joke/movie/geek/funny
./workspace/quotes/hilarious/joke/movie/geek/funny/quote-6.utf8
./workspace/quotes/hilarious/popular
./workspace/quotes/hilarious/popular/internet
./workspace/quotes/hilarious/popular/internet/movie
./workspace/quotes/hilarious/popular/internet/movie/geek
./workspace/quotes/hilarious/popular/internet/movie/geek/quote-9.utf8
./workspace/quotes/joke
./workspace/quotes/joke/movie
./workspace/quotes/joke/movie/internet
./workspace/quotes/joke/movie/internet/popular
./workspace/quotes/joke/movie/internet/popular/hilarious
./workspace/quotes/joke/movie/internet/popular/hilarious/funny
./workspace/quotes/joke/movie/internet/popular/hilarious/funny/quote-7.utf8
./workspace/quotes/popular
./workspace/quotes/popular/geek
./workspace/quotes/popular/geek/quote-8.utf8
./workspace/quotes/popular/movie
./workspace/quotes/popular/movie/hilarious
./workspace/quotes/popular/movie/hilarious/quote-1.utf8
```

#### C. After running the application

```
$ find workspace/quotes/
workspace/quotes/
workspace/quotes//funny
workspace/quotes//funny/joke
workspace/quotes//funny/joke/hilarious
workspace/quotes//funny/joke/hilarious/quote-5.utf8
workspace/quotes//funny/joke/hilarious/quote-5.utf8.out
workspace/quotes//geek
workspace/quotes//geek/hilarious
workspace/quotes//geek/hilarious/movie
workspace/quotes//geek/hilarious/movie/joke
workspace/quotes//geek/hilarious/movie/joke/internet
workspace/quotes//geek/hilarious/movie/joke/internet/funny
workspace/quotes//geek/hilarious/movie/joke/internet/funny/popular
workspace/quotes//geek/hilarious/movie/joke/internet/funny/popular/quote-10.utf8
workspace/quotes//geek/hilarious/movie/joke/internet/funny/popular/quote-10.utf8.out
workspace/quotes//geek/movie
workspace/quotes//geek/movie/internet
workspace/quotes//geek/movie/internet/popular
workspace/quotes//geek/movie/internet/popular/hilarious
workspace/quotes//geek/movie/internet/popular/hilarious/joke
workspace/quotes//geek/movie/internet/popular/hilarious/joke/quote-4.utf8
workspace/quotes//geek/movie/internet/popular/hilarious/joke/quote-4.utf8.out
workspace/quotes//hilarious
workspace/quotes//hilarious/funny
workspace/quotes//hilarious/funny/joke
workspace/quotes//hilarious/funny/joke/geek
workspace/quotes//hilarious/funny/joke/geek/internet
workspace/quotes//hilarious/funny/joke/geek/internet/quote-3.utf8
workspace/quotes//hilarious/funny/joke/geek/internet/quote-3.utf8.out
workspace/quotes//hilarious/joke
workspace/quotes//hilarious/joke/movie
workspace/quotes//hilarious/joke/movie/geek
workspace/quotes//hilarious/joke/movie/geek/funny
workspace/quotes//hilarious/joke/movie/geek/funny/quote-6.utf8
workspace/quotes//hilarious/joke/movie/geek/funny/quote-6.utf8.out
workspace/quotes//hilarious/popular
workspace/quotes//hilarious/popular/internet
workspace/quotes//hilarious/popular/internet/movie
workspace/quotes//hilarious/popular/internet/movie/geek
workspace/quotes//hilarious/popular/internet/movie/geek/quote-9.utf8
workspace/quotes//hilarious/popular/internet/movie/geek/quote-9.utf8.out
workspace/quotes//hilarious/quote-2.utf8
workspace/quotes//hilarious/quote-2.utf8.out
workspace/quotes//joke
workspace/quotes//joke/movie
workspace/quotes//joke/movie/internet
workspace/quotes//joke/movie/internet/popular
workspace/quotes//joke/movie/internet/popular/hilarious
workspace/quotes//joke/movie/internet/popular/hilarious/funny
workspace/quotes//joke/movie/internet/popular/hilarious/funny/quote-7.utf8
workspace/quotes//joke/movie/internet/popular/hilarious/funny/quote-7.utf8.out
workspace/quotes//popular
workspace/quotes//popular/geek
workspace/quotes//popular/geek/quote-8.utf8
workspace/quotes//popular/geek/quote-8.utf8.out
workspace/quotes//popular/movie
workspace/quotes//popular/movie/hilarious
workspace/quotes//popular/movie/hilarious/quote-1.utf8
workspace/quotes//popular/movie/hilarious/quote-1.utf8.out
```

You can then compare `quote-8.utf8` with `quote-8.utf8` to see the text received as input (from the web service) and the text produced as output (by your program).


### Tasks

Here is the proposed list of tasks to achieve the objectives:

1. Start by forking and cloning this repo (**mandatory!!**).
2. From the main project, do a `mvn clean install` and notice that the tests fail.
3. Spend some time to explore the package structure (and watch [this](https://www.youtube.com/watch?v=v_ZpVgf0lGc&list=PLfKkysTy70Qb_mfkkqa5OUMqsOPNEYZIa&index=5) Youtube video).
4. Examine the automated tests in the test project and do a step-by-step implementation, until all tests are green. Here is a proposed order for fixing the broken tests:
   - `ApplicationTest.java`
   - `UtilsTest.java`
   - `UpperCaseFilterWriterTest.java`
   - `DFSFileExplorerTest.java`
   - `FileTransformerTest.java`
   - `FileNumberingFilterWriterTest.java`
   - `CompleteFileTransformerTest.java`
5. Each time that you fix a failing test, `commit` your work (and use a **meaningful message**)
6. When all the tests are green, invoke the application (`java -jar`) from the top-level directory (the directory that contains the `.git` hidden folder). Inspect the content of the `workspace/quotes` directory and check that the output files are correct.
7. When you are done, make sure that you have committed all your work and push your commits.
8. To make a final validation, move to a fresh directory. Clone your fork. Do a `mvn clean install` and make sure that the tests are still green and that the app still produces the correct output.
9. Submit a pull request.
