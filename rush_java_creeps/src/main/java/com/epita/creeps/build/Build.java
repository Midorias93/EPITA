package com.epita.creeps.build;

import com.epita.creeps.given.vo.geometry.Point;

abstract public class Build {
    boolean isSafePlace;
    Point co;
    Build (boolean isSafePlace, Point co) {
        this.isSafePlace = isSafePlace;
        this.co = co;
    }
}
