package com.epita.creeps;


import com.epita.creeps.given.exception.NoReportException;
import com.epita.creeps.given.json.Json;
import com.epita.creeps.given.vo.geometry.Point;
import com.epita.creeps.given.vo.report.MoveReport;
import com.epita.creeps.unit.Citizen;
import com.epita.creeps.utils.Pair;
import com.mashape.unirest.http.HttpResponse;
import com.mashape.unirest.http.JsonNode;
import com.mashape.unirest.http.exceptions.UnirestException;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;

public class Action {
    static public String goTo(Point currentPos, Point destPos) {
        if (currentPos.x < destPos.x)
            return "right";
        else if (currentPos.x > destPos.x)
            return "left";
        else if (currentPos.y < destPos.y)
            return "up";
        else if (currentPos.y > destPos.y)
            return "down";
        else
            return null;
    }
/*
    static public boolean directionNull(List<String> listDirections) {
        boolean a = false;
        for (String direction : listDirections) {
            if (direction != null)
                a = true;
        }
        return a;

    }

    static public List<String> rempliList(List<String> listDirections, List<Point> coordonees, List<Citizen> units) {
        for (int i = 0; i < coordonees.size(); i++) {
            listDirections.add(goTo(units.get(i).co, coordonees.get(i)));
        }
        return listDirections;
    }

    static public void move(List<Point> coordonees, List<Citizen> units) throws UnirestException, NoReportException, ExecutionException, InterruptedException {
        List<Pair> moveCitizens = new ArrayList<>();
        List<String> listDirections = new ArrayList<>();
        while (directionNull(rempliList(listDirections, coordonees, units))) {
            System.out.println("citoyen1 co : " + units.get(0).co + " dest co " + coordonees.get(0) + " direction " +listDirections.get(0));
            System.out.println("le citoyen 1 est arriver " + units.get(0).co.equals(coordonees.get(0)));
            //System.out.println("citoyen2 co : " + units.get(1).co + " dest co " + coordonees.get(1) + " direction " +listDirections.get(1));
            //System.out.println("le citoyen 2 est arriver " + units.get(1).co.equals(coordonees.get(1)));
            for (int i = 0; i < coordonees.size(); i++) {
                if (listDirections.get(i) != null)
                    moveCitizens.add(new Pair(units.get(i), units.get(i).move(listDirections.get(i))));
                else
                    moveCitizens.add(null);
            }
            int i = 0;
            for (Pair move : moveCitizens) {
                if (move != null) {
                    move.key.co = ((MoveReport) InteractionServer.Get(move.value, InteractionServer.reportName.move)).newPosition;
                }
                i++;
            }
            moveCitizens = new ArrayList<>();
            listDirections = new ArrayList<>();
        }

    }


    static public void moveSingle(Point coDest, Citizen unitToDeplace) throws UnirestException, NoReportException, ExecutionException, InterruptedException {
        CompletableFuture<HttpResponse<JsonNode>> moveCitizen = null;
        String direction = null;
        while ((direction = goTo(unitToDeplace.co, coDest)) != null) {
            if (direction != null)
                moveCitizen = unitToDeplace.move(direction);
            if (moveCitizen != null)
                unitToDeplace.co = ((MoveReport) InteractionServer.Get(moveCitizen, InteractionServer.reportName.move)).newPosition;
        }
    }

 */


    static public void goGetTiles() {

    }
}