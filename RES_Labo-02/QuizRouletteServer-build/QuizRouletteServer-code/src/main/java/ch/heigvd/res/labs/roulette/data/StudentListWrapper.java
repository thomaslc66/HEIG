package ch.heigvd.res.labs.roulette.data;

import java.util.List;

public class StudentListWrapper {
    private List<Student> students;

    public StudentListWrapper() {}

    public StudentListWrapper(List<Student> students) {
        this.students = students;
    }

    public List<Student> getStudents() {
        return students;
    }

    public void setStudents(List<Student> students) {
        this.students = students;
    }
}
