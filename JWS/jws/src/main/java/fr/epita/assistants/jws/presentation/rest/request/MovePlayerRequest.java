package fr.epita.assistants.jws.presentation.rest.request;

import lombok.AllArgsConstructor;
import lombok.NoArgsConstructor;

@AllArgsConstructor @NoArgsConstructor
public class MovePlayerRequest {
    public int posX;
    public int posY;
}