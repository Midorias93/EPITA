package fr.epita.assistants.practicelombok;

import lombok.*;

@ToString
@EqualsAndHashCode
@AllArgsConstructor
@NoArgsConstructor

public class Horse {
    @Getter @Setter private String name;
    @ToString.Exclude @Getter @Setter private String nickname;
    @EqualsAndHashCode.Exclude @Getter private int speed;
}