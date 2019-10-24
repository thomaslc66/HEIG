package ch.heigvd.res.labs.roulette.net.client;

import ch.heigvd.res.labs.roulette.data.JsonObjectMapper;
import ch.heigvd.res.labs.roulette.data.Student;
import ch.heigvd.res.labs.roulette.data.StudentListWrapper;
import ch.heigvd.res.labs.roulette.data.StudentsList;
import ch.heigvd.res.labs.roulette.net.protocol.RouletteV2Protocol;
import com.fasterxml.jackson.core.type.TypeReference;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * This class implements the client side of the protocol specification (version 2).
 *
 * @author Olivier Liechti
 */
public class RouletteV2ClientImpl extends RouletteV1ClientImpl implements IRouletteV2Client {

  @Override
  public void clearDataStore() throws IOException {
      os.write(simulateInput(RouletteV2Protocol.CMD_CLEAR));
  }

  @Override
  public List<Student> listStudents() throws IOException {
      StudentListWrapper studentListWrapper;
      os.write(simulateInput(RouletteV2Protocol.CMD_LIST));
      is.read(buffer);
      String respond = new String(buffer);
      studentListWrapper = JsonObjectMapper.parseJson(respond, StudentListWrapper.class);
      return studentListWrapper.getStudents();
  }
  
}
