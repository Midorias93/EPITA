package com.epita.creeps.unit;

import com.epita.creeps.InteractionServer;
import com.epita.creeps.given.json.Json;
import com.epita.creeps.given.vo.geometry.Point;
import com.epita.creeps.given.vo.response.CommandResponse;
import com.epita.creeps.given.vo.response.InitResponse;
import com.mashape.unirest.http.HttpResponse;
import com.mashape.unirest.http.JsonNode;
import com.mashape.unirest.http.Unirest;
import com.mashape.unirest.http.exceptions.UnirestException;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.TimeUnit;

abstract public class myUnit {
    boolean isALife = true;
    String myUnitId;
    public Point co;
    InitResponse info;
    String[] args;
    public boolean IsSafe = true;
    public myUnit(String myUnitId, Point co, InitResponse info, String[] args) {
        this.myUnitId = myUnitId;
        this.co = co;
        this.info = info;
        this.args = args;
    }

    public CompletableFuture<HttpResponse<JsonNode>> noop() throws UnirestException {
        String URL = "http://" + this.args[0] + ":" + this.args[1] + "/command/" + this.args[2] + "/" + this.myUnitId + "/noop";
        HttpResponse<JsonNode> serverResponse = Unirest.post(URL).body("{}").asJson();
        CommandResponse response = Json.parse(serverResponse.getBody().toString(), CommandResponse.class);
        if (response.errorCode != null && response.errorCode.compareTo("noplayer") == 0 || response.reportId == null) {
            this.isALife = false;
            return null;
        }
        return CompletableFuture.supplyAsync(() -> {
            try {
                return InteractionServer.getReport(response.reportId, this.args);
            } catch (UnirestException e) {
                throw new RuntimeException(e);
            }
        }, CompletableFuture.delayedExecutor((long) (this.info.costs.noop.cast / this.info.setup.ticksPerSeconds),
                TimeUnit.SECONDS));
    }

}
