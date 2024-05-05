package fr.epita.assistants.jws.data.model;

import io.quarkus.hibernate.orm.panache.PanacheEntity;
import io.quarkus.hibernate.orm.panache.PanacheEntityBase;
import lombok.*;

import javax.persistence.*;
import java.security.Timestamp;
import java.util.List;

@Entity @Table(name = "player")
@AllArgsConstructor @NoArgsConstructor @With
public class PlayerModel extends PanacheEntityBase {
    public @Id @GeneratedValue(strategy = GenerationType.IDENTITY) int id;
    public @Column Timestamp lastbomb;
    public @Column Timestamp lastmovement;
    public @Column int lives;
    public @Column String name;
    public @Column int posx;
    public @Column int posy;
   public @ManyToOne GameModel game;
}
