package com.epita.creeps;

import com.epita.creeps.given.extra.Cartographer;
import com.epita.creeps.given.vo.Tile;
import com.epita.creeps.given.vo.geometry.Point;

import java.util.ArrayList;
import java.util.List;

public class Carte {
    static public Point getTiles(Cartographer cartographer, Tile resourceType, Point currentPos) {
        List<Point> list = cartographer.requestOfType(resourceType).toList();
        if (list.size() == 0)
            return null;
        Point closest = list.get(0);
        Point difColsest = null;
        Point dif = null;
        int distance = 0;
        int distanceClosest = 0;
        for (Point co : list) {
            difColsest = closest.minus(currentPos);
            dif = co.minus(currentPos);
            distanceClosest = Math.abs(dif.x) + Math.abs(dif.y);
            distance = Math.abs(dif.x) + Math.abs(dif.y);
            if (distance < distanceClosest) {
                closest = co;
            }
        }
        return closest;
    }

    public static Point closestToUnitAndBuild(Cartographer cartographer,  Point currentPos, Point destPost) {

        List<Point> list = new ArrayList<>(cartographer.requestOfType(Tile.Road).toList());

        list.addAll(cartographer.requestOfType(Tile.Household).toList());
        list.addAll(cartographer.requestOfType(Tile.TownHall).toList());
        list.addAll(cartographer.requestOfType(Tile.Smeltery).toList());
        list.addAll(cartographer.requestOfType(Tile.Sawmill).toList());

        if (list.size() == 0)
            return null;


       Point closest = list.get(0);

        Point difClosestToBuild = null;
        int distanceClosestToBuild = 0;

        Point difClosestToUnit = null;
        int distanceClosestToUnit = 0;

        Point difCoAndBuild = null;
        int distanceCoAndBuild = 0;

        Point difCoAndUnit = null;
        int distanceCoAndUnit = 0;


        for (Point co : list) {

            difCoAndBuild = co.minus(destPost);
            difCoAndUnit = co.minus(currentPos);
            distanceCoAndBuild = Math.abs(difCoAndBuild.x) + Math.abs(difCoAndBuild.y);
            distanceCoAndUnit = Math.abs(difCoAndUnit.x) + Math.abs(difCoAndUnit.y);

            difClosestToBuild = closest.minus(destPost);
            difClosestToUnit = co.minus(currentPos);
            distanceClosestToBuild = Math.abs(difClosestToBuild.x) + Math.abs(difClosestToBuild.y);
            distanceClosestToUnit = Math.abs(difClosestToUnit.x) + Math.abs(difClosestToUnit.y);

            if (distanceCoAndUnit <= distanceClosestToUnit && distanceCoAndBuild <= distanceClosestToBuild) {
                closest = co;
            }
        }
        return closest;
    }
}
