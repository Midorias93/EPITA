package com.epita.creeps.unit;

import com.epita.creeps.InteractionServer;
import com.epita.creeps.given.json.Json;
import com.epita.creeps.given.vo.Resources;
import com.epita.creeps.given.vo.geometry.Point;
import com.epita.creeps.given.vo.report.MoveReport;
import com.epita.creeps.given.vo.response.CommandResponse;
import com.epita.creeps.given.vo.response.InitResponse;
import com.mashape.unirest.http.HttpResponse;
import com.mashape.unirest.http.JsonNode;
import com.mashape.unirest.http.Unirest;
import com.mashape.unirest.http.exceptions.UnirestException;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.TimeUnit;

public class Citizen extends myUnit {
    Resources inventaire;
    public Citizen(String myUnitId, Point co, InitResponse info, String[] args, Resources inventaire) {
        super(myUnitId, co, info, args);
    }

    public CompletableFuture<HttpResponse<JsonNode>> move (String direction) throws UnirestException {
        String URL = "http://" + args[0] + ":" + args[1] + "/command/" + args[2] + "/" + this.myUnitId + "/move:" + direction;
        HttpResponse<JsonNode> serverResponse = Unirest.post(URL).body("{}").asJson();
        CommandResponse response = Json.parse(serverResponse.getBody().toString(), CommandResponse.class);
        if (response.errorCode != null && response.errorCode.compareTo("noplayer") == 0 || response.reportId == null) {
            this.isALife = false;
            return null;
        }
        return CompletableFuture.supplyAsync(() -> {
            try {
                return InteractionServer.getReport(response.reportId, args);
            } catch (UnirestException e) {
                throw new RuntimeException(e);
            }
        }, CompletableFuture.delayedExecutor((long) (this.info.costs.move.cast / this.info.setup.ticksPerSeconds),
                TimeUnit.SECONDS));
    }
    public MoveReport getMove (CompletableFuture<JsonNode> futureReport) {
        if (futureReport != null) {

        }

    }

    public CompletableFuture<HttpResponse<JsonNode>> observe () throws UnirestException {
        String URL = "http://" + args[0] + ":" + args[1] + "/command/" + args[2] + "/" + this.myUnitId + "/observe";
        HttpResponse<JsonNode> serverResponse = Unirest.post(URL).body("{}").asJson();
        CommandResponse response = Json.parse(serverResponse.getBody().toString(), CommandResponse.class);
        if (response.errorCode != null && response.errorCode.compareTo("noplayer") == 0 || response.reportId == null) {
            this.isALife = false;
        }
        return CompletableFuture.supplyAsync(() -> {
            try {
                return InteractionServer.getReport(response.reportId, args);
            } catch (UnirestException e) {
                throw new RuntimeException(e);
            }
        }, CompletableFuture.delayedExecutor((long) (this.info.costs.observe.cast / this.info.setup.ticksPerSeconds),
                TimeUnit.SECONDS));

    }
    public CompletableFuture<HttpResponse<JsonNode>> gather () throws UnirestException {
        String URL = "http://" + args[0] + ":" + args[1] + "/command/" + args[2] + "/" + this.myUnitId + "/gather";
        HttpResponse<JsonNode> serverResponse = Unirest.post(URL).body("{}").asJson();
        CommandResponse response = Json.parse(serverResponse.getBody().toString(), CommandResponse.class);
        if (response.errorCode != null && response.errorCode.compareTo("noplayer") == 0 || response.reportId == null) {
            this.isALife = false;
        }
        return CompletableFuture.supplyAsync(() -> {
            try {
                return InteractionServer.getReport(response.reportId, args);
            } catch (UnirestException e) {
                throw new RuntimeException(e);
            }
        }, CompletableFuture.delayedExecutor((long) (this.info.costs.gather.cast / this.info.setup.ticksPerSeconds),
                TimeUnit.SECONDS));


    }
    public void unload () {

    }
    public CompletableFuture<HttpResponse<JsonNode>> spawnTurret () throws UnirestException {
        String URL = "http://" + args[0] + ":" + args[1] + "/command/" + args[2] + "/" + this.myUnitId + "/spawn:turret";
        HttpResponse<JsonNode> serverResponse = Unirest.post(URL).body("{}").asJson();
        CommandResponse response = Json.parse(serverResponse.getBody().toString(), CommandResponse.class);
        if (response.errorCode != null && response.errorCode.compareTo("noplayer") == 0 || response.reportId == null) {
            this.isALife = false;
        }
        return CompletableFuture.supplyAsync(() -> {
            try {
                return InteractionServer.getReport(response.reportId, args);
            } catch (UnirestException e) {
                throw new RuntimeException(e);
            }
        }, CompletableFuture.delayedExecutor((long) (this.info.costs.spawnTurret.cast / this.info.setup.ticksPerSeconds),
                TimeUnit.SECONDS));

    }
    public void farm() {

    }
    public CompletableFuture<HttpResponse<JsonNode>> buildRoad () throws UnirestException {
        String URL = "http://" + args[0] + ":" + args[1] + "/command/" + args[2] + "/" + this.myUnitId + "/build:road";
        HttpResponse<JsonNode> serverResponse = Unirest.post(URL).body("{}").asJson();
        CommandResponse response = Json.parse(serverResponse.getBody().toString(), CommandResponse.class);
        if (response.errorCode != null && response.errorCode.compareTo("noplayer") == 0 || response.reportId == null) {
            this.isALife = false;
        }
        return CompletableFuture.supplyAsync(() -> {
            try {
                return InteractionServer.getReport(response.reportId, args);
            } catch (UnirestException e) {
                throw new RuntimeException(e);
            }
        }, CompletableFuture.delayedExecutor((long) (this.info.costs.buildRoad.cast / this.info.setup.ticksPerSeconds),
                TimeUnit.SECONDS));

    }
    public void upgrade () {

    }
    public void refine () {

    }
    public void mesage () {

    }

}
