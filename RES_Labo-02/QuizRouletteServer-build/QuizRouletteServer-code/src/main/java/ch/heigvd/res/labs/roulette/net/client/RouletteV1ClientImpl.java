package ch.heigvd.res.labs.roulette.net.client;

import ch.heigvd.res.labs.roulette.data.EmptyStoreException;
import ch.heigvd.res.labs.roulette.data.JsonObjectMapper;
import ch.heigvd.res.labs.roulette.data.Student;
import ch.heigvd.res.labs.roulette.net.protocol.InfoCommandResponse;
import ch.heigvd.res.labs.roulette.net.protocol.RandomCommandResponse;
import ch.heigvd.res.labs.roulette.net.protocol.RouletteV1Protocol;
import ch.heigvd.res.labs.roulette.net.protocol.RouletteV2Protocol;

import java.io.*;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * This class implements the client side of the protocol specification (version 1).
 * 
 * @author Olivier Liechti
 */
public class RouletteV1ClientImpl implements IRouletteV1Client {

  private static final Logger LOG = Logger.getLogger(RouletteV1ClientImpl.class.getName());
  protected static final int BUFFER_SIZE = 255;
  protected static byte[] buffer = new byte[BUFFER_SIZE];
  protected Socket clientSocket;
  protected InputStream is;
  protected OutputStream os;

  protected static byte[] simulateInput(String s) {
    return (s + "\n").getBytes();
  }

  @Override
  public void connect(String server, int port) throws IOException {
      clientSocket = new Socket();
      clientSocket.connect(new InetSocketAddress(server, port));

      is = clientSocket.getInputStream();
      os = clientSocket.getOutputStream();

      is.read(buffer); //Ignore welcome server message
  }

  @Override
  public void disconnect() throws IOException {
      is.close();
      os.close();
      clientSocket.close();
  }

  @Override
  public boolean isConnected() {
    return (clientSocket != null && clientSocket.isConnected());
  }

  @Override
  public void loadStudent(final String fullname) throws IOException {
    ArrayList<Student> students = new ArrayList<Student>() {{
      add(new Student(fullname));
    }};
    this.loadStudents(students);
  }

  @Override
  public void loadStudents(List<Student> students) throws IOException {
    os.write(simulateInput(RouletteV1Protocol.CMD_LOAD));
    is.read(buffer); //ignore message "Send your data [end with ENDOFDATA]"
    for(Student student : students) {
      os.write(simulateInput(student.getFullname()));
    }
    os.write(simulateInput(RouletteV1Protocol.CMD_LOAD_ENDOFDATA_MARKER));
    is.read(buffer); //Ignore message "DATA LOADED"
  }

  @Override
  public Student pickRandomStudent() throws EmptyStoreException, IOException {
    os.write(simulateInput(RouletteV1Protocol.CMD_RANDOM));
    Student student = new Student();

    is.read(buffer);

    RandomCommandResponse rd = JsonObjectMapper.parseJson(new String(buffer), RandomCommandResponse.class);

    if(rd.getError() != null && rd.getError().isEmpty()) {
      student.setFullname(rd.getFullname());
    }
    else {
      throw new EmptyStoreException();
    }

    return student;
  }

  @Override
  public int getNumberOfStudents() throws IOException {
    os.write(simulateInput(RouletteV1Protocol.CMD_INFO));

    is.read(buffer);

    InfoCommandResponse icr = JsonObjectMapper.parseJson(new String(buffer), InfoCommandResponse.class);

    return icr.getNumberOfStudents();
  }

  @Override
  public String getProtocolVersion() throws IOException {
    os.write(simulateInput(RouletteV1Protocol.CMD_INFO));

    is.read(buffer);

    InfoCommandResponse icr = JsonObjectMapper.parseJson(new String(buffer), InfoCommandResponse.class);

    return icr.getProtocolVersion();
  }
}
