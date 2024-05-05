package fr.epita.assistants.jws.data.repository;

import fr.epita.assistants.jws.data.model.PlayerModel;
import io.quarkus.hibernate.orm.panache.PanacheQuery;
import io.quarkus.hibernate.orm.panache.PanacheRepository;

import javax.enterprise.context.ApplicationScoped;

public class PlayerRepository implements PanacheRepository<PlayerModel> {
}
