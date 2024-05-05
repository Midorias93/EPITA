package fr.epita.assistants.data.model;

import lombok.AllArgsConstructor;
import lombok.NoArgsConstructor;
import lombok.ToString;
import lombok.With;

import javax.persistence.*;
import java.util.List;

@Entity @Table(name = "student_model")
@AllArgsConstructor @NoArgsConstructor @With @ToString
public class StudentModel {
    @Id long id;
    public @Column(name = "name") String name;
    @ManyToOne CourseModel course;
}
