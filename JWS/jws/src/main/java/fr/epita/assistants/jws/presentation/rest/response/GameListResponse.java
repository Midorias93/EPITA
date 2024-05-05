package fr.epita.assistants.jws.presentation.rest.response;

import fr.epita.assistants.jws.domain.entity.GameEntity;
import fr.epita.assistants.jws.utils.GameState;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
public class GameListResponse {
    int id;
    int players;
    GameState state; // enum GameState to String
}
