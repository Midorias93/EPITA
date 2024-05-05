package fr.epita.assistants.practicelombok;
import lombok.*;

@AllArgsConstructor
@NoArgsConstructor
@ToString

public class Tiger {
    @Getter @Setter public String name;
    @Getter @Setter public String nickname;
}