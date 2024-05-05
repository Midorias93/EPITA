package fr.epita.assistants.grades;

import fr.epita.assistants.grades.model.*;

import java.util.*;
import java.util.function.*;
import java.util.stream.*;

public class GradeHandler {
    private final List<Activity> activities;
    private final List<Student> students;

    public GradeHandler() {
        this.activities = new ArrayList<>();
        this.students = new ArrayList<>();
    }

    /**
     * @param activity The {@link Activity} to be added
     * @return {@code true} (as specified by {@link List#add})
     */
    public boolean addActivity(Activity activity) {
        // FIXME
        if (activity != null) {
            this.activities.add(activity);
            return true;
        }
        return false;
    }

    /**
     * @param student The {@link Student} to be added
     * @return {@code true} (as specified by {@link List#add})
     */
    public boolean addStudent(Student student) {
        // FIXME
        if (student != null) {
            this.students.add(student);
            return true;
        }
        return false;
    }

    /**
     * @param name The name of the desired {@link Student}
     * @return The desired student
     * @throws EntryNotFoundException No known {@link Student} with the given name
     */
    public Student getStudent(String name) throws EntryNotFoundException {
        // FIXME
        for (Student x:this.students) {
          if (x.name().compareTo(name) == 0) {
              return x;
          }
        }
        throw new EntryNotFoundException(Student.class, name);
    }

    /**
     * @param grade The {@link Grade} to be added to the {@link Student}
     * @param name  The name of the desired {@link Student}
     * @return {@code true} (as specified by {@link List#add})
     * @throws EntryNotFoundException No known {@link Student} with the given name
     */
    public boolean addGradeToStudent(Grade grade, String name) throws EntryNotFoundException {
        // FIXME
        if (grade == null && name == null)
            return false;
        this.getStudent(name).grades().add(grade);
        return true;
    }

    /**
     * @param name The name of the desired {@link Student} to remove
     * @return The removed {@link Student}
     * @throws EntryNotFoundException No known {@link Student} with the given name
     */
    public Student removeStudent(String name) throws EntryNotFoundException {
        // FIXME
        Student removedStudent = this.getStudent(name);
        this.students.remove(removedStudent);
        return removedStudent;
    }

    /**
     * @param name     The name of the desired {@link Student}
     * @param function A {@link Function} returning an updated {@link Student} from the given one
     * @throws EntryNotFoundException No known {@link Student} with the given name
     */
    public void updateStudent(String name, Function<Student, Student> function) throws EntryNotFoundException {
        // FIXME
        function.apply(getStudent(name));
    }

    /**
     * @param name    The name of the {@link Student} from which to get grades
     * @param subject The {@link Subject} from which we want the student's average
     * @return The student's average grade in the specified subject (0 if no grades are available)
     * @throws EntryNotFoundException No known {@link Student} with the given name
     */
    public double getStudentAverageInSubject(String name, Subject subject) throws EntryNotFoundException {
        // FIXME
        double somme = 0;
        double ponderence = 0;
       for (Grade note:this.getStudent(name).grades()) {
           if(note.activity().subject().compareTo(subject) == 0)
           {
               somme += note.grade() * note.activity().weight();
               ponderence += note.activity().weight();
           }
       }
       if (somme == 0 || ponderence == 0)
           return 0.0;
       return somme / ponderence;
    }
}
