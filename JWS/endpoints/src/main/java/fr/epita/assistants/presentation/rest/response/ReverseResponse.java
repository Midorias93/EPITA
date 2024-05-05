package fr.epita.assistants.presentation.rest.response;

import fr.epita.assistants.presentation.rest.request.ReverseRequest;
import lombok.Getter;
import lombok.Setter;

public class ReverseResponse {
    @Getter
    @Setter
    String original;
    @Getter @Setter String reversed;

    public ReverseResponse() {
    }

    public ReverseResponse(ReverseRequest request) {
        this.original = request.getContent();
        StringBuilder reversed = new StringBuilder(this.original);
        this.reversed = reversed.reverse().toString();
    }
}
