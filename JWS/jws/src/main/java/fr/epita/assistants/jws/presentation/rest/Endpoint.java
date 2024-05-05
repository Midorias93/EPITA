package fr.epita.assistants.jws.presentation.rest;


import fr.epita.assistants.jws.data.model.GameModel;
import fr.epita.assistants.jws.domain.entity.GameEntity;
import fr.epita.assistants.jws.domain.entity.PlayerEntity;
import fr.epita.assistants.jws.domain.service.GameService;
import fr.epita.assistants.jws.domain.service.PlayerService;
import fr.epita.assistants.jws.presentation.rest.request.CreatGameRequest;
import fr.epita.assistants.jws.presentation.rest.request.JoinGameRequest;
import fr.epita.assistants.jws.presentation.rest.request.MovePlayerRequest;
import fr.epita.assistants.jws.presentation.rest.request.PutBombRequest;
import fr.epita.assistants.jws.presentation.rest.response.GameDetailResponse;
import fr.epita.assistants.jws.presentation.rest.response.GameListResponse;
import fr.epita.assistants.jws.utils.GameState;

import javax.inject.Inject;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

@Path("/games")
@Produces(MediaType.TEXT_PLAIN)
@Consumes(MediaType.TEXT_PLAIN)
public class Endpoint {
    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response getGames() {
        return Response.ok(GameService.listAll()).build();
    }

    @POST
    @Produces(MediaType.APPLICATION_JSON)
    @Consumes(MediaType.APPLICATION_JSON)
    public Response createNewGame(CreatGameRequest creatGameRequest) throws IOException {
        if (creatGameRequest == null || creatGameRequest.name == null)
            return Response.status(400).build();
        return Response.ok(GameService.creatNewGame(creatGameRequest.name)).build();
    }

    @GET
    @Path("{gameId}")
    @Produces(MediaType.APPLICATION_JSON)
    public Response getGameInfo(@PathParam("gameId") int gameId) {
        GameDetailResponse gameDetailResponse = GameService.getGameInfo(gameId);
        if(gameDetailResponse == null)
            return Response.status(404).build();
        return Response.ok(gameDetailResponse).build();
    }

    @POST
    @Path("{gameId}")
    @Produces(MediaType.APPLICATION_JSON)
    @Consumes(MediaType.APPLICATION_JSON)
    public Response joinGame(@PathParam("gameId") int gameId, JoinGameRequest joinGameRequest) {
        if (joinGameRequest == null || joinGameRequest.name == null)
            return Response.status(400).build();
        GameDetailResponse gameDetailResponse = GameService.joinGame(gameId, joinGameRequest.name);
        if (gameDetailResponse == null)
            return Response.status(404).build();
        if (gameDetailResponse.id == -1)
            return Response.status(400).build();
        return Response.ok(gameDetailResponse).build();
    }

    @PATCH
    @Path("{gameId}/start")
    @Produces(MediaType.APPLICATION_JSON)
    public Response startGame(@PathParam("gameId") int gameId) {
        GameDetailResponse gameDetailResponse = GameService.startGame(gameId);
        if (gameDetailResponse == null)
            return Response.status(400).build();
        if(gameDetailResponse.id == -1)
            return Response.status(404).build();
        return Response.ok(gameDetailResponse).build();
    }

    @POST
    @Path("{gameId}/players/{playerId}/move")
    @Produces(MediaType.APPLICATION_JSON)
    @Consumes(MediaType.APPLICATION_JSON)
    public Response movePlayer(@PathParam("gameId") int gameId, @PathParam("playerId") int playerId, MovePlayerRequest movePlayerRequest) {
        GameDetailResponse gameDetailResponse = GameService.move(gameId, playerId, movePlayerRequest.posX, movePlayerRequest.posY);
        if(gameDetailResponse == null)
            return Response.status(404).build();
        if(gameDetailResponse.id == -1)
            return Response.status(400).build();
        return Response.ok(gameDetailResponse).build();
    }
    @POST
    @Path("{gameId}/players/{playerId}/bomb")
    @Produces(MediaType.APPLICATION_JSON)
    @Consumes(MediaType.APPLICATION_JSON)
    public Response putBomb(@PathParam("gameId") int gameId, @PathParam("playerId") int playerId, PutBombRequest putBombRequest) {
        if (putBombRequest == null)
            return Response.status(400).build();
        GameDetailResponse gameDetailResponse = GameService.putBomb(gameId, playerId, putBombRequest.posX, putBombRequest.posY);
        if(gameDetailResponse == null)
            return  Response.status(404).build();
        else if(gameDetailResponse.id == -1)
            return Response.status(400).build();
        else
            return Response.status(429).build();
    }

}
