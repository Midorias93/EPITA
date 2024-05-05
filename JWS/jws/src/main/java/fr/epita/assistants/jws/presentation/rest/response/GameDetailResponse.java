package fr.epita.assistants.jws.presentation.rest.response;

import fr.epita.assistants.jws.utils.GameState;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.util.List;
@NoArgsConstructor @AllArgsConstructor @Getter @Setter
public class GameDetailResponse {
    public String startTime;
    public GameState state; // enum GameState to String
    public List<PlayerResponse> players;
    public List<String> map;
    public int id;
}