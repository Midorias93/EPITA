package fr.epita.assistants.jws.presentation.rest.response;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@AllArgsConstructor @NoArgsConstructor @Getter @Setter
public class PlayerResponse {
    int id;
    String name;
    int lives;
    int posX;
    int posY;
}
