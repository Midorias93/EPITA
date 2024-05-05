package fr.epita.assistants.jws.domain.service;

import fr.epita.assistants.jws.converter.Converter;
import fr.epita.assistants.jws.data.repository.GameRepository;
import fr.epita.assistants.jws.data.repository.PlayerRepository;
import fr.epita.assistants.jws.domain.entity.PlayerEntity;
import io.quarkus.hibernate.orm.panache.PanacheRepository;

import javax.enterprise.context.ApplicationScoped;
import javax.enterprise.context.RequestScoped;
import javax.inject.Inject;

public class PlayerService {
    static GameRepository gameRepository = new GameRepository();
    static PlayerRepository playerRepository = new PlayerRepository();
}
