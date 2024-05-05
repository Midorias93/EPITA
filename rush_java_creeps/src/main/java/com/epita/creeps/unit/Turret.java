package com.epita.creeps.unit;

import com.epita.creeps.InteractionServer;
import com.epita.creeps.given.json.Json;
import com.epita.creeps.given.vo.geometry.Point;
import com.epita.creeps.given.vo.parameter.FireParameter;
import com.epita.creeps.given.vo.response.CommandResponse;
import com.epita.creeps.given.vo.response.InitResponse;
import com.epita.creeps.unit.myUnit;
import com.mashape.unirest.http.HttpResponse;
import com.mashape.unirest.http.JsonNode;
import com.mashape.unirest.http.Unirest;
import com.mashape.unirest.http.exceptions.UnirestException;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.TimeUnit;

public class Turret extends myUnit {
    public Turret(String myUnitId, Point co, InitResponse info, String[] args) {
        super(myUnitId, co, info, args);
    }
    public CompletableFuture<HttpResponse<JsonNode>> fire (Point fireCo) throws UnirestException {
        String URL = "http://" + args[0] + ":" + args[1] + "/command/" + args[2] + "/" + this.myUnitId + "/fire:turret";
        HttpResponse<JsonNode> serverResponse = Unirest.post(URL).body(Json.serialize(new FireParameter(fireCo))).asJson();
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
        }, CompletableFuture.delayedExecutor((long) (this.info.costs.fireTurret.cast / this.info.setup.ticksPerSeconds),
                TimeUnit.SECONDS));


    }
}
