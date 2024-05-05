package fr.epita.assistants.data.model;

import io.quarkus.hibernate.orm.panache.PanacheEntityBase;
import lombok.AllArgsConstructor;
import lombok.NoArgsConstructor;
import lombok.ToString;
import lombok.With;

import javax.persistence.*;
import java.util.List;

@Entity @Table(name = "course_model")
@AllArgsConstructor @NoArgsConstructor @With @ToString
public class CourseModel extends PanacheEntityBase {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY) Long id;
    public @Column(name = "name") String name;
    @OneToMany @JoinColumn(referencedColumnName = "id", name = "course_id") List<StudentModel> studens;
    public @ElementCollection @CollectionTable(name = "course_model_tags", joinColumns = @JoinColumn(referencedColumnName = "id", name = "course_id")) List<String> tag;
}