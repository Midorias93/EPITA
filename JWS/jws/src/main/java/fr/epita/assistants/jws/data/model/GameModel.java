package fr.epita.assistants.jws.data.model;

import fr.epita.assistants.jws.domain.entity.PlayerEntity;
import fr.epita.assistants.jws.utils.GameState;
import io.quarkus.hibernate.orm.panache.PanacheEntity;
import io.quarkus.hibernate.orm.panache.PanacheEntityBase;
import lombok.*;

import javax.persistence.*;
import javax.validation.constraints.Null;
import java.sql.Timestamp;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.List;

@Entity @Table(name = "game")
@AllArgsConstructor @NoArgsConstructor @With
public class GameModel extends PanacheEntityBase {
    public @Id @GeneratedValue(strategy = GenerationType.IDENTITY) int id;
    public @Column Timestamp starttime;
    public @Column String state;
    public @ElementCollection @CollectionTable(name = "game_map", joinColumns = @JoinColumn(referencedColumnName = "id",name = "gamemodel_id")) List<String> map;
    public @OneToMany @JoinColumn(referencedColumnName = "id", name = "game_id") List<PlayerModel> players;

}
