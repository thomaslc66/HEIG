/**
 * @project     : Argmagetron
 * @file        : TestUtils.java
 * @author(s)   : Michaël Brouchoud
 * @date        : 30.05.2017
 *
 * @brief        : Utils Object shared by Test class
 *
 */

package server;

class TestUtils {
    static final short port = 5555;
    static  final Server server = new Server(port);
}
