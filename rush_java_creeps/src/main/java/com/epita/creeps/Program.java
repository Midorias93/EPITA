package com.epita.creeps;


import com.epita.creeps.build.Townhall;
import com.epita.creeps.given.exception.NoReportException;
import com.epita.creeps.given.extra.Cartographer;
import com.epita.creeps.given.json.Json;
import com.epita.creeps.given.vo.Tile;
import com.epita.creeps.given.vo.geometry.Point;
import com.epita.creeps.given.vo.response.InitResponse;
import com.epita.creeps.unit.Citizen;
import com.mashape.unirest.http.exceptions.UnirestException;

import java.io.IOException;
import java.util.concurrent.ExecutionException;

public class Program {
    public static void main(String[] args) throws ExecutionException, InterruptedException, UnirestException, NoReportException, IOException {
        if (args.length < 3)
            return;


        String report = InteractionServer.init(args).getBody().toString();

        /*
        BufferedWriter writer = new BufferedWriter(new FileWriter("file.txt"));
        writer.write(report);

        writer.close();
         */

        InitResponse info = Json.parse(report ,InitResponse.class);

        Townhall mainTown = new Townhall(true, info.townHallCoordinates, info.resources);

        Citizen citizen1 = new Citizen(info.citizen1Id, info.householdCoordinates, info, args, info.resources);
        Citizen citizen2 = new Citizen(info.citizen2Id, info.householdCoordinates, info, args, info.resources);

            /*
            if (move != null)
                citizen1.co = ((MoveReport) InteractionServer.Get(move, InteractionServer.commandType.move)).newPosition;
            CompletableFuture<HttpResponse<JsonNode>> turret = citizen1.spawnTurret();
            Turret tutu = null;
            if (turret != null) {
                SpawnReport report = (SpawnReport) InteractionServer.Get(turret, InteractionServer.commandType.spawn);
                if (report != null) {
                    tutu = new Turret(report.spawnedUnitId, citizen1.co, info, args);
                }
            }
            move = citizen1.move("down");
            if (move != null)
                citizen1.co = ((MoveReport) InteractionServer.Get(move, InteractionServer.commandType.move)).newPosition;

            if (tutu != null)
                InteractionServer.Get(tutu.fire(citizen1.co), InteractionServer.commandType.fire);
     */
        String directionCitizen1;
        String directionCitizen2;
       for(int i = 0; i < 3; i++) {
           Action.moveSingle(citizen1.co.plus(1, 0), citizen1);
           InteractionServer.Get(citizen1.buildRoad(), InteractionServer.reportName.build);
       }
       for(int i = 0; i < 2; i++) {
           Action.moveSingle(citizen1.co.plus(1, 0), citizen1);
       }
       InteractionServer.Get(citizen1.buildRoad(), InteractionServer.reportName.build);
       Action.moveSingle(citizen1.co.plus(-1, 0), citizen1);
       while (!citizen1.co.equals(info.householdCoordinates)) {
           Action.moveSingle(Carte.closestToUnitAndBuild(Cartographer.INSTANCE,citizen1.co, info.householdCoordinates), citizen1);
       }

        /*
        Point co2 = null;
        while (co2 == null)
        {

            co2 = Carte.getTiles(Cartographer.INSTANCE , Tile.Food, citizen1.co);
            if (co2 == null)
                Action.moveSingle(citizen1.co.plus(1,0), citizen1);
        }

       Action.moveSingle(co2, citizen1);
        */


       /*
        Point co1 = info.householdCoordinates.plus(5, 0);
        co2 = info.householdCoordinates.plus(0,3);
        List<Point> listCo = new ArrayList<>();
        listCo.add(co1);
        listCo.add(co2);
        List<Citizen> listUnit = new ArrayList<>();
        listUnit.add(citizen1);
        listUnit.add(citizen2);
        Action.deplaceUnits(listCo, listUnit);
        */
    }
}