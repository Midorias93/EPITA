package fr.epita.assistants.jws.domain.service;

import com.google.inject.Inject;
import fr.epita.assistants.jws.converter.Converter;
import fr.epita.assistants.jws.data.model.GameModel;
import fr.epita.assistants.jws.data.model.PlayerModel;
import fr.epita.assistants.jws.data.repository.GameRepository;
import fr.epita.assistants.jws.data.repository.PlayerRepository;
import fr.epita.assistants.jws.domain.entity.GameEntity;
import fr.epita.assistants.jws.domain.entity.PlayerEntity;
import fr.epita.assistants.jws.presentation.rest.response.GameDetailResponse;
import fr.epita.assistants.jws.presentation.rest.response.GameListResponse;
import fr.epita.assistants.jws.presentation.rest.response.PlayerResponse;
import fr.epita.assistants.jws.utils.GameState;
import org.hibernate.Hibernate;

import javax.enterprise.context.ApplicationScoped;
import javax.enterprise.context.RequestScoped;
import javax.transaction.Transactional;
import javax.ws.rs.BadRequestException;
import java.io.IOException;
import java.nio.file.Path;
import java.sql.Timestamp;
import java.time.Instant;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class GameService {
    static GameRepository gameRepository = new GameRepository();
    static PlayerRepository playerRepository = new PlayerRepository();

    public static List<GameListResponse> listAll() {
        List<GameListResponse> listGameListResponse = new ArrayList<>();
        List<GameModel>  listGameModel = gameRepository.listAll();
        for(GameModel gameModel:listGameModel) {
            listGameListResponse.add(new GameListResponse(gameModel.id, gameModel.players.size(), GameState.valueOf(gameModel.state)));
        }
        return listGameListResponse;
    }
    @Transactional public static GameDetailResponse creatNewGame(String playerName) throws IOException {
        PlayerModel playerModel = new PlayerModel().withGame(null).withName(playerName).withLives(3).withPosx(1).withPosy(1).withLastbomb(null).withLastmovement(null);
        GameModel gameModel = new GameModel().withStarttime(Timestamp.from(Instant.now())).withMap(getMap()).withPlayers(new ArrayList<>()).withState(GameState.STARTING.toString());
        playerModel.game = gameModel;
        gameModel.players.add(playerModel);
        playerRepository.persist(playerModel);
        gameRepository.persist(gameModel);
        List<PlayerResponse> playerResponse = new ArrayList<>();
        playerResponse.add(new PlayerResponse(playerModel.id, playerModel.name, playerModel.lives, playerModel.posy, playerModel.posy));
        return new GameDetailResponse(gameModel.starttime.toString(), GameState.valueOf(gameModel.state), playerResponse, gameModel.map, gameModel.id);
    }

    static public GameDetailResponse getGameInfo(int gameId) {
        GameModel gameModel = gameRepository.find("id", gameId).firstResult();
        if (gameModel == null)
            return null;
        List<PlayerResponse> playerResponses = new ArrayList<>();
        for(PlayerModel playerModel:gameModel.players) {
           playerResponses.add(new PlayerResponse(playerModel.id, playerModel.name, playerModel.lives,playerModel.posx,playerModel.posy));
        }
        return new GameDetailResponse(gameModel.starttime.toString(), GameState.valueOf(gameModel.state), playerResponses,gameModel.map, gameModel.id);
    }

    @Transactional static public GameDetailResponse joinGame(int gameId, String playerName) {
        GameModel gameModel = gameRepository.find("id", gameId).firstResult();
        if (gameModel == null)
            return null;
        PlayerModel playerModel = new PlayerModel().withGame(gameModel).withName(playerName).withLives(3).withLastbomb(null).withLastmovement(null);
        if(gameModel.players.size() == 1) {
            playerModel.posx = 15;
            playerModel.posy = 1;
        }
        else if(gameModel.players.size() == 2) {
            playerModel.posx = 15;
            playerModel.posy = 13;
        }
        else {
            playerModel.posx = 1;
            playerModel.posy = 13;
        }
        if(!(gameModel.players.size() >= 4 || gameModel.state.equals(GameState.FINISHED.toString()) || gameModel.state.equals(GameState.RUNNING.toString()))) {
            playerRepository.persist(playerModel);
            gameModel.players.add(playerModel);
            gameRepository.persist(gameModel);
            List<PlayerResponse> playerResponses = new ArrayList<>();
            for (PlayerModel player : gameModel.players) {
                playerResponses.add(new PlayerResponse(player.id, player.name, player.lives, player.posx, player.posy));
            }
            Hibernate.initialize(gameModel.map);
            return new GameDetailResponse(gameModel.starttime.toString(), GameState.valueOf(gameModel.state), playerResponses, gameModel.map, gameModel.id);
        }
        else {
            return new GameDetailResponse(gameModel.starttime.toString(), GameState.valueOf(gameModel.state), null, gameModel.map, -1);
        }

    }

    @Transactional static public GameDetailResponse startGame(int gameId) {
        boolean a = false;
        GameModel gameModel = gameRepository.find("id", gameId).firstResult();
        if(gameModel == null)
            return null;
        if(gameModel.state.equals(GameState.FINISHED.toString()))
            a = true;
        else if(gameModel.players.size() == 1)
           gameModel.state = GameState.FINISHED.toString();
        else
            gameModel.state = GameState.RUNNING.toString();
        gameRepository.persist(gameModel);
        List<PlayerResponse> playerResponses = new ArrayList<>();
        for(PlayerModel player:gameModel.players) {
            playerResponses.add(new PlayerResponse(player.id, player.name, player.lives, player.posx, player.posy));
        }
        Hibernate.initialize(gameModel.map);
        return new GameDetailResponse(gameModel.starttime.toString(), GameState.valueOf(gameModel.state), playerResponses , gameModel.map, a ? - 1 : gameModel.id);
    }
    @Transactional static public GameDetailResponse move(int gameId, int playerId, int posX, int posY) {
        if(posX < 1 || posX > 15 || posY < 1 || posX > 13)
            return new GameDetailResponse(null, null, null, null, -1);
        GameModel gameModel = gameRepository.find("id", gameId).firstResult();
        PlayerModel playerModel= playerRepository.find("id", playerId).firstResult();
        if (gameModel == null || playerModel == null)
            return null;
        int distance = Math.abs(playerModel.posx - posX) +  Math.abs(playerModel.posy - posY);
        if (gameModel.state.equals(GameState.FINISHED.toString()) || gameModel.state.equals(GameState.STARTING.toString()) || playerModel.lives <= 0 || distance > 1)
            return new GameDetailResponse(null, null, null, null, -1);
        playerModel.posx = posX;
        playerModel.posy = posY;
        playerRepository.persist(playerModel);
        gameRepository.persist(gameModel);
        List<PlayerResponse> playerResponses = new ArrayList<>();
        for(PlayerModel player:gameModel.players) {
            playerResponses.add(new PlayerResponse(player.id, player.name, player.lives, player.posx, player.posy));
        }
        Hibernate.initialize(gameModel.map);
        return new GameDetailResponse(gameModel.starttime.toString(), GameState.valueOf(gameModel.state), playerResponses, gameModel.map, gameModel.id);
    }

    public static GameDetailResponse putBomb(int gameId, int playerId, int posX, int posy) {
        GameModel gameModel = gameRepository.find("id", gameId).firstResult();
        PlayerModel playerModel = playerRepository.find("id", playerId).firstResult();
        if (gameModel == null || playerModel == null)
            return null;
        else if(gameModel.state.equals(GameState.FINISHED.toString()) || gameModel.state.equals(GameState.STARTING.toString()) || playerModel.lives <= 0 || playerModel.posx != posX || playerModel.posy != posy) {
            return new GameDetailResponse(null, null, null ,null, -1);
        }
        else
            return new GameDetailResponse(null, null, null, null, -2);
    }

    static public List<String> getMap() throws IOException {
        List<String> map = new ArrayList<>();
        Scanner scanner = new Scanner(Path.of(System.getenv("JWS_MAP_PATH")));
        while (scanner.hasNext()) {
            map.add(scanner.next());
        }
        return map;
    }

}
