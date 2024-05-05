package fr.epita.assistants.presentation.rest.request;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Value;
import lombok.With;

public class ReverseRequest {
    String content;
    public ReverseRequest() {
    }
    public ReverseRequest(String content) {
        this.content = content;
    }


    public String getContent() {
        return content;
    }
}